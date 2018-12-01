
#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using std::cout;

Mat src, src_gray, dst;
const char* window_name = "Otsu Thresholding";

int main(int argc, char** argv)
{
	// Otsu Binarization and Thresholding
	//String imageName("Romeo and Juliet.jpg"); 
	//src = imread(imageName, IMREAD_COLOR); // Load an image
	//
	//if (src.empty()) {
	//	cout << "Cannot read image: " << imageName << std::endl;
	//	return -1;
	//}

	//cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
	//namedWindow(window_name, WINDOW_NORMAL); // Create a window to display results

	//threshold(src_gray, dst, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	//imshow(window_name, dst);
	//resizeWindow(window_name, 512, 830);

	// Skew Detection and Correction
	Mat src = imread("skew.jpg", 0);
	Mat thr, dst;
	threshold(src, thr, 200, 255, THRESH_BINARY_INV);
	imshow("thr", thr);

	std::vector<cv::Point> points;
	cv::Mat_<uchar>::iterator it = thr.begin<uchar>();
	cv::Mat_<uchar>::iterator end = thr.end<uchar>();
	for (; it != end; ++it)
	if (*it)
		points.push_back(it.pos());

	cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
	cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, box.angle, 1);

	Mat rotated;
	cv::warpAffine(src, rotated, rot_mat, src.size(), cv::INTER_CUBIC);
	imshow("Deskewed", rotated);

	waitKey();
	return 0;
}