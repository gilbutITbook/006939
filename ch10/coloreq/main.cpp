#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 컬러 영상의 히스토그램 평활화 Example
int main(void)
{
	// pepper.bmp를 3채널 BGR Color 이미지로 Mat 형태로 저장
	Mat src = imread("pepper.bmp", IMREAD_COLOR);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);  // BGR color 영상을 YCrCb 영상으로 변환

	vector<Mat> ycrcb_planes;			// YCrCb 영상을 한 채널씩 담을 백터 생성
	split(src_ycrcb, ycrcb_planes);		// (입력 다채널 채널, 분리된 행렬을 저장할 벡터)

	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); // Y channel
	// 히스토그램 평활화 수행 후 결과 영상에 저장 (입력 영상, 결과 영상)

	Mat dst_ycrcb;						// 세 채널을 담을 결과 영상 생성
	merge(ycrcb_planes, dst_ycrcb);		// y_crcb_planes 벡터에 들어있는 세 영상을 합쳐 dst_ycrcb에 저장

	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);	// YCrCb 영상을 BGR Color 영상으로 변환

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);		// 키 입력을 기다리는 함수
	return 0;			// 모든 창이 소멸
}