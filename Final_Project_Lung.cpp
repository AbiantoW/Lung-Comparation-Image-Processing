//	Final project "Lung Cancer Detection"
//	Mata Kuliah Pengolahan Citra
//	Abianto Wibisono 00000007344 - Teknik Informatika UPH 2014
//  Sherwin			 00000006001 - Teknik Informatika UPH 2014

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

Mat preProcSequence(Mat src) 
{
	//pre-processing

	//bitplane slicing
	cout << " Begin Bitplane Slicing" << endl;
	Mat bitplane8(((src/ (1 << 8)) & 1) * 255);
	//imshow("Bit Plane Slicing 8", bitplane8);

	//erode
	cout << " Begin Erode Picture" << endl;
	Mat	erode_out;
	Mat erode_kernel(15, 15, CV_8UC1);
	erode(bitplane8, erode_out, erode_kernel);
	//imshow("Erode", erode_out);

	//median
	cout << " Begin Median Smooting Filter" << endl;
	int median_kernel = 3;
	Mat median_out;
	medianBlur(erode_out, median_out, 3);
	//imshow("Median Filter", median_out);

	//dilate to smooth final before edge detection
	cout << " Begin to Smooth with Dilate" << endl;
	Mat dilate_out;
	Mat dilate_kernel(3, 3, CV_8UC1);
	dilate(median_out, dilate_out, dilate_kernel);
	//imshow("Dilate", dilate_out);

	return dilate_out;
}

int main()
{
	Mat source;
	Mat src_proc;
	source = imread("dataset4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Original Image", source);
	
	//Ver.2
	src_proc = preProcSequence(source);
	imshow("Pre-Processed Image", src_proc);

	waitKey(0);

	return 0;
}