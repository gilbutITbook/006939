#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 히스토그램 역투영을 이용한 피부색 영역 검출 
int main()
{
	// Calculate CrCb histogram from a reference image

	Mat ref, ref_ycrcb, mask;
	ref = imread("ref.png", IMREAD_COLOR);  // 기준 영상을 3채널 BGR 이미지로 Mat 형태로 저장
	mask = imread("mask.bmp", IMREAD_GRAYSCALE);  // 마스크 영상을 3채널 BGR 이미지로 Mat 형태로 저장
	cvtColor(ref, ref_ycrcb, COLOR_BGR2YCrCb);	// BGR Color 영상에서 YCrCB 영상으로 변환

	// 기준 영상에서의 피부색 영역의 히스토그램을 계산하여 hist에 저장
	
	// calcHist() 전달할 인자를 생성
	Mat hist;
	int channels[] = { 1, 2 };
	int cr_bins = 128; int cb_bins = 128;
	int histSize[] = { cr_bins, cb_bins };
	float cr_range[] = { 0, 256 };
	float cb_range[] = { 0, 256 };
	const float* ranges[] = { cr_range, cb_range };

	calcHist(&ref_ycrcb, 1, channels, mask, hist, 2, histSize, ranges);
	// (입력 영상, 입력 영상의 갯수, 채널 번호들의 배열(Cr,Cb)), mask 영역 지정, 출력 히스토그램, 출력 히스토그램 차원 수, 히스토그램 bin 갯수, 차원의 범위 )

	// Apply histogram backprojection to an input image

	Mat src, src_ycrcb;
	src = imread("kids.png", IMREAD_COLOR);
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	Mat backproj;
	calcBackProject(&src_ycrcb, 1, channels, hist, backproj, ranges, 1, true);	// 히스토그램 역투행 수행
	// (입력 영상, 입력 영상의 갯수, 역투영 계산시 사용할 채널 번호 배열, 입력 히스토그램, 출력 히스토그램, 차원의 bin 범위, 결과 히스토그램에 곱할 것, bin이 균등하게 이루어져 있는지 보는 flag)
	
	// 이미지 출력
	imshow("src", src);
	imshow("backproj", backproj);
	waitKey(0);			// 키 입력을 기다리는 함수

	return 0;			
}
