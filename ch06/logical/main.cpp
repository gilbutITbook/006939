#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 영상의 논리 연산
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
	
	// 영상의 논리 연산 수행
	// 하나의 픽셀을 8개의 비트로 만들고 비트 단위에서 논리 연산을 수행 후 다시 십진수로 변환
	bitwise_and(src1, src2, dst1);   // dst1 = src1 & src2 (AND 연산 수행)
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)
	bitwise_or(src1, src2, dst2);    // dst2 = src1 | src2 (OR 연산 수행)
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)
	bitwise_xor(src1, src2, dst3);   // dst3 = src1 ^ src2 (XOR 연산 수행)
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)
	bitwise_not(src1, dst4);         // dst4 = ~src1 (부정 연산 수행)
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치)

	// 이미지 출력
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);
	imshow("dst4", dst4);
	waitKey();				 // 키 입력을 기다리는 함수

	return 0;
}
