#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위해 선언
void color_op();
void color_inverse();
void color_grayscale();
void color_split();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	color_op();
	color_inverse();
	color_grayscale();
	color_split();

	return 0;
}

// 컬러 영상의 픽셀 value 참조
void color_op()
{
	// butterfly.jpg를 3채널 BGR Color 이미지로 Mat 형태로 저장
	Mat img = imread("butterfly.jpg", IMREAD_COLOR);

	// 이미지를 잘 불러왔는지 확인
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Vec3b& pixel = img.at<Vec3b>(0, 0);	//(0,0)에 있는 픽셀 value 참조
	uchar b1 = pixel[0];				//픽셀 중 Blue 성분
	uchar g1 = pixel[1];				//픽셀 중 Green 성분
	uchar r1 = pixel[2];				//픽셀 중 Red 성분

	Vec3b* ptr = img.ptr<Vec3b>(0);		// 0번째 행 시작 픽셀 주소 가져오기
	uchar b2 = ptr[0][0];				// 0번째 행, 0번째 열 Blue 성분
	uchar g2 = ptr[0][1];				// 0번째 행, 0번째 열 Green 성분
	uchar r2 = ptr[0][2];				// 0번째 행, 0번째 열 Red 성분
}

// 컬러 영상의 픽셀 value 반전
void color_inverse()
{
	// butterfly.jpg를 3채널 BGR Color 이미지로 Mat 형태로 저장
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Mat dst = Scalar(255,255,255) - src;     // 모든 pixel value에 대해 반전(for문 이용할 필요 X)
	Mat dst(src.rows, src.cols, src.type());    // src와 동일한 dst 생성 (for문을 통해 픽셀 value 설정)

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			Vec3b& p1 = src.at<Vec3b>(j, i);	// (i,j)좌표에 있는 src pixel value
			Vec3b& p2 = dst.at<Vec3b>(j, i);	// (i,j)좌표에 있는 dst pixel value

			p2[0] = 255 - p1[0]; // B
			p2[1] = 255 - p1[1]; // G
			p2[2] = 255 - p1[2]; // R
		}
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();				// 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();	// 모든 창을 닫는다.
}

// Color 영상을 GrayScale 영상으로 변환
void color_grayscale()
{
	// butterfly.jpg를 3채널 BGR Color 이미지로 Mat 형태로 저장(default)
	Mat src = imread("butterfly.jpg");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY); //BGR Image를 GrayScale로 변환

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();				// 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();	// 모든 창을 닫는다.
}

// BGR 컬러 영상의 색상 채널 나누기
void color_split()
{
	// candies.jpg를 3채널 BGR Color 이미지로 Mat 형태로 저장(default)
	Mat src = imread("candies.png");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<Mat> bgr_planes;  	// 분리된 채널 영상을 담을 Mat Vector 생성
	split(src, bgr_planes);		// (입력 다채널 채널, 분리된 행렬을 저장할 벡터)

	// 이미지 출력
	imshow("src", src);
	imshow("B_plane", bgr_planes[0]);	// Blue channel
	imshow("G_plane", bgr_planes[1]);	// Green channel
	imshow("R_plane", bgr_planes[2]);	// Red channel

	waitKey();				// 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();	// 모든 창을 닫는다.
}