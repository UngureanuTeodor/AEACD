#include "stdafx.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "tesseract/baseapi.h"
#include "iostream"

using namespace cv;
using namespace std;

class Tesseract
{
public:
	Mat TesseractTool(Mat inputImage)
	{
		char* inputPath="";
		Mat im = imread(inputPath);
		if (im.empty())
		{
			cout << "Cannot open source image!" << endl;

		}

		Mat gray;
		cvtColor(im, gray, CV_BGR2GRAY);
		// ...other image pre-processing here...

		// Pass it to Tesseract API
		tesseract::TessBaseAPI tess;
		tess.Init("./tessdata", "eng", tesseract::OEM_TESSERACT_CUBE_COMBINED);
		tess.SetPageSegMode(tesseract::PSM_AUTO);

		tess.SetImage((uchar*)gray.data, gray.cols, gray.rows, 1, gray.cols);

		// Get the text
		int* outAccuracy = tess.AllWordConfidences();
		char* outText = tess.GetUTF8Text();
		cout << outText << endl;
		cout <<"Accuracy: "<< outAccuracy << endl;

		return im;
	}
private:
};