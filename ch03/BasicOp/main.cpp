#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위해 선언
void PointOp();
void SizeOp();
void RectOp();
void RotatedRectOp();
void RangeOp();
void StringOp();

// 주석을 이용하여 원하는 부분만 출력
int main()
{
	PointOp();
	SizeOp();
	RectOp();
	RotatedRectOp();
	RangeOp();
	StringOp();

	return 0;
}

// Point Class Example
void PointOp()
{
	Point pt1;				// pt1 = (0, 0)
	pt1.x = 5; pt1.y = 10;	// pt1 = (5, 10)
    // Point Class 선언을 한 다음 따로 좌표에 대해 선언

	Point pt2(10, 30);		// pt2 = (10, 30)
    // Point Class 선언과 동시에 좌표를 선언
    
	Point pt3 = pt1 + pt2;	// pt3 = [15, 40]
	Point pt4 = pt1 * 2;	// pt4 = [10, 20]
	
    int d1 = pt1.dot(pt2);	// d1 = 350
    // 벡터의 내적 연산

	bool b1 = (pt1 == pt2);	// b1 = false
    // 포인트들이 다른지 아닌지 여부 검사

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;
}

// Size Class Example
void SizeOp()
{
	Size sz1, sz2(10, 20);			// sz1 = [0 x 0], sz2 = [10 x 20]
	sz1.width = 5; sz1.height = 10;	// sz1 = [5 x 10]
    // sz1 - Size Class 선언과 가로 세로 선언
    // sz2 - Size Class 선언과 동시에 가로 세로를 선언

	Size sz3 = sz1 + sz2;	// sz3 = [15 x 30]
	Size sz4 = sz1 * 2;		// sz4 = [10 x 20]
	int area1 = sz4.area();	// area1 = 200

	cout << "sz3: " << sz3 << endl;
	cout << "sz4: " << sz4 << endl;
}

// Rect Class Example
void RectOp()
{
	Rect rc1;					// rc1 = [0 x 0 from (0, 0)]
    // 아직 좌표 설정이나 넓이를 선언해주지 않았다. - 원점

	Rect rc2(10, 10, 60, 40);	// rc2 = [60 x 40 from (10, 10)]
    // rc2는 좌표를 따로 설정해주었다.

	Rect rc3 = rc1 + Size(50, 40);	// rc3 = [50 x 40 from (0, 0)]
    // 시작점과 Size를 설정

	Rect rc4 = rc2 + Point(10, 10);	// rc4 = [60 x 40 from (20, 20)]
    // Rc2의 시작점을 설정

	Rect rc5 = rc3 & rc4;		// rc5 = [30 x 20 from (10, 10)]
    // rc3와 rc4의 교집합의 Rect 클래스 선언

	Rect rc6 = rc3 | rc4;		// rc6 = [80 x 60 from (0, 0)]
    // rc3와 rc4의 합집합의 Rect 클래스 선언

	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl;
}

// RotatedRect Class Example
void RotatedRectOp()
{
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);
    // rr1의 중심좌표, 넓이, angle을 선언

	Point2f pts[4];
	rr1.points(pts);

    // rr1의 좌표 출력
    for(int i = 0; i <4; i++){
        cout << "rr1 "<< i+1 << "'s Point : " << pts[i] << endl;
    }

	Rect br = rr1.boundingRect();
    // rr1을 포함하는 Rect 선언

    cout << "rr1's boungindRect - " << br << endl;    
    

}

// Range Class Example
void RangeOp()
{
	Range r1(0, 10);
    // start, end를 선언
}

// String Class Example
void StringOp()
{
	String str1 = "Hello";
	String str2 = "world";
	String str3 = str1 + " " + str2;	// str3 = "Hello world"

	bool ret = (str2 == "WORLD");

    cout << "world == WORLD ? -->" <<ret << endl;  // false - 대문자와 소문자를 same하게 인식하는지 검사

	Mat imgs[3];
	for (int i = 0; i < 3; i++) {
		String filename = format("data%02d.bmp", i + 1);
		cout << filename << endl;
		imgs[i] = imread(filename);
	}
}