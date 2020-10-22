#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void labeling_basic();
void labeling_stats();

// 주석을 이용하여 원하는 부분 출력
int main()
{
	labeling_basic();
	labeling_stats();

	return 0;
}

// 영상의 라벨링 예제
void labeling_basic()
{
	// Input으로 넣을 이진화를 마친 data 준비
	uchar data[] = {
		0, 0, 1, 1, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 1, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	Mat src = Mat(8, 8, CV_8UC1, data) * 255;	// Input 영상 생성 (8x8 1채널 GrayScale)

	Mat labels;
	int cnt = connectedComponents(src, labels);	// Labeling을 수행 , output : labeling의 갯수 (배경 포함)
	// (입력 영상, 출력 행렬, 연결성(default = 8))

	cout << "src:\n" << src << endl;	// Labeling 전 출력
	cout << "labels:\n" << labels << endl;	// Labeling 후 출력
	cout << "number of labels: " << cnt << endl;
}

// 라벨링을 이용하여  Bounding Box 그리기
void labeling_stats()
{
	// keyboard.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);	// 이진화 수행
	//(입력 영상, 결과 영상, Threshold, Max Value, 연산 방법(Otsu Algorithm 적용))

	Mat labels, stats, centroids;
	// label - labeling 결과를 담는 행렬
	// stats - 행: 배경 + labeling된 물체의 갯수, 열: Bounding Box 정보 (x,y,w,h) + 면적
	// centroids - 행: 배경 + labeling된 물체의 갯수, 열 : 무게 중심 x, y
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);	// 라벨링 Map과 물체의 정보 반환 , Output : labeling의 갯수 (배경 포함)

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);	// GrayScale 영상을 3채널 Color 영상으로 변환

	for (int i = 1; i < cnt; i++) {
		int* p = stats.ptr<int>(i);	// 물체 하나 당 Bounding Box 정보 (x,y,w,h) + 면적 
		
		if (p[4] < 20) continue;	// 객체의 면적이 20보다 작으면 무시

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255));	// Rectangle을 그리는 함수
		// (입출력 이미지, 좌표, Yellow)
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창을 소멸
}