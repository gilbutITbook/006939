#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// OpenCV 3.4.0으로 실습을 진행하여 따로 코드를 실행시키지는 못했습니다.
// QRCodeDetector Class는 OpenCV 4.0부터 지원 가능합니다.

void decode_qrcode();

// 동영상에서 QR 코드 검출 및 해석 예제
int main(void)
{
	decode_qrcode();

	return 0;
}

void decode_qrcode()
{
	VideoCapture cap(0);	// VideoCapture 클래스 생성

	// 카메라가 잘 불러지는지 확인
	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	QRCodeDetector detector;	// QRCodeDetector 생성

	Mat frame;		// frame을 담을 Mat 생성
	while (true) {
		cap >> frame;

		if (frame.empty()) {	// 더 이상 받을 프레임이 없을 경우 break 
			cerr << "Frame load failed!" << endl;
			break;
		}

		vector<Point> points;	// QR 코드 위치를 담을 Point Vector생성
		String info = detector.detectAndDecode(frame, points);	// QR 코드에서 문자열 추출

		if (!info.empty()) {	// 문자열에 info 변수가 저장 되었다면
			polylines(frame, points, true, Scalar(0, 0, 255), 2);	// 임의의 모양을 그리는 함수
			// 입출력 이미지, 좌표 배열, 폐곡선 유무, Red, Thickness = 2
			putText(frame, info, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
			// 다양한 Pont의 문자열 출력 (입출력 이미지, 문자열, 시작점, 폰트, Thickness, Color(B,G,R))
		}

		imshow("frame", frame);		// 이미지 출력
		if (waitKey(1) == 27)		// 10ms 만큼 기다리고 ESC Key 누르면 종료
			break;
	}
}