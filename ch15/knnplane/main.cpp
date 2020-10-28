#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

Mat img;
Mat train, label;
Ptr<KNearest> knn;
int k_value = 1;

// 함수 사용을 위해 미리 선언
void on_k_changed(int, void*);
void addPoint(const Point& pt, int cls);
void trainAndDisplay();

// kNN 알고리즘을 이용한 2차원 점 분류
int main(void)
{
	img = Mat::zeros(Size(500, 500), CV_8UC3);	// 크기가 (500x500)이고 3채널 Color, data는 0으로 채워진 Mat 생성
	knn = KNearest::create();	// KNearest 객체 생성, Output : KNearest 객체를 참조하는 Ptr 스마트 포인터 객체

	namedWindow("knn");	// knn이라는 이름을 가진 Window 생성
	createTrackbar("k", "knn", &k_value, 5, on_k_changed);	// k value를 조절할 수 있는 트랙바 생성
	// (name, windowname, 트랙바 위치, Call back 함수를 통해 전달 할 데이터, Max Value, Call back function)

	const int NUM = 30;
	Mat rn(NUM, 2, CV_32SC1);	// (2,30) 32비트 수, data는 garbage value인 Mat 생성 

	randn(rn, 0, 50);	// rn에 평균은 0 ,표준편차는 50을 따르는 가우시안 분포를 따르는 랜덤 데이터 생성
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 150, rn.at<int>(i, 1) + 150), 0);	// (150,150) 좌표를 중심으로 하는 0번 클래스

	randn(rn, 0, 50);	// rn에 평균은 0 ,표준편차는 50을 따르는 가우시안 분포를 따르는 랜덤 데이터 생성
	for (int i = 0; i < NUM; i++)
		addPoint(Point(rn.at<int>(i, 0) + 350, rn.at<int>(i, 1) + 150), 1);	// (350,150) 좌표를 중심으로 하는 1번 클래스

	randn(rn, 0, 70);	// rn에 평균은 0 ,표준편차는 70을 따르는 가우시안 분포를 따르는 랜덤 데이터 생성
	for (int i = 0; i < NUM; i++) 
		addPoint(Point(rn.at<int>(i, 0) + 250, rn.at<int>(i, 1) + 400), 2);	// (250,400) 좌표를 중심으로 하는 2번 클래스

	trainAndDisplay();	// train 및 window에 표시

	waitKey();		// 키 입력을 기다리는 함수
	return 0;
}

// Track Bar Call Function
void on_k_changed(int, void*)
{
	if (k_value < 1) k_value = 1;
	trainAndDisplay();
}

// 특정 좌표 pt를 cls 클래스로 등록
// Input : 특정 좌표 pt, Label value cls
void addPoint(const Point& pt, int cls)
{
	Mat new_sample = (Mat_<float>(1, 2) << pt.x, pt.y);
	train.push_back(new_sample);

	Mat new_label = (Mat_<int>(1, 1) << cls);
	label.push_back(new_label);
}

// kNN 알고리즘에 의한 학습과 img 영상 모든 좌표에서의 클래스 예측을 진행하고 그 결과를 knn 창에 표시
void trainAndDisplay()
{
	knn->train(train, ROW_SAMPLE, label);	// StatModel::train()을 이용하여 kNN 알고리즘 학습
	// (훈련 데이터 행렬, 훈련 데이터 배치 방법, 훈련 데이터에 대응되는 응답 레이블 행렬)

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {	// img의 모든 좌표에 대하여 조사
			Mat sample = (Mat_<float>(1, 2) << j, i);	// (2,1) 형태의 Mat 생성

			Mat res;

			knn->findNearest(sample, k_value, res);	// 훈련을 마친 후 테스트 데이터 예측
			// 하나의 샘플에 대해서만 findNearest를 수행, sample : (2,1), res : (1,1)
			// (테스트 데이터가 행 단위로 저장 된 행렬, 사용할 최근접 이웃 갯수, 입력 샘플에 대해 저장할 행렬)

			int response = cvRound(res.at<float>(0, 0));	// Label value를 response에 변수에 저장
			if (response == 0)
				img.at<Vec3b>(i, j) = Vec3b(128, 128, 255); // R
			else if (response == 1)
				img.at<Vec3b>(i, j) = Vec3b(128, 255, 128); // G
			else if (response == 2)
				img.at<Vec3b>(i, j) = Vec3b(255, 128, 128); // B
		}
	}

	for (int i = 0; i < train.rows; i++)	// 훈련 데이터 모든 원소에 대해 검사
	{
		int x = cvRound(train.at<float>(i, 0));	// 훈련 데이터의 x 좌표
		int y = cvRound(train.at<float>(i, 1));	// 훈련 데이터의 y 좌표
		int l = label.at<int>(i, 0);	// 훈련 데이터의 Label value

		if (l == 0)	// 0번 클래스
			circle(img, Point(x, y), 5, Scalar(0, 0, 128), -1, LINE_AA);	// Circle을 그리는 함수
			// 입출력 이미지, 중심점, 반지름, SkyBlue, 내부 채움, 안티에일리어싱

		else if (l == 1)	// 1번 클래스
			circle(img, Point(x, y), 5, Scalar(0, 128, 0), -1, LINE_AA);	// Circle을 그리는 함수
			// 입출력 이미지, 중심점, 반지름, SkyBlue, 내부 채움, 안티에일리어싱

		else if (l == 2)	// 2번 클래스
			circle(img, Point(x, y), 5, Scalar(128, 0, 0), -1, LINE_AA);	// Circle을 그리는 함수
			// 입출력 이미지, 중심점, 반지름, SkyBlue, 내부 채움, 안티에일리어싱
	}

	imshow("knn", img);	// 이미지 출력
}