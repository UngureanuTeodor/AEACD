
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

void main_teo() {
	Preprocesare preprocesare;

	// Otsu Binarization and 
	Mat dst_otsu = preprocesare.OtsuThresholding("Romeo and Juliet.jpg");
	// Display Otsu
	char* window_name = "Otsu Thresholding";
	namedWindow(window_name, WINDOW_NORMAL);
	imshow(window_name, dst_otsu);
	resizeWindow(window_name, 512, 830);
	
	// Skew Detection and Correction
	Mat src = imread("skew.jpg", 0);
	Mat thr = preprocesare.BinaryInverseThresholding(src);
	imshow("Binary Inverse Thresholding", thr);
	// Display Rotated
	Mat rotated = preprocesare.DeskewRotationAndCorrection(src, thr);
	imshow("Deskewed", rotated);
	Tesseract tesseract;
	tesseract.TesseractTool("skew.jpg");	
}

void main_alex() {

	
}


int main(int argc, char** argv)
{

	// main_andrei();
	main_teo();
	//main_alex();
	waitKey();

	return 0;
}