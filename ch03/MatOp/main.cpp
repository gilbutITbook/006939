#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

// 주석을 이용하여 원하는 부분만 출력
int main()
{
	MatOp1();
	MatOp2();
	MatOp3();
	MatOp4();
	MatOp5();
	MatOp6();
	MatOp7();

	return 0;
}

// Mat의 생성과 초기화
void MatOp1()
{
	Mat img1; 	// empty matrix - 비어있는 행렬

	Mat img2(480, 640, CV_8UC1);		// unsigned char, 1-channel
	// 행(세로), 열(가로), uchar형태로 1채널, data는 garbage value

	Mat img3(480, 640, CV_8UC3);		// unsigned char, 3-channels
	// 행(세로), 열(가로), uchar형태로 3채널, data는 garbage value

	Mat img4(Size(640, 480), CV_8UC3);	// Size(width, height)
	// Size로 행과 열을 선언, uchar형태로 3채널, data는 garbage value

	Mat img5(480, 640, CV_8UC1, Scalar(128));		// initial values, 128
	// 행(세로), 열(가로), uchar형태로 1채널, data는 128로 채워진다.

	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));	// initial values, red
	// 행(세로), 열(가로), uchar형태로 3채널, data는 B, G, R 순서이므로 Red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);	// 0's matrix
	// 행(세로), 열(가로), 32비트 수, data는 0으로 채워짐.

	Mat mat2 = Mat::ones(3, 3, CV_32FC1);	// 1's matrix
	// 행(세로), 열(가로), 32비트 수, data는 1으로 채워짐.

	Mat mat3 = Mat::eye(3, 3, CV_32FC1);	// identity matrix
	// 행(세로), 열(가로), 32비트 수, data는 단위 행렬

	float data[] = { 1, 2, 3, 4, 5, 6 };
	// 데이터의 원소를 미리 정의
	Mat mat4(2, 3, CV_32FC1, data);
	// 미리 정의된 데이터를 이용하여 Mat 선언 - 하나의 Memory space를 공유

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	// Mat4와 일치, 연산자를 이용하여 data 선언

	// Mat mat6 = (Mat_<float>({2, 3}, { 1, 2, 3, 4, 5, 6 }));
	// OpenCV 4.0부터 적용 가능

	// create 함수를 이용하여 생성
	mat4.create(256, 256, CV_8UC3);	// uchar, 3-channels
	mat5.create(4, 4, CV_32FC1);	// float, 1-channel

	mat4 = Scalar(255, 0, 0);
	// mat4의 value를 Blue로 설정

	mat5.setTo(1.f);
	// mat5의 모든 value를 1.f로 설정
}

// 행렬의 복사
void MatOp2()
{	
	Mat img1 = imread("dog.bmp");
	// dog.bmp를 Mat으로 선언

	Mat img2 = img1; // 복사 생성자 (얕은 복사)
	Mat img3;
 	img3 = img1;     // 대입 연산자 (앝은 복사)

	// 메모리 Space를 새로 할당하여 깊은 복사를 할 때
	Mat img4 = img1.clone();  // 자기 자신과 동일한 Mat을 만들고 깊은 복사가 일어남
	Mat img5;
	img1.copyTo(img5);        // 비어있는 객체에서 img1과 동일한 Mat으로 만들고 깊은 복사가 일어남.

	img1.setTo(Scalar(0, 255, 255));	// img1의 value를 B, G, R -> yellow로 바꿈.

	imshow("img1", img1); 
	imshow("img2", img2);  // 얕은 복사로 노란색 이미지
	imshow("img3", img3);  // 얕은 복사로 노란색 이미지
	imshow("img4", img4);  // 깊은 복사로 원본 이미지
	imshow("img5", img5);  // 깊은 복사로 원본 이미지

	waitKey();             // 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();   // 영상 출력 창을 소멸시키는 함수
}

