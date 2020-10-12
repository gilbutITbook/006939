#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat img;
Point ptOld;
void on_mouse(int event, int x, int y, int flags, void*);    // 마우스 콜백 함수

int main(void)
{
	// lenna.bmp를 img 객체에 저장
	img = imread("lenna.bmp");

	// 이미지가 잘 불러와 졌는지 확인
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	
	namedWindow("img");                 // img라는 window 생성
	setMouseCallback("img", on_mouse);  // img라는 window에 마우스 콜백 함수 등록

	imshow("img", img);                 // img 영상 출력
	waitKey();							// 키 입력 기다리기

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
	case EVENT_LBUTTONDOWN:    // 마우스의 왼쪽 버튼을 누른 경우
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN: " << x << ", " << y << endl;  // 좌표 출력
		break;
	case EVENT_LBUTTONUP:     // 마우스의 왼쪽 버튼을 떼는 경우
		cout << "EVENT_LBUTTONUP: " << x << ", " << y << endl;    // 좌표 출력
		break;
	case EVENT_MOUSEMOVE:     // 마우스의 왼쪽 버튼을 계속 누르고 있을 때
		if (flags & EVENT_FLAG_LBUTTON) {
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2); // 입출력 이미지, pt1에서 pt2까지, Yellow, Thickness = 2
			imshow("img", img);       // img 영상 출력
			ptOld = Point(x, y);      // 직선을 그리고 난 후, 현재 위치로 ptOld를 Update
		}
		break;
	default:
		break;
	}
}
