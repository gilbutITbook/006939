#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void sobel_derivative();
void sobel_edge();
void canny_edge();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	sobel_derivative();
	sobel_edge();
	canny_edge();

	return 0;
}

// 기본적인 미분 연산 Mask 기반 엣지 검출 Example
void sobel_derivative()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	//Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });  // OpenCV 4.0부터 사용 가능
	Mat mx = (Mat_<float>( 1, 3 ) <<  -1 / 2.f, 0, 1 / 2.f );
	// x축 편미분을 수행하는 (1x3) Mask 생성

	//Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });  // OpenCV 4.0부터 사용 가능
	Mat my = (Mat_<float>( 3, 1 ) << -1 / 2.f, 0, 1 / 2.f );
	// y축 편미분을 수행하는 (3x1) Mask 생성

	//결과 영상 생성
	Mat dx, dy;
	filter2D(src, dx, -1, mx, Point(-1, -1), 128);
	filter2D(src, dy, -1, my, Point(-1, -1), 128);
	// (입력 영상, 결과 영상, 결과영상의 depth, 필터링할 커널, 고정점 좌표(대부분(-1,-1), 필터링 연산후 추가적으로 더할 pixel value) 

	// 이미지 출력
	imshow("src", src);
	imshow("dx", dx);
	imshow("dy", dy);

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// Sobel Mask 기반 엣지 검출 Example
void sobel_edge()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 미분 영상 생성
	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);  // Sobel 연산 이용
	Sobel(src, dy, CV_32FC1, 0, 1);  // Sobel 연산 이용
	// (입력 영상, 결과 영상, 결과 영상 type, x 방향 미분 차수, y 방향 미분 차수)

	
	Mat fmag, mag;
	magnitude(dx, dy, fmag);  //  dx 행렬과 dy 행렬의 gradient 크기를 계산하여 fmag에 저장 (Input X, Input Y, Output)
	fmag.convertTo(mag, CV_8UC1);  // fmag Array를 Grayscale형식으로 변환하여 mag에 저장

	Mat edge = mag > 150;  // Threshold를 150으로 설정하여 150보다 크면 255, 작으면 0으로 pixel value 설정

	// 이미지 출력
	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();	// 모든 창이 소멸
}

void canny_edge()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 결과 영상 생성
	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);   // 케니 엣지 검출기 적용
	Canny(src, dst2, 50, 150);
	// (원본 영상, 결과 영상, 최소 Threshold, 최대 Threshold)

	// 이미지 출력
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();	// 모든 창이 소멸
}