// 부분 행렬 추출 - 영상에서 특정 부분 추출
void MatOp3()
{
	// cat.bmp를 Mat으로 선언
	Mat img1 = imread("cat.bmp");

	// image load를 검사
	if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat img2 = img1(Rect(220, 120, 340, 240));
	// img1에서 (220, 120) 좌표부터 가로가 340, 세로가 240인 영상을 추출 (얕은 복사)

	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();
	// img3를 깊은 복사를 이용하여 img2와 동일한 형태로 선언

	img2 = ~img2;
	//img2에 value에 대해 반전시킴

	Mat img1_rowrange = img1.rowRange(220,230);  // 행의 범위에 해당하는 Value로 Mat 선언
	Mat img1_colrange = img1.colRange(100,150);  // 열의 범위에 해당하는 Value로 Mat 선언


	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	cout << "img1 rowrange : " << img1_rowrange << endl;
	cout << "img1 colrange : " << img1_colrange << endl; 

	waitKey();             // 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();   // 영상 출력 창을 소멸시키는 함수
} 

// 행렬의 원소 Value 참조
void MatOp4()
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);
	// (3 x 4) 크기의 1차원 영행렬 선언
	
	//Mat.at() 사용 방법 - 원소 접근
	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	}

	// Mat.ptr() 사용 방법 - y번째 행의 시작 주소 접근
	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j); // j번째 행 원소의 시작 주소를 반환 - 포인터로 접근
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;  // p를 1차원 배열처럼 사용하여 원소에 접근
		}
	}

	// Matiterator 반복자 사용 방법
	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}

	cout << "mat1:\n" << mat1 << endl;  // 원소에 접근하여 1 증가를 3번 하였으므로 모든 원소는 3 출력
}

// 행렬 정보 참조하기
void MatOp5()
{
	Mat img1 = imread("lenna.bmp");
	// lenna.bmp를 Mat으로 선언

	cout << "Width: " << img1.cols << endl;            // 가로 정보를 출력
	cout << "Height: " << img1.rows << endl;           // 세로 정보를 출력
	cout << "Channels: " << img1.channels() << endl;   // 채널 정보를 출력

	if (img1.type() == CV_8UC1)                        // type()은 행렬의 type 반환
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };       // 데이터를 float형식으로 선언
	Mat mat1(2, 2, CV_32FC1, data);                    // data를 이용하여 Mat의 Value 선언
	cout << "mat1:\n" << mat1 << endl;
	// 연산자 재정의를 통한 행렬 원소 반환
}

// 행렬 연산
void MatOp6()
{
	float data[] = { 1, 1, 2, 3 };         // 데이터를 float형식으로 선언
	Mat mat1(2, 2, CV_32FC1, data);        // data를 이용하여 Mat의 Value 선언
	cout << "mat1:\n" << mat1 << endl;
	// 연산자 재정의를 통한 행렬 원소 반환

	Mat mat2 = mat1.inv();                 
	// 역행렬을 계산해주는 함수 - 일반적으로는 가우스 소거법, 역행렬이 없을경우 SVD(Single Value Decompostion) 이용
	cout << "mat2:\n" << mat2 << endl;

	cout << "mat1.t():\n" << mat1.t() << endl;  //.t() 함수를 이용하여 전치행렬을 반환
	cout << "mat1 + 3:\n" << mat1 + 3 << endl;  // 모든 행렬 원소에 3씩 증가
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;  // 행렬의 덧셈
	cout << "mat1 * mat2:\n" << mat1 * mat2 << endl;  // 행렬의 곱셈
}

// Mat의 크기 및 Type 변환 함수
void MatOp7()
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	// lenna.bmp를 그레이스케일 Mat 형식으로 선언, data - uchar8

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);   // 데이터의 type을 float32로 바꿔 img1f에 저장

	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };  // 데이터를 uchar 형태로 선언
	Mat mat1(3, 4, CV_8UC1, data1);                             // data1을 담고 있는 (3x4) 형태의 행렬을 Mat으로 선언, 
	Mat mat2 = mat1.reshape(0, 1);                              // 행의 개수를 1로 변경 따라서 (12x1) 형태의 Mat 반환
	
	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	mat1.resize(5, 100);  
	// reshape 처럼 모양을 변경시키는 것이 아니라, 행 크기를 변경하고 원소를 추가할 때 사용

	cout << "mat1:\n" << mat1 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;                   // (1x4) 크기이고 Value가 255인 Mat 생성 및 선언
	mat1.push_back(mat3);
	// mat1의 맨 마지막 행으로 mat3를 추가
	cout << "mat1:\n" << mat1 << endl;
}
