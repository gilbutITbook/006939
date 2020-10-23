#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// HOG Algorithm을 이용한 보행자 검출 예제
int main()
{
	// VideioCapture 클래스 생성
	VideoCapture cap("vtest.avi");

	// 비디오가 사용 가능한지 확인
	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return -1;
	}

	HOGDescriptor hog;	// HOGDescriptor 생성
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());	// 원하는 객체에 훈련된 SVM 분류기 계수 등록
	// 사람을 찾는 검출기를 원하므로 HOGDescriptor::getDefaultPeopleDetector() 등록 - 정적 멤버 함수이기 때문에 클래스 이름까지 써줘야 한다.
	
	Mat frame;	// frame을 담을 Mat 생성
	while (true) {
		cap >> frame;
		if (frame.empty())	// 더 이상 받을 프레임이 없을 경우 break 
			break;

		vector<Rect> detected;	// detect한 좌표를 여러 객체 담기 위해 RectClass로 Vector 생성 
		hog.detectMultiScale(frame, detected);	// 입력 영상에서 다양한 객체의 영역을 검출  (입력 영상, 검출된 Rect 좌표 정보)

		// 범위 기반 반복문 사용, detected 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
		for (Rect r : detected) {
			Scalar c = Scalar(rand() % 256, rand() % 256, rand() % 256);	// 임의의 Color 생성
			rectangle(frame, r, c, 3);	// Rectangle을 그리는 함수
			//입출력 이미지, 좌표, 임의의 Color , Thickness = 3
		}

		imshow("frame", frame);		// 이미지 출력

		if (waitKey(10) == 27)		// 10ms 만큼 기다리고 ESC Key 누르면 종료
			break;
	}

	return 0;
}
