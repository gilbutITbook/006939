#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 선언
void on_level_change(int pos, void* userdata);

int main(void)
{
	// (400 x 400) 1채널의 Mat 생성
	Mat img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");   // image라는 이름의 window 생성
	// track bar 생성 (name, windowname, 트랙바 위치, 트랙바 최대 value, Callback 함수, 전달하고 싶은 데이터)
	createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img);
	
	imshow("image", img);   // 영상 출력
	waitKey();				// 키 입력을 기다리는 함수  

	return 0;
}

// Track bar Call back function
// 
void on_level_change(int pos, void* userdata)
{
	// void type의 userdata를 Mat type으로 형변환 후, img 변수로 참조
	Mat img = *(Mat*)userdata;

	img.setTo(pos * 16);    // (트랙바의 value * 16)으로 이미지의 픽셀 value로 설정
	imshow("image", img);   // 영상 출력
}
