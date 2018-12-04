
#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Preprocesare
{

public:
	Mat RGB2Gray(char* imagePath) {
		Mat dst;
		Mat src = imread(imagePath, IMREAD_COLOR);

		cvtColor(src, dst, COLOR_BGR2GRAY);

		return dst;
	}

	Mat OtsuThresholding(char* imagePath) {
		Mat dst_otsu;
		Mat src_gray = RGB2Gray(imagePath);

		threshold(src_gray, dst_otsu, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

		return dst_otsu;
	}

	Mat BinaryInverseThresholding(Mat src) {
		Mat dst_binary_inv_thr;

		threshold(src, dst_binary_inv_thr, 200, 255, THRESH_BINARY_INV);

		return dst_binary_inv_thr;
	}

	Mat GenerateRotationMatrix(vector<Point> points) {
		RotatedRect box = minAreaRect(Mat(points));
		Mat rot_mat = getRotationMatrix2D(box.center, box.angle, 1);

		return rot_mat;
	}

	Mat DeskewRotationAndCorrection(Mat src, Mat thr) {
		vector<Point> points;
		Mat_<uchar>::iterator it = thr.begin<uchar>();
		Mat_<uchar>::iterator end = thr.end<uchar>();

		for (; it != end; ++it) {
			if (*it) {
				points.push_back(it.pos());
			}
		}

		Mat rot_mat = GenerateRotationMatrix(points);

		Mat rotated;
		warpAffine(src, rotated, rot_mat, src.size(), INTER_CUBIC);

		return rotated;
	}

	Rect findBorder(InputArray _src, int size) {
		Mat src = _src.getMat();
		Mat sbl_x, sbl_y;
		int ksize = 2 * size + 1;
		Sobel(src, sbl_x, CV_32FC1, 2, 0, ksize);
		Sobel(src, sbl_y, CV_32FC1, 0, 2, ksize);
		Mat sum_img = sbl_x + sbl_y;

		Mat gray;
		normalize(sum_img, gray, 0, 255, CV_MINMAX, CV_8UC1);

		Mat row_proj, col_proj;
		reduce(gray, row_proj, 1, CV_REDUCE_AVG, CV_8UC1);
		reduce(gray, col_proj, 0, CV_REDUCE_AVG, CV_8UC1);
		Sobel(row_proj, row_proj, CV_8UC1, 0, 2, 3);
		Sobel(col_proj, col_proj, CV_8UC1, 2, 0, 3);


		Point peak_pos;
		int half_pos = row_proj.total() / 2;
		Rect result;

		minMaxLoc(row_proj(Range(0, half_pos), Range(0, 1)), 0, 0, 0, &peak_pos);
		result.y = peak_pos.y;
		minMaxLoc(row_proj(Range(half_pos, row_proj.total()), Range(0, 1)), 0, 0, 0, &peak_pos);
		result.height = (peak_pos.y + half_pos - result.y);

		half_pos = col_proj.total() / 2;
		minMaxLoc(col_proj(Range(0, 1), Range(0, half_pos)), 0, 0, 0, &peak_pos);
		result.x = peak_pos.x;
		minMaxLoc(col_proj(Range(0, 1), Range(half_pos, col_proj.total())), 0, 0, 0, &peak_pos);
		result.width = (peak_pos.x + half_pos - result.x);

		return result;
	}

	Mat BorderRemoval(Mat src) {
		Rect r = findBorder(src, 2);
		Mat dest = src(r);
		return dest;
	}

private:
	;

};
