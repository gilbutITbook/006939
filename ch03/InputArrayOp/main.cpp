#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위해 선언
void InputArrayOp();
void printMat(InputArray _mat);


int main(void)
{
	InputArrayOp();

	return 0;
}

// InputArray - 입력 인자 자료형, 다양한 type으로부터 생성될 수 있는 인터페이스
void InputArrayOp()
{
	uchar data1[] = { 1, 2, 3, 4, 5, 6 };   // 데이터의 원소를 미리 정의
	Mat mat1(2, 3, CV_8UC1, data1);         // 미리 정의된 데이터를 이용하여 (2x3) 1채널의 Mat 선언
	
	printMat(mat1);							// getMat()함수를 이용하여 Mat 출력
	
	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };   // float type의 벡터 선언
	printMat(vec1);								  // getMat()함수를 이용하여 벡터 출력
}

void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat();			    // getMat()함수로 Mat type 객체 반환
	cout << mat << endl;
}
