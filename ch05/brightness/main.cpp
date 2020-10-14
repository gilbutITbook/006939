#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
void brightness1();
void brightness2();
void brightness3();
void brightness4();
void on_brightness(int pos, void* userdata);

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	brightness1();
	brightness2();
	brightness3();
	brightness4();

	return 0;
}

// 단순히 이미지의 밝기를 증가시키는 예제
void brightness1()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 모든 픽셀 value를 100씩 증가
	// 만약 연산 결과가 255보다 클 경우 자동적으로 255로 저장 
	Mat dst = src + 100;

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);
	waitKey();            // 키 입력을 기다리는 함수 

	destroyAllWindows();  // 모든 창이 소멸
}

// 직접 픽셀 value를 참조하면서 밝기를 증가시키는 예제
void brightness2()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 입력 영상과 동일한 결과 영상을 미리 생성 및 선언
	// 단순히 Mat dst;로 만들고 픽셀 value를 .at()으로 참조하려 하면 안됨
	Mat dst(src.rows, src.cols, src.type());

	// 영상 전체를 직접 스캔하면서 영상의 픽셀 value 직접 설정
	// uchar 자료형은 255가 넘어가면 0으로 초기화 
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);
	waitKey();            // 키 입력을 기다리는 함수

	destroyAllWindows();  // 모든 창이 소멸
}

// 포화 연산을 고려한 영상의 밝기 증가 직접 구현
void brightness3()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 입력 영상과 동일한 결과 영상을 미리 생성 및 선언
	Mat dst(src.rows, src.cols, src.type());

	// 영상 전체를 직접 스캔하면서 영상의 픽셀 value 직접 설정
	// saturate_cast() 함수를 이용하여 포화 연산을 수행
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);
	waitKey();            // 키 입력을 기다리는 함수

	destroyAllWindows();  // 모든 창이 소멸
}

// 트랙바를 이용하여 영상의 밝기 조절하기
void brightness4()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	namedWindow("dst");    // dst라는 이름의 Window 생성
	// track bar 생성 (name, windowname, 트랙바 위치, 트랙바 최대 value, Callback 함수, 전달하고 싶은 데이터)
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	// 프로그램 실행시 영상이 정상적으로 출력 되도록 함수 호출
	on_brightness(0, (void*)&src);

	waitKey();            // 키 입력을 기다리는 함수
	destroyAllWindows();  // 모든 창이 소멸
}

void on_brightness(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}
