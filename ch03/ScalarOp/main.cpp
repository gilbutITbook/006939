#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
 
void VecOp();
void ScalarOp();

int main(void)
{
	VecOp();
	ScalarOp();

	return 0;
}

// Vec Class Example
void VecOp()
{
	// 영상에서 Pixel Value를 표현하는 용도로 사용	
	Vec3b p1, p2(0, 0, 255);
	// uchar형태의 3채널 Vector 생성
	// p1은 (0,0,0), p2는 (0,0,255)로 초기화

	p1[0] = 100;    // p1의 첫번째 원소에 100을 대입
	cout << "p1: " << p1 << endl;    // p1: [100, 0, 0]
	cout << "p2: " << p2 << endl;    // p2: [0, 0, 255]
}

// Scalar Class Example
void ScalarOp()
{
	// 4채널 이하의 영상에서 Pixel Value를 표현하는 용도로 사용
	// Scalar (밝기)
	// Scalar (B ,G, R)
	// Scalar (B, G, R, alpha)

	Scalar gray = 128;
	cout << "gray: " << gray << endl;      // gray: [128, 0, 0, 0]

	Scalar yellow(0, 255, 255);
	cout << "yellow: " << yellow << endl;  // yellow: [0, 255, 255, 0]

	Mat img1(256, 256, CV_8UC3, yellow);   // 세로 256, 가로 256, 3채널이고 data Value가 Yellow인 Mat 생성 및 선언

	for (int i = 0; i < 4; i++)
		cout << yellow.val[i] << ", " << yellow[i] << endl;    // Scalar 클래스의 원소를 참조하는 방법
}
