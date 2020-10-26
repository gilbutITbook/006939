#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void corner_harris();
void corner_fast();

// 주석을 이용하여 원하는 부분 출력
int main(void)
{
	corner_harris();
	corner_fast();

	return 0;
}

// Harris Corner 검출 예제
void corner_harris()
{
	// building.jpg를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat harris;
	cornerHarris(src, harris, 3, 3, 0.04);	// 해리스 코너 응답 함수 행렬
	// (입력 영상, 결과를 저장할 행렬, 윈도우 크기 설정, Sobel 연산을 위한 커널 크기, 해리스 코너 검출 상수)

	Mat harris_norm;
	normalize(harris, harris_norm, 0, 255, NORM_MINMAX, CV_8U);	// 해리스 코너 응답 함수 분포를 영상으로 나타내기 위한 정규화
	// (입력 Mat , 출력 Mat, min Value, max Value, NORM_TYPE, 결과 영상 타입)

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);	// 영상을 3채널 Color 영상으로 바꾸어 저장

	// Simple Non Maximum Suppression 수행
	for (int j = 1; j < harris.rows - 1; j++) {
		for (int i = 1; i < harris.cols - 1; i++) {
			if (harris_norm.at<uchar>(j, i) > 120) {	// 120보다 큰 value만 코너로 인식
				if (harris.at<float>(j, i) > harris.at<float>(j - 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j + 1, i) &&
					harris.at<float>(j, i) > harris.at<float>(j, i - 1) &&
					harris.at<float>(j, i) > harris.at<float>(j, i + 1) ) 	// 주변 인접한 네 pixel과 비교하여 최대인 경우만 수행
					{
					circle(dst, Point(i, j), 5, Scalar(0, 0, 255), 2);	// Circle을 그리는 함수
					// 입출력 이미지, 중심점, 반지름, Blue, Thickness = 3, 안티에일리어싱
				}
			}
		}
	}

	// 이미지 출력
	imshow("src", src);
	imshow("harris_norm", harris_norm);
	imshow("dst", dst);

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}

// FAST Corner 검출 예제
void corner_fast()
{
	// building.jpg를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<KeyPoint> keypoints;	// 코너 점 좌표를 저장할 Vector 생성
	FAST(src, keypoints, 60, true);	// FAST corner 검출 방법 구현
	// (입력 영상, 검출된 특징점, 중심 픽셀과 주변 픽셀 차이의 Threshold, NMS(Non Maximum Suppression) 수행 여부)

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);	// 영상을 3채널 Color 영상으로 바꾸어 저장

	// 범위 기반 반복문 사용, keypoints 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용 
	for (KeyPoint kp : keypoints) {
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y));	// 중심점 추출
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);	// Circle을 그리는 함수
		// 입출력 이미지, 중심점, 반지름, Red, Thickness = 2
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}

