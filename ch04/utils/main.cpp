#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void mask_setTo();
void mask_copyTo();
void time_inverse();
void useful_func();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	mask_setTo();
	mask_copyTo();
	time_inverse();
	useful_func();

	return 0;
}

// Mask Image를 이용하여 픽셀 Value 설정
void mask_setTo()
{
	Mat src = imread("lenna.bmp", IMREAD_COLOR);  // lenna.bmp를 RGB 영상으로 Mat에 저장
	Mat mask = imread("mask_smile.bmp", IMREAD_GRAYSCALE);  // mask_smile.bmp를 GrayScale로 Mat에 저장

	// 영상이 잘 받아졌는지 확인
	if (src.empty() || mask.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// (Yellow, Mask 행렬) - 0이 아닌 부분에서만 Yellow로 색 설정
	src.setTo(Scalar(0, 255, 255), mask);

	// 영상 출력
	imshow("src", src);
	imshow("mask", mask);

	waitKey(0);           // 키 입력을 기다리는 함수
	destroyAllWindows();  // 모든 창이 소멸
}

// Mask Image를 이용하여 픽셀 Value 일부분 복사
void mask_copyTo()
{
	Mat src = imread("airplane.bmp", IMREAD_COLOR);         // airplane.bmp를 RGB 영상으로 Mat에 저장
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);  // mask_plane.bmp를 GrayScale 영상으로 Mat에 저장
	Mat dst = imread("field.bmp", IMREAD_COLOR);		    // field.bmp를 RGB 영상으로 Mat에 저장

	// 영상이 잘 받아졌는지 확인
	if (src.empty() || mask.empty() || dst.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Mask Image에서 0이 아닌 부분만 src 영상이 dst 영상으로 복사
	// (목표 Mat, Mask 행렬)
	src.copyTo(dst, mask);

	// 영상 출력
	imshow("src", src);
	imshow("dst", dst);
	imshow("mask", mask);

	waitKey(0); 		  // 키 입력을 기다리는 함수
	destroyAllWindows();  // 모든 창이 소멸
}

// 연산 Time 측정 
void time_inverse()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);   // lenna.bmp를 GrayScale 영상으로 Mat에 저장

	// 영상이 잘 받아졌는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// src와 동일하도록 복사
	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start();    // Time 측정을 시작

	// 모든 픽셀을 반전시키는 작업
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop();    // Time 측정을 끝냄
	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;  // 측정한 Time을 콘솔 창에 출력

	// 영상 출력
	imshow("src",src);
	imshow("dst",dst);

	waitKey();              // 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// Sum, mean, minMaxLoc, normalize, cvRound functions Example
void useful_func()
{
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);  // lenna.bmp를 GrayScale 영상으로 Mat에 저장

	cout << "Sum: " << (int)sum(img)[0] << endl;      // 첫번째 원소에 모든 픽셀의 합 저장 (3채널일 경우, B G R) 
	cout << "Mean: " << (int)mean(img)[0] << endl;    // 첫번째 원소에 모든 픽셀의 평균 저장 (3채널일 경우, B G R)

	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);  // 입력 영상(단일 채널), Min Value, Max Value, Min Value 좌표, Max Value 좌표 
	// Max Value, Min Value 그에 대한 좌표까지 알 수 있는 함수

	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;

	// Mat src = Mat_<float>({ 1, 5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });
	// OpenCV 4.0부터 사용가능
	Mat src = (Mat_<float>( 1, 5 ) << -1.f, -0.5f, 0.f, 0.5f, 1.f );
	// -1 ~ 1 사이의 실수로 구성된 (1x5) 행렬

	Mat dst;
	normalize(src, dst, 0, 255 ,NORM_MINMAX, CV_8UC1);
	// 행렬의 norm을 정규화 하거나 원소 Value의 범위로 정규화할 때 사용하는 함수
	// (입력 Mat , 출력 Mat, min Value, max Value, NORM_TYPE, 결과 영상 타입)

	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;

	// cvRound - 실수를 반올림하여 정수를 만들어주는 함수
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.4999): " << cvRound(3.4999) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
}