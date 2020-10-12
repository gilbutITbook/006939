#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	// lenna.bmp를 img 변수에 저장
	Mat img = imread("lenna.bmp");

	// 이미지가 잘 불러졌나 확인
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("img");     // img라는 문자열을 제목으로 가지는 window 생성
	imshow("img", img);     // img 영상 출력

	while (true) {
		// 키 입력을 기다리기 위해 watiKey() 사용 - 아스키 코드
		int keycode = waitKey();
		
		// i or I가 입력이 되면 이미지를 반전 시킨다.
		if (keycode == 'i' || keycode == 'I') {
			img = ~img;
			imshow("img", img);
		}

		// ESC, q, Q가 입력이 되면 종료한다.  (왼쪽 화살표도 종료된다)
		else if (keycode == 27 || keycode == 'q' || keycode == 'Q') {
			break;
		}
	
	}

	return 0;
}
