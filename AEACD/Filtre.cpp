
#include "stdafx.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

 
using namespace cv;
using namespace std;

class Filtre
{

public:
	// Blur Correction
	// Illumination Correction
	// Edge Enhancement
	// Operatii morfologice de dilatare si eroziune

	void IlluminationCorrection() {
		Mat bgr_image = imread("skew.jpg");
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

		imshow("Image Original", bgr_image);
		imshow("Image CLAHE", image_clahe);
	}

private:
	;

};
