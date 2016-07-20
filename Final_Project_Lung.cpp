/*  
	Final project "Lung Cancer Detection"
	Mata Kuliah Pengolahan Citra
	Abianto Wibisono 00000007344 - Teknik Informatika UPH 2014
    Sherwin			 00000006001 - Teknik Informatika UPH 2014 
	**********************************************************
	Current Version : Ver.1.2.0
	Ver.1.0.0		: Initial code
	Ver.1.1.0		: Pre-processing code complete
	Ver.1.1.1		: Pre-processing compiled into 1 function
	Ver.1.2.0		: New Method for calculating black pixels + logical comparation
*/

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

//Method untuk menghitung jumlah pixel yang bernilai 0.
int calculateZeroPixels(Mat src)
{
	int TotalNumberOfPixels = src.rows * src.cols;
	int ZeroPixels = TotalNumberOfPixels - countNonZero(src);
	
	return ZeroPixels;
}

int main()
{
	Mat source, source2, src_proc, src_proc2, result;
	source = imread("dataset3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Normal Lung", source);

	source2 = imread("dataset4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Lung to Compare", source2);
	//experimental convert
	
	//Ver.2
	src_proc = preProcSequence(source);
	imshow("Pre-Processed Normal Lung", src_proc);

	src_proc2 = preProcSequence(source2);
	imshow("Pre-Processed Lung to Compare", src_proc2);
	//cout << src_proc2;

	// Comparation Proccess
	int ZeroPixelsGuide = calculateZeroPixels(src_proc);
	cout << " Number of Black in Picture Guide: " << ZeroPixelsGuide << endl;

	int ZeroPixelsComp = calculateZeroPixels(src_proc2);
	cout << " Number of Black in Analyzed Picture: " << ZeroPixelsComp << endl;

	cout << " " << ZeroPixelsGuide << " Black Pixels in Base Picture Compared to " 
		 << " " << ZeroPixelsComp << " Black Pixels in Analyzed Picture" << endl;

	if (ZeroPixelsComp < ZeroPixelsGuide) 
	{
		cout << " Maligant ";
	}
	else cout << " Normal ";


	waitKey(0);
	return 0;
}