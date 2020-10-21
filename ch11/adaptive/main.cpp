#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void on_trackbar(int pos, void* userdata);

int main()
{
	// sudoku.jpg를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("sudoku.jpg", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);		// 이미지 출력

	namedWindow("dst");		// dst라는 이름의 Window 생성
	createTrackbar("Block Size", "dst", 0, 200, on_trackbar, (void*)&src);	// 트랙바 생성
	// track bar 생성 (name, windowname, 트랙바 위치, 트랙바 최대 value, Callback 함수, 전달하고 싶은 데이터)
	setTrackbarPos("Block Size", "dst", 11);	// 트랙바 value 지정
	// (트랙 바 이름, 윈도우 이름, 초기 value)

	waitKey(0);		// 키 입력을 기다리는 함수
	return 0;
}

void on_trackbar(int pos, void* userdata)
{
	// void type의 userdata를 Mat type으로 형변환 후, img 변수로 참조
	Mat src = *(Mat*)userdata;

	int bsize = pos;		// pos를 block의 크기를 결정하는데 사용
	if (bsize % 2 == 0) bsize--;	// 만약 짝수이면 -1 연산으로 홀수를 만들어 준다.
	if (bsize < 3) bsize = 3;		// 만약 3이하이면 3으로 만들어준다.

	Mat dst;
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 
					  bsize, 2);
	// (입력 영상, 출력 영상, 결과 영상의 Max value ,블록 평균 계산 방법, 이진화 방법, Threshold 계산시 사용하는 블록 크기, Threshold 조정을 위한 상수)

	imshow("dst", dst);		// 이미지 출력
}
