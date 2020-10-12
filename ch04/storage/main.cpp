#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
void writeData();
void readData();

// String filename = "mydata.xml";
String filename = "mydata.yml";
// String filename = "mydata.json";

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	writeData();
	readData();

	return 0;
}

// 파일 쓰기 모드
void writeData()
{
	// 저장할 데이터들 변수 선언
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = { 80, 90, 50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	FileStorage fs; // FileStorage 객체 생성
	fs.open(filename, FileStorage::WRITE);  // (파일 이름, 파일 열기 모드)

	// 파일이 제대로 열리는지 확인
	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	// 데이터를 파일에 저장할 때는 << 재정의 함수 사용
	fs << "name" << name;
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;

	fs.release();      // 사용하고 있던 파일을 닫고, 메모리 버터를 해제
}

// 파일 읽기 모드
void readData()
{
	// 저장할 데이터들 변수 선언
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ); // FileStorgage 생성 및 선언 (파일 이름, 파일 열기 모드)

	// 파일이 제대로 열리는지 확인
	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}
	
	// 데이터를 파일에서 읽을 때는 >> 재정의 함수 사용
	fs["name"] >> name;
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();  // 사용하고 있던 파일을 닫고, 메모리 버터를 해제

	// 제대로 전달이 되었는지 콘솔 창에 출력
	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores) << endl;      
	cout << "scores: " << Mat(scores).t() << endl;  // 1행 전치 행렬을 구한 후 출력
	cout << "data:\n" << mat1 << endl;
}
