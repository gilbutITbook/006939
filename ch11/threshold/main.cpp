#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위한 선언
void on_threshold(int pos, void* userdata);

// 트랙바를 이용한 이진화 예제
int main(int argc, char* argv[])		// 프로그램 실행시 명령행 인자를 2개 받을 수 있도록 설정
{
	Mat src;
	
	// 명령 인수가 2개보다 작으면 neutrophils.png를 입력영상으로 사용
	// 만약 실행 파일 이름 뒤에 사용할 영상 파일 이름을 명시하면 해당 파일을 입력 영상으로 사용
	if (argc < 2)
		src = imread("neutrophils.png", IMREAD_GRAYSCALE);
	else 
		src = imread(argv[1], IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);		// 이미지 출력

	namedWindow("dst");		// dst라는 이름의 Window 생성
	createTrackbar("Threshold", "dst", 0, 255, on_threshold, (void*)&src);	// 트랙바 생성
	// track bar 생성 (name, windowname, 트랙바 위치, 트랙바 최대 value, Callback 함수, 전달하고 싶은 데이터)
	setTrackbarPos("Threshold", "dst", 128);	// 트랙바 value 지정
	// (트랙 바 이름, 윈도우 이름, 초기 value)

	waitKey(0);		// 키 입력을 기다리는 함수
	return 0;
}

void on_threshold(int pos, void* userdata)
{
	// void type의 userdata를 Mat type으로 형변환 후, img 변수로 참조
	Mat src = *(Mat*)userdata;

	Mat dst;
	threshold(src, dst, pos, 255, THRESH_BINARY);
	// 입력 영상, 출력 영상, Threshold, Max Value, 연산 방법(Threshold보다 크면 흰색, 아니면 검은색)

	imshow("dst", dst);		// 이미지 출력
}
