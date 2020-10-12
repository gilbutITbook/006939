#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언
void camera_in();
void video_in();
void camera_in_video_out();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	camera_in();
	video_in();
	camera_in_video_out();

	return 0;
}

// Camera in Example
void camera_in()
{
	// VideioCapture 클래스 생성
	VideoCapture cap(0);

	//카메라가 사용 가능한지 확인
	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	// get()을 이용하여 카메라 파일의 여러가지 정보를 받아온다.
	// cvRound() -> 실수형을 정수형으로 변환할 때 사용
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	// Mat 클래스 생성
	Mat frame, inversed;
	while (true) {
		// 카메라의 파일에서 한 프레임의 정지 영상 받아오기
		cap >> frame;   //cap.read(frame) 동일한 표현
		
		// 받아오는 frame이 없을 경우 while문 탈출
		if (frame.empty())
			break;

		// 현재 프레임 반전
		inversed = ~frame;

		// 정지 영상을 화면에 출력
		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27) // ESC key
			break;
	}

	// 모든 창을 닫는다.
	destroyAllWindows();

	// cap.release() - 자원을 해제하는 코드
	// 함수가 종료되면서 cap 변수가 소멸, cap.relase() 함수 생략
}

// Video In Example
void video_in()
{
	// VideioCapture 클래스 생성
	VideoCapture cap("stopwatch.avi");

	//비디오가 사용 가능한지 확인
	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;      // 비디오 프레임의 가로 크기
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;    // 비디오 프레임의 세로 크기
	cout << "Frame count: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;      // 비디오 프레임의 전체 프레임 수

	// 동영상의 FPS를 확인
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;

	// frame의 time에 대한 차이를 계산
	int delay = cvRound(1000 / fps);

	// Mat 클래스 생성
	Mat frame, inversed;

	while (true) {
		// 카메라의 파일에서 한 프레임의 정지 영상 받아오기
		cap >> frame;    //cap.read(frame) 동일한 표현

		// 받아오는 frame이 없을 경우 while문 탈출
		if (frame.empty())
			break;

		// 현재 프레임 반전
		inversed = ~frame;

		// 정지 영상을 화면에 출력
		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) // delay 만큼 기다리고 ESC key 누르면 종료
			break;
	}

	// 모든 창을 닫는다.
	destroyAllWindows();
}

// Camera 영상을 Video로 저장하는 함수
// Input : Camera
// Output : .avi Video
void camera_in_video_out()
{
	// VideioCapture 클래스 생성
	VideoCapture cap(0);

	// 카메라가 사용 가능한지 확인
	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));      // 카메라의 가로 크기
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));     // 카메라의 세로 크기
	double fps = cap.get(CAP_PROP_FPS);					 // 카메라의 fps

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');    // DivX MPEG-4 코덱
	int delay = cvRound(1000 / fps);						 // frame의 time에 대한 차이를 계산

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));  // 저장할 동영상 파일 생성

	// 비디오 파일이 잘 저장 되었는지 확인
	if (!outputVideo.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}

	// Mat 클래스 생성
	Mat frame, inversed;

	while (true) {
		// 카메라의 파일에서 한 프레임의 정지 영상 받아오기
		cap >> frame;

		// 받아오는 frame이 없을 경우 while문 탈출
		if (frame.empty())
			break;

		// 카메라 프레임을 반전시켜 inversed 프레임에 저장
		inversed = ~frame;

		// inversed 프레임을 outputVideo에 저장
		outputVideo << inversed;

		// 정지 영상을 화면에 출력
		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)   // delay 만큼 기다리고 ESC key 누르면 종료
			break;
	}

	// 모든 창을 닫는다.
	destroyAllWindows();
}
