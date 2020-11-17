#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

// kNN 알고리즘을 이용한 필기체 숫자 학습
// 훈련 데이터 : opencv에서 제공하는 digit.png
// Test 데이터 : 직접 GUI에 쓴 글씨체

// 함수 사용을 위해 미리 선언
Ptr<KNearest> train_knn();
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	Ptr<KNearest> knn = train_knn();	// train_knn 함수를 실행하여 knn에 저장

	// train_knn이 잘 받아졌는지 확인
	if (knn.empty()) {
		cerr << "Training failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8U);	// (400 x 400) 크기의 영상 생성

	imshow("img", img);		// img 영상을 출력
	setMouseCallback("img", on_mouse, (void*)&img);	// img에 마우스 콜백 함수 등록

	while (true) {
		int c = waitKey(0);	// 키 입력을 저장
		
		if (c == 27) {	// esc 버튼을 누르면 종료
			break;
		} else if (c == ' ') {
			Mat img_resize, img_float, img_flatten, res;

			resize(img, img_resize, Size(20, 20), 0, 0, INTER_AREA);	// 영상을 (20x20) size 변환하여 img_resize에 저장
			img_resize.convertTo(img_float, CV_32F);	// 영상을 float형으로 바꿔준다.
			img_flatten = img_float.reshape(1, 1);		// (20x20) 1채널 이미지 -> (1x400) 1채널로 reshape
			// (새로운 채널의 갯수, 행의 새로운 갯수) 열의 갯수는 자동으로 계산
			// reshape - 픽셀의 위치 변경 없이 Mat의 Dimension 변경

			knn->findNearest(img_flatten, 3, res);	// 테스트 데이터 예측
			// (테스트 데이터가 행 단위로 저장 된 행렬, 사용할 최근접 이웃 갯수, 입력 샘플에 대해 저장할 행렬)
			cout << cvRound(res.at<float>(0, 0)) << endl;

			img.setTo(0);	// img 영상의 원소를 0(검은색)으로 설정
			imshow("img", img);	// img 영상을 출력
		} 
	}

	return 0;
}

// kNN 알고리즘 학습을 위해 사용하는 함수
Ptr<KNearest> train_knn()
{
	// digits.png를 GrayScale 이미지로 Mat 형태로 저장
	Mat digits = imread("digits.png", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (digits.empty()) {
		cerr << "Image load failed!" << endl;
		//return; //error: could not convert ‘-1’ from ‘int’ to ‘cv::Ptr<cv::ml::KNearest>’ 발생
	}

	Mat train_images, train_labels;

	// 가로 100개, 세로 50개 (20x20) 이미지를 하나씩 불러온다.
	for (int j = 0; j < 50; j++) {
		for (int i = 0; i < 100; i++) {
			Mat roi, roi_float, roi_flatten;
			roi = digits(Rect(i * 20, j * 20, 20, 20));	// 필기체 숫자 영상 저장
			roi.convertTo(roi_float, CV_32F);	// 자료형을 float로 변환
			roi_flatten = roi_float.reshape(1, 1);	// (20x20) 1채널 이미지 -> (1x400) 1채널로 reshape
			// (새로운 채널의 갯수, 행의 새로운 갯수) 열의 갯수는 자동으로 계산
			// reshape - 픽셀의 위치 변경 없이 Mat의 Dimension 변경 

			train_images.push_back(roi_flatten);	// roi_flatten을 train_images 맨 아래 행으로 추가
			train_labels.push_back(j / 5);	// 현재 추가한 필기체 숫자 영상의 정답 레이블 추가
		}
	}

	Ptr<KNearest> knn = KNearest::create();	// knn 객체를 생성
	knn->train(train_images, ROW_SAMPLE, train_labels);	// knn 학습을 수행

	return knn;
}

Point ptPrev(-1, -1);

// 마우스로 숫자 그리기
void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;

	if (event == EVENT_LBUTTONDOWN) {
		ptPrev = Point(x, y);	// 마우스 왼쪽 버튼을 누르면 누른 위치를 ptPrev에 저장
	} else if (event == EVENT_LBUTTONUP) {
		ptPrev = Point(-1, -1);	// 마우스 왼쪽 버튼을 떼면 ptPrev 좌표를 (-1,-1)로 초기화
	} else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
		// 마우스 왼쪽 버튼을 누른 상태로 마우스를 움직이면 ptPrev 좌표부터 (x,y) 좌표까지 직선을 그린다.
		line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);	 
		// 입출력 이미지, 시작점 , 끝점, 흰색 , Thickness = 40 , 안티에일리어싱
		ptPrev = Point(x, y);

		imshow("img", img);		// 영상을 출력
	}
}
