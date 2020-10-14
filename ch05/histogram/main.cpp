#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
Mat calcGrayHist(const Mat& img);
Mat getGrayHistImage(const Mat& hist);

void histgoram_stretching();
void histgoram_equalization();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	histgoram_stretching();
	histgoram_equalization();

	return 0;
}

// GrayScale 영상의 히스토그램 구하기
Mat calcGrayHist(const Mat& img)
{
	// img가 GrayScale이 맞는지 검사
	CV_Assert(img.type() == CV_8UC1);

	// calcHist() 전달할 인자를 생성
	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };

	// (입력영상, 입력영상의 갯수, 채널 번호들의 배열(B,G,R 순서), mask 영역 지정, 출력 히스토그램, 출력 히스토그램 차원 수, 히스토그램 bin 갯수, 차원의 범위 )
	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}

// GrayScale 영상의 히스토그램 그래프 그리기
Mat getGrayHistImage(const Mat& hist)
{
	// hist가 1차원의 256개의 bin으로 구성된 행렬인지 검사
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	// 히스토그램 Max Value 저장
	double histMax;
	minMaxLoc(hist, 0, &histMax);

	// (256x100) 크기의 흰 색으로 초기화된 Mat 생성
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));

	// line()함수를 이용하여 bin에 대한 그래프 그리기
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

// 히스토그램 스트레칭 구현 -> min max 정규화하는 느낌
void histgoram_stretching()
{
	// hawkes.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 입력영상의 min, max value를 저장
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);

	// 히스토그램 스트레칭 수식을 결과 영상에 적용
	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	// 이미지, 히스토그램 출력
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();             // 키 입력을 기다리는 함수
	destroyAllWindows();   // 모든 창이 소멸
}

// 히스토그램 평활화 구현
void histgoram_equalization()
{
	// hawkes.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 히스토그램 평활화 수행 후 결과 영상에 저장
	Mat dst;
	equalizeHist(src, dst);

	// 이미지, 히스토그램 출력
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey(); 			   // 키 입력을 기다리는 함수
	destroyAllWindows();   // 모든 창이 소멸
}