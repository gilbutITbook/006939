#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 영상의 산술 연산
int main(void)
{
	// lenna256.bmp를 GrayScale 이미지로 Mat 형태로 저장
	// square.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src1 = imread("lenna256.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("square.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// 이미지 출력
	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst1, dst2, dst3, dst4;

	// 영상의 산술 연산 수행
	// 포화연산을 수행해야 정확한 산술 연산이 수행 가능
	add(src1, src2, dst1);  // 두 영상의 덧셈 연산 수행
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)
	addWeighted(src1, 0.5, src2, 0.5, 0, dst2); // 두 영상의 가중치 합 구하기
	// (입력영상1, 가중치1, 입력영상2, 가중치2, Gamma, 결과영상)
	subtract(src1, src2, dst3);  // 두 영상의 뺄셈 연산 수행 - 순서에 영향을 받는다.
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)
	absdiff(src1, src2, dst4);   // 순서에 영향을 받지 않는 두 영상의 차영상 구하기
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)

	// 이미지 출력
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();              // 키 입력을 기다리는 함수

	return 0;
}
