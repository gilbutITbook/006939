#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void detect_face();
void detect_eyes();

// 주석을 이용하여 원하는 부분 출력
int main()
{
	detect_face();
	detect_eyes();

	return 0;
}

// 얼굴 검출 예제
void detect_face()
{
	// kids.png를 3 채널 Color 이미지로 Mat 형태로 저장
	Mat src = imread("kids.png");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 정면 얼굴을 검출하는 CascadeClassifier 생성(폴더에 haarcascade_frontalface_default.xml 존재 해야 한다.)
	CascadeClassifier classifier("haarcascade_frontalface_default.xml");

	// xml 파일이 잘 불러왔는지 확인
	if (classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return;
	}

	vector<Rect> faces;	// 좌표 정보를 담을 Rect class로 이루어진 Vector 생성
	classifier.detectMultiScale(src, faces);	// 객체 검출 실행 (입력 영상, 검출된 Rect의 좌표 정보)


	// 범위 기반 반복문 사용, faces 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
	for (Rect rc : faces) {
		rectangle(src, rc, Scalar(255, 0, 255), 2);		// Rectangle 그리는 함수
	// (입출력 이미지, Rect의 좌표 , Purple , Thickness = 2)
	}

	imshow("src", src);		// 이미지 출력

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}

// 눈 검출 예제
void detect_eyes()
{
	// kids.png를 3 채널 Color 이미지로 Mat 형태로 저장
	Mat src = imread("kids.png");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 정면 얼굴을 검출하는 CascadeClassifier 생성(폴더에 haarcascade_frontalface_default.xml 존재 해야 한다.)
	CascadeClassifier face_classifier("haarcascade_frontalface_default.xml");

	// 눈을 검출하는 CascadeClassifier 생성(폴더에 haarcascade_eye.xml 존재 해야 한다.)
	CascadeClassifier eye_classifier("haarcascade_eye.xml");

	// xml 파일이 잘 불러왔는지 확인
	if (face_classifier.empty() || eye_classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return;
	}

	vector<Rect> faces;		// 좌표 정보를 담을 Rect class로 이루어진 Vector 생성
	face_classifier.detectMultiScale(src, faces);		// 객체 검출 실행 (입력 영상, 검출된 Rect의 좌표 정보)

	// 범위 기반 반복문 사용, faces 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
	for (Rect face : faces) {
		rectangle(src, face, Scalar(255, 0, 255), 2);			// Rectangle 그리는 함수
	// (입출력 이미지, Rect의 좌표 , Purple , Thickness = 2)

		Mat faceROI = src(face);	// src 영상에서 face의 좌표만 부분적인 영상을 만든다.
		vector<Rect> eyes;		// 좌표 정보를 담을 Rect class로 이루어진 Vector 생성
		eye_classifier.detectMultiScale(faceROI, eyes);		// 객체 검출 실행 (입력 영상, 검출된 Rect의 좌표 정보)
		
		// 범위 기반 반복문 사용, eyes 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
		for (Rect eye : eyes) {
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);	// Rect 좌표를 이용하여 중심점 찾기
			circle(faceROI, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);	// Circle을 그리는 함수
			// 입출력 이미지, 중심점, 반지름, Blue, Thickness = 2, 안티에일리어싱
		}
	}

	imshow("src", src);		// 이미지 출력

	waitKey(0);			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}
