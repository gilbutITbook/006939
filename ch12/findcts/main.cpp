#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언
void contours_basic();
void contours_hier();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	contours_basic();
	contours_hier();

	return 0;
}

// 외곽선 검출과 그리기
void contours_basic()
{
	// contours.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<vector<Point>> contours;	// 컨투어 벡터 생성 
	// 하나의 컨투어에 여러 좌표를 담아야 하므로 vector<Point>, 컨투어가 여러개 있으므로 vector<vector<Point>>
	
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);	// 영상 내부의 외곽선 검출 수행
	// (입력 영상(8비트 1채널, 0이 아닌 픽셀을 객체로 취급), 검출된 외곽선 정보,
	// 외곽선 계층 정보(객체 바깥쪽과 안쪽 외곽선 모두 검색, 계층 구조 X),
	// 모드(모든 외곽선 점들의 좌표를 저장))

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);	// GrayScale을 3채널 Color 영상으로 변환

	for (int i = 0; i < contours.size(); i++) {
		Scalar c(rand() & 255, rand() & 255, rand() & 255);		// 임의의 컬러
		drawContours(dst, contours, i, c, 2);		// 외곽선 정보를 이용하여 그림 그리기
		// (외곽선을 그릴 영상, findCountours로 찾은 외곽 정보, 외곽선 번호(Index), 외곽선 색상, 외곽선 두께)	
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창을 소멸
}

// 계층 구조를 사용하는 외곽선 검출과 그리기
void contours_hier()
{
	// contours.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("contours.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<vector<Point> > contours;	// 컨투어 벡터 생성 
	// 하나의 컨투어에 여러 좌표를 담아야 하므로 vector<Point>, 컨투어가 여러개 있으므로 vector<vector<Point>>

	vector<Vec4i> hierarchy;	// 외곽선의 계층 구조 저장할 벡터 생성 (4개의 성분)
	// 0번째 성분 - 다음 외곽선 번호, 1번째 성분 - 이전 외곽선 번호, 2번째 성분 - 자식 외곽선 번호, 3번째 성분 - 부모 외곽선 번호 (없으면 -1 저장)
	
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);	// 영상 내부의 외곽선 검출 수행
	// (입력 영상(8비트 1채널, 0이 아닌 픽셀을 객체로 취급), 검출된 외곽선 정보,
	// 외곽선 계층 정보(모든 외곽선을 검색하고 2단계 계층 구조 구성),
	// 모드(외곽선 중에서 수평선, 수직선, 사선 성분은 끝점만 저장))

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);	// GrayScale을 3채널 Color 영상으로 변환

	for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {		// 0번 외곽선부터 계층 정보의 다음 외곽선으로 이동하면서 for문 수행
	
		Scalar c(rand() & 255, rand() & 255, rand() & 255);		// 임의의 컬러
		drawContours(dst, contours, idx, c, -1, LINE_8, hierarchy);		// 외곽선 정보를 이용하여 그림 그리기
		// (외곽선을 그릴 영상, findCountours로 찾은 외곽 정보, 외곽선 번호(Index), 외곽선 색상, 외곽선 내부 채움, 선 종류, 계층 정보)
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창을 소멸
}
