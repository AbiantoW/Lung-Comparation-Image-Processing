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

int main()
{
	Mat source;
	source = imread("dataset1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Original Image", source);
	/*
	//Penggunaan Gabor Filter
	
	Mat gabor_kernel;
	Mat gabor_out;
	int kernel_size = 31;	//fixed
	double sig = 1.0, th = 3, lm = 2, gm = 2, ps = CV_PI*0.46;
	gabor_kernel = getGaborKernel( CvSize( kernel_size, kernel_size), sig, th, lm, gm, ps,CV_32F);
	filter2D(source, gabor_out, CV_32F, gabor_kernel);

	
	//Median Filter
	
	Mat gabor_new;
	gabor_out.convertTo(gabor_new, CV_8U); //convert depth ke 8Unsigned
	int median_kernelsize = 7;
	Mat median_out;
	medianBlur(gabor_new, median_out, median_kernelsize);
	median_out.convertTo(median_out, CV_32F);	
	

	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", source);

	namedWindow("Gabor Filter", WINDOW_AUTOSIZE);
	imshow("Gabor Filter", gabor_out);

	namedWindow("Median Filter", WINDOW_AUTOSIZE);
	imshow("Median Filter", median_out);
	*/
	
	//Ver.2
	//pre-processing

	//bitplane slicing
	Mat bitplane8(((source / (1 << 8)) & 1) * 255);
	imshow("Bit Plane Slicing 8", bitplane8);
	
	//erode
	Mat	erode_out;
	Mat erode_kernel(15,15,CV_8UC1);
	erode(bitplane8, erode_out, erode_kernel);
	imshow("Erode", erode_out);

	//median
	int median_kernel = 3;
	Mat median_out;
	medianBlur(erode_out, median_out, 3);
	imshow("Median Filter", median_out);

	//dilate to smooth final before edge detection
	Mat dilate_out;
	Mat dilate_kernel(3, 3, CV_8UC1);
	dilate(median_out, dilate_out, dilate_kernel);
	imshow("Dilate", dilate_out);

	//finding edges
	//Mat edge;
	//Canny(dilate_out, edge, 0, 100);
	//imshow("Lung Edge", edge);
	//cout << dilate_out;


	waitKey(0);

	return 0;
}