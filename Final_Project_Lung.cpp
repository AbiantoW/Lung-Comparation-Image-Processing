//	Final project "Lung Cancer Detection"
//	Mata Kuliah Pengolahan Citra
//	Abianto Wibisono 0000000007344 - Teknik Informatika UPH 2014

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

int main()
{
	Mat source;

	source = imread("dataset1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	//Penggunaan Filter Gabor
	Mat gaborkernel;
	Mat gaborout;
	int kernel_size = 7;	//fixed
	double sig = 1.0, th = 0, lm = 0.2, gm = 0.01, ps = 0;
	gaborkernel = getGaborKernel( CvSize( kernel_size, kernel_size), sig, th, lm, gm, ps);
	filter2D(source, gaborout, CV_16U, gaborkernel);


	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", source);

	namedWindow("Gabor Filter", WINDOW_AUTOSIZE);
	imshow("Gabor Filter", gaborout);
	
	waitKey(0);

	return 0;
}
