#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int lower_hue = 40, upper_hue = 80;	// 트렉바 위치 초기화
Mat src, src_hsv, mask;

void on_hue_changed(int, void*);

int main(int argc, char* argv[])
{
	// candies.png를 3채널 BGR Color 이미지로 Mat 형태로 저장
	src = imread("candies.png", IMREAD_COLOR);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	cvtColor(src, src_hsv, COLOR_BGR2HSV);	// BGR color 영상을 YCrCb 영상으로 변환

	imshow("src", src);

	namedWindow("mask");		// mask라는 window 생성
	createTrackbar("Lower Hue", "mask", &lower_hue, 179, on_hue_changed);
	createTrackbar("Upper Hue", "mask", &upper_hue, 179, on_hue_changed);
	// 색상의 하한 value와 상한 value를 조절할 수 있는 트랙바 생성
	// track bar 생성 (name, windowname, 트랙바 위치, 트랙바 최대 value, Callback 함수, 전달하고 싶은 데이터)
	
	on_hue_changed(0, 0);		// 프로그램이 실행될 때 정상적인 출력을 위해 트랙바 콜벡 함수 호출

	waitKey(0);				// 키 입력을 기다리는 함수 
	return 0;
}

// Track bar Call back function
void on_hue_changed(int, void*)
{
	Scalar lowerb(lower_hue, 100, 0);		// (H,S,V) - 사용자 지정 채도, 100, 0으로 lowerb 생성
	Scalar upperb(upper_hue, 255, 255);		// (H,S,V) - 사용자 지정 채도, 255, 255으로 upperb 생성
	inRange(src_hsv, lowerb, upperb, mask);	// HSV 색상 범위가 lowerb부터 upperb인 픽셀만 흰색으로 설정한 mask 영상 생성
	// inRange() - 그 범위 안에 들어가면 0으로 만들어주고 나머지는 1로 만들어 흑백 사진을 만드는 함수

	// 이미지 출력
	imshow("mask", mask);
}
