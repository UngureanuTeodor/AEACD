
#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Filtre
{

public:
	// Edge Enhancement
	// Operatii morfologice de dilatare si eroziune





	///////////////////////////////
	// BEGIN IlluminationCorrection

	Mat IlluminationCorrection(char* imagePath) {
		Mat bgr_image = imread(imagePath);
		Mat lab_image;
		cvtColor(bgr_image, lab_image, CV_BGR2Lab);

		// Extract the L channel in lab_planes[0]
		vector<Mat> lab_planes(3);
		split(lab_image, lab_planes);

		// Apply the CLAHE algorithm to the L channel
		Ptr<CLAHE> clahe = createCLAHE();
		clahe->setClipLimit(4);
		Mat dst;
		clahe->apply(lab_planes[0], dst);

		// Merge the color planes back into a Lab Image
		dst.copyTo(lab_planes[0]);
		merge(lab_planes, lab_image);

		// Convert back to RGB
		Mat image_clahe;
		cvtColor(lab_image, image_clahe, CV_Lab2BGR);

		return image_clahe;
	}

	// END IlluminationCorrection
	/////////////////////////////





	///////////////////////
	// BEGIN BlurCorrection

	Mat BlurCorrection(char* imagePath, int R, int snr) {
		Mat imgIn, imgOut;
		imgIn = imread(imagePath, IMREAD_GRAYSCALE);

		// It needs to process even image only
		Rect roi = Rect(0, 0, imgIn.cols & -2, imgIn.rows & -2);

		// Hw Calculation
		Mat Hw, h;
		calcPSF(h, roi.size(), R);
		calcWnrFilter(h, Hw, 1.0 / double(snr));

		// Filtering
		filter2DFreq(imgIn(roi), imgOut, Hw);

		imgOut.convertTo(imgOut, CV_8U);
		normalize(imgOut, imgOut, 0, 255, NORM_MINMAX);

		return imgOut;
	}

	void calcPSF(Mat& outputImg, Size filterSize, int R) {
		Mat h(filterSize, CV_32F, Scalar(0));
		Point point(filterSize.width / 2, filterSize.height / 2);
		circle(h, point, R, 255, -1, 8);
		Scalar summa = sum(h);
		outputImg = h / summa[0];
	}

	void fftshift(const Mat& inputImg, Mat& outputImg) {
		outputImg = inputImg.clone();
		int cx = outputImg.cols / 2;
		int cy = outputImg.rows / 2;
		Mat q0(outputImg, Rect(0, 0, cx, cy));
		Mat q1(outputImg, Rect(cx, 0, cx, cy));
		Mat q2(outputImg, Rect(0, cy, cx, cy));
		Mat q3(outputImg, Rect(cx, cy, cx, cy));
		Mat tmp;
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);
		q1.copyTo(tmp);
		q2.copyTo(q1);
		tmp.copyTo(q2);
	}

	void filter2DFreq(const Mat& inputImg, Mat& outputImg, const Mat& H) {
		Mat planes[2] = { Mat_<float>(inputImg.clone()), Mat::zeros(inputImg.size(), CV_32F) };
		Mat complexI;
		merge(planes, 2, complexI);
		dft(complexI, complexI, DFT_SCALE);
		Mat planesH[2] = { Mat_<float>(H.clone()), Mat::zeros(H.size(), CV_32F) };
		Mat complexH;
		merge(planesH, 2, complexH);
		Mat complexIH;
		mulSpectrums(complexI, complexH, complexIH, 0);
		idft(complexIH, complexIH);
		split(complexIH, planes);
		outputImg = planes[0];
	}

	void calcWnrFilter(const Mat& input_h_PSF, Mat& output_G, double nsr) {
		Mat h_PSF_shifted;
		fftshift(input_h_PSF, h_PSF_shifted);
		Mat planes[2] = { Mat_<float>(h_PSF_shifted.clone()), Mat::zeros(h_PSF_shifted.size(), CV_32F) };
		Mat complexI;
		merge(planes, 2, complexI);
		dft(complexI, complexI);
		split(complexI, planes);
		Mat denom;
		pow(abs(planes[0]), 2, denom);
		denom += nsr;
		divide(planes[0], denom, output_G);
	}

	// END BlurCorrection
	/////////////////////





private:
	;

};
