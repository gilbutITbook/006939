#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 영상에서 외곽선 주변에 Bounding Box를 그리고 Label 문자열 출력
void setLabel(Mat& img, const vector<Point>& pts, const String& label)
{
	Rect rc = boundingRect(pts);	// 주어진 외곽선 점들을 포괄하는 가장 작은 Rectangle
	rectangle(img, rc, Scalar(0, 0, 255), 1);	// Rectangle을 그리는 함수 (입출력 이미지, 좌표, Red, Thickness = 1)
	putText(img, label, rc.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	// 다양한 Pont의 문자열 출력 (입출력 이미지, 문자열, 시작점, 폰트, Thickness, Color(B,G,R)- Red)
}

// Polygon 검출 및 인식 예제
int main(int argc, char* argv[])
{
	// polygon.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat img = imread("polygon.bmp", IMREAD_COLOR);

	// 이미지를 잘 불러왔는지 확인
	if (img.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);	// 3채널 Color 영상을 GrayScale로 변환

	Mat bin;
	threshold(gray, bin, 200, 255, THRESH_BINARY_INV | THRESH_OTSU);

	vector<vector<Point>> contours;		// 컨투어 벡터 생성 
	// 하나의 컨투어에 여러 좌표를 담아야 하므로 vector<Point>, 컨투어가 여러개 있으므로 vector<vector<Point>>

	findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);		// 영상 내부의 외곽선 검출 수행
	// (입력 영상(8비트 1채널, 0이 아닌 픽셀을 객체로 취급), 검출된 외곽선 정보,
	// 외곽선 계층 정보(모든 외곽선을 검색하고 2단계 계층 구조 구성),
	// 모드(외곽선 중에서 수평선, 수직선, 사선 성분은 끝점만 저장))

	// 범위 기반 반복문 사용, contours 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
	for (vector<Point> pts : contours) {
		if (contourArea(pts) < 400)	// 외곽선을 포괄하는 면적이 400이 안되면 무시
			continue;

		vector<Point> approx;
		approxPolyDP(pts, approx, arcLength(pts, true)*0.02, true);	// 곡선 또는 Polygon을 단순화
		// (입력 2차원 좌표, 근사화된 출력 좌표, 근사화 정밀도 파라미터(입력 곡선과 근사화 곡선의 최대거리), 폐곡선 여부)

		int vtc = (int)approx.size();	// 외곽선 점의 갯수를 저장

		if (vtc == 3) {	// 외곽선 꼭지점의 갯수가 3이면
			setLabel(img, pts, "TRI");	// 해당 도형의 이름 문자열 표시 (위에서 선언한 함수)
		} else if (vtc == 4) { 	// 외곽선 꼭지점의 갯수가 4이면
			setLabel(img, pts, "RECT"); // 해당 도형의 이름 문자열 표시 (위에서 선언한 함수)
		} else {
			double len = arcLength(pts, true);
			double area = contourArea(pts);
			double ratio = 4. * CV_PI * area / (len * len);	// 외곽선 모양이 원에 가까운 형태인지 판단, 1에 가까울수록 원 모양

			if (ratio > 0.85) {		// 비율이 0.85 이상이면
				setLabel(img, pts, "CIR");	// 원이라고 판단 후 도형의 이름 문자열 표시 (위에서 선언한 함수)
			}
		}
	}

	imshow("img", img);		// 이미지 출력

	waitKey(0);		// 키 입력을 기다리는 함수
	return 0;
}