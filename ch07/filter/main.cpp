#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void filter_embossing();

int main(void)
{
	filter_embossing();

	return 0;
}

void filter_embossing()
{
	// rose.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 엠보싱 필터 (3x3) 32비트 1채널 마스크 생성  
	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	// filter2D 함수를 이용하여 엠보싱 필터 구현
	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);
	// (입력영상, 결과영상, 결과영상의 depth, 필터링할 커널, 고정점 좌표(대부분(-1,-1), 필터링 연산후 추가적으로 더할 pixel value)  

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}  
