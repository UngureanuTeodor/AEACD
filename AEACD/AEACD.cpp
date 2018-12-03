
#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "tesseract/baseapi.h"
#include <iostream>

#include "Preprocesare.cpp"
#include "Filtre.cpp"
#include "Tesseract.cpp"

using namespace cv;
using namespace std;

void main_andrei() {}

void Pas1_Preprocesare() {
	Preprocesare preprocesare;

	// Otsu Binarization
	Mat src_rj = imread("Alice in Wonderland.jpg", IMREAD_COLOR);
	namedWindow("Alice in Wonderland", WINDOW_NORMAL);
	imshow("Alice in Wonderland", src_rj);
	resizeWindow("Alice in Wonderland", 512, 830);
	Mat dst_otsu = preprocesare.OtsuThresholding("Alice in Wonderland.jpg");
	// Display Otsu
	char* window_name = "Otsu Thresholding";
	namedWindow(window_name, WINDOW_NORMAL);
	imshow(window_name, dst_otsu);
	resizeWindow(window_name, 512, 830);

	// Skew Detection and Correction
	Mat src = imread("skew.jpg", 0);
	imshow("Skewed", src);
	Mat thr = preprocesare.BinaryInverseThresholding(src);
	imshow("Binary Inverse Thresholding", thr);
	// Display Rotated
	Mat rotated = preprocesare.DeskewRotationAndCorrection(src, thr);
	imshow("Deskewed", rotated);

	Tesseract tesseract;
	tesseract.TesseractTool(rotated);
}

void Pas2_AplicareFiltre() {
	Filtre filtre;

	// Illumination Correction
	Mat image_clahe = filtre.IlluminationCorrection("illumination_correction.png");
	// Display Illumination Correction
	char* window_name = "Illumination Correction";
	namedWindow(window_name, WINDOW_NORMAL);
	imshow(window_name, image_clahe);
	resizeWindow(window_name, 960, 540);

	// Blur Correction
	int R = 2;
	int snr = 20;
	Mat blur_correction = filtre.BlurCorrection("blurry.jpg", R, snr);
	// Display Blur Correction
	imshow("Blur Correction", blur_correction);
}

void main_teo() {
	// Pas1_Preprocesare();
	Pas2_AplicareFiltre();
}

void main_alex() {
}

int main(int argc, char** argv)
{
	// main_alex();
	// main_andrei();
	main_teo();

	waitKey();

	return 0;
}