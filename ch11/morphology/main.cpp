#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void erode_dilate();
void open_close();

// 주석을 이용하여 원하는 부분 출력
int main(void)
{
	erode_dilate();
	open_close();

	return 0;
}

// 이진 영상의 침식과 팽창
void erode_dilate()
{
	// milkdrop.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);  // 이진화 수행
	//(입력 영상, 결과 영상, Threshold, Max Value, 연산 방법(Otsu Algorithm 적용))

	Mat dst1, dst2;
	erode(bin, dst1, Mat());	// 침식 연산
	dilate(bin, dst2, Mat());	// 팽창 연산
	// (입력 영상, 출력 영상, 구조 요소(3x3))
	// 구조 요소 - 모폴로지 연산의 동작을 결정하는 작은 크기의 행렬

	// 이미지 출력
	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();		// 키 입력을 기다리는 함수
	destroyAllWindows();		// 모든 창을 소멸
}

// 이진 영상의 열기와 닫기
void open_close()
{
	// milkdrop.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("milkdrop.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);	// 이진화 수행
	//(입력 영상, 결과 영상, Threshold, Max Value, 연산 방법(Otsu Algorithm 적용))

	Mat dst1, dst2;
	morphologyEx(bin, dst1, MORPH_OPEN, Mat());		// Opening 연산
	morphologyEx(bin, dst2, MORPH_CLOSE, Mat());	// Closing 연산
	// (입력 영상, 출력 영상, 모폴로지 연산 타입 ,구조 요소(3x3))

	// 이미지 출력
	imshow("src", src);
	imshow("bin", bin);
	imshow("opening", dst1);
	imshow("closing", dst2);

	waitKey();		// 키 입력을 기다리는 함수
	destroyAllWindows();		// 모든 창을 소멸
}
