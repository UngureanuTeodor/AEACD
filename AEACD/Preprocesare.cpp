
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

private:
	;

};
