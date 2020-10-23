#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void template_matching();

// 템플릿 매칭 사용 예제
int main()
{
	template_matching();

	return 0;
}

void template_matching()
{
	// circuit.bmp, crystal.bmp를 3 채널 Color 이미지로 Mat 형태로 저장
	Mat img = imread("circuit.bmp", IMREAD_COLOR);
	Mat templ = imread("crystal.bmp", IMREAD_COLOR);

	// 이미지를 잘 불러왔는지 확인
	if (img.empty() || templ.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	img = img + Scalar(50, 50, 50);	// 입력 영상 밝기를 50 증가

	Mat noise(img.size(), CV_32SC3);	// 노이즈 행렬 생성
	randn(noise, 0, 10);	//(입출력 영상, 가우시안 분포 평균, 가우시안 분포 표준편차)
	add(img, noise, img, Mat(), CV_8UC3);	// 영상의 덧셈을 이용하여 결과 영상 생성
	// (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치, 마스크 행렬, 출력 행렬 깊이)

	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);	// 템플릿 매칭 수행
	// (입력 영상, 템플릿 영상, 비교 결과를 저장할 행렬, 템플릿 매칭 비교 방법(정규화된 상관계수 매칭))

	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);
	// 행렬의 norm을 정규화 하거나 원소 Value의 범위로 정규화할 때 사용하는 함수
	// (입력 Mat , 출력 Mat, min Value, max Value, NORM_TYPE, 결과 영상 타입)

	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);	// res 영상의 max value를 maxv에 max value location을 maxloc에 저장
	cout << "maxv: " << maxv << endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);	// Rectangle 그리는 함수
	// (입출력 이미지, (x시작점, y시작점, 열(width), 행(height) , Red, Thickness = 2)

	// 이미지 출력
	imshow("templ", templ);
	imshow("res_norm", res_norm);
	imshow("img", img);

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}
