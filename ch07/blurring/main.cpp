#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
void blurring_mean();
void blurring_gaussian();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	blurring_mean();
	blurring_gaussian();

	return 0;
}

// 평균 필터 마스크를 이용한 Blurring
void blurring_mean()
{
	// rose.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 이미지 출력
	imshow("src", src);

	// 결과 영상 생성
	Mat dst;
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		// 마스크의 크기가 (ksize x ksize)인 평균 필터 마스크를 수행하여 dst에 저장
		blur(src, dst, Size(ksize, ksize));

		// 사용된 평균 필터 마스크의 크기를 문자열 형태로 화면에 출력
		String desc = format("Mean: %dx%d", ksize, ksize);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, 
				Scalar(255), 1, LINE_AA);
		
		// 이미지 출력
		imshow("dst", dst);
		waitKey();           // 키 입력을 기다리는 함수
	}	

	destroyAllWindows();     // 모든 창이 소멸
}

// 가우시안 필터 마스크를 이용한 Blurring
void blurring_gaussian()
{
	// rose.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 이미지 출력
	imshow("src", src);

	// 결과 영상 생성
	Mat dst;
	for (int sigma = 1; sigma <= 5; sigma++) {
		// sigma 수를 변경해가며 가우시안 필터링 수행
		// (원본 영상, 결과 영상, 가우시안 커널 크기, sigma)
		GaussianBlur(src, dst, Size(), (double)sigma);

		// 사용한 가우시안 sigma를 화면에 출력
		String desc = format("Gaussian: sigma = %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, 
				Scalar(255), 1, LINE_AA);
		
		// 이미지 출력
		imshow("dst", dst);
		waitKey();           // 키 입력을 기다리는 함수
	}

	destroyAllWindows();     // 모든 창이 소멸
}
