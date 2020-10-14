#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
void contrast1();
void contrast2();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	contrast1();
	contrast2();

	return 0;
}

// 기본적인 영상의 명암비 증가 예제
// 전체적으로 픽셀 value가 포화상태를 이루어 실제로는 잘 사용하지 않음
void contrast1()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 입력 영상의 모든 픽셀 value에 2.0를 곱하여 결과 영상을 생성
	float s = 2.f;
	Mat dst = s * src;

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);
	waitKey();            // 키 입력을 기다리는 함수 

	destroyAllWindows();  // 모든 창이 소멸
}

// 효과적인 영상의 명암비 조절 방법
// 기준 value를 128로 설정하여 128보다 크면 더 밝게 128보다 작으면 더 어둡게 만든다.
void contrast2()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 효과적인 명암비를 증가시켜 결과 영상을 생성
	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);
	waitKey();             // 키 입력을 기다리는 함수

	destroyAllWindows();   // 모든 창이 소멸
}
