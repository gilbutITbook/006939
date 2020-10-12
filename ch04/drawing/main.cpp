#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언
void drawLines();
void drawPolys();
void drawText1();
void drawText2();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	drawLines();
	drawPolys();
	drawText1();
	drawText2();

	return 0;
}

// Draw Line Example
void drawLines()
{
	// (400 x 400) 모든 픽셀이 흰색인 Mat 클래스 생성
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));
	
	// line 함수를 이용하여 직선 그리기 - 선 색상, 선 두께 지정
	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255)); // 입출력 이미지, 시작점, 끝점, Red
	line(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 3);  // 입출력 이미지, 시작점 , 끝점, Purple, Thickness = 3
	line(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 10);   // 입출력 이미지, 시작점 , 끝점, Blue , Thickness = 10

	// line 함수를 이용하여 직선 그리기 - 선 색상, 선 연결 방향 지정
	line(img, Point(250, 50), Point(350, 100), Scalar(0, 0, 255), 1, LINE_4);  // 입출력 이미지, 시작점, 끝점, Red , 4방향 연결
	line(img, Point(250, 70), Point(350, 120), Scalar(255, 0, 255), 1, LINE_8);  // 입출력 이미지, 시작점 , 끝점, Purple, 8방향 연결
	line(img, Point(250, 90), Point(350, 140), Scalar(255, 0, 0), 1, LINE_AA);   // 입출력 이미지, 시작점 , 끝점, Blue , 안티에일리어싱

	// 화살표 형태의 직선 그리기
	arrowedLine(img, Point(50, 200), Point(150, 200), Scalar(0, 0, 255), 1);    // 입출력 이미지, 시작점, 끝점, Red , Thickness = 1
	arrowedLine(img, Point(50, 250), Point(350, 250), Scalar(255, 0, 255), 1);  // 입출력 이미지, 시작점, 끝점, Purple , Thickness = 1 , 직선 길이에 비례해서 화살표 크기 증가
	arrowedLine(img, Point(50, 300), Point(350, 300), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05); // 입출력 이미지, 시작점 , 끝점, Blue , 화살표 크기를 줄이고 싶으면 tipLength 길이 조절

	// 다양한 형태의 Marker 만들기
	drawMarker(img, Point(50, 350), Scalar(0, 0, 255), MARKER_CROSS);      // 입출력 이미지, 마커 출력 위치, Red, 십자가 모양
	drawMarker(img, Point(100, 350), Scalar(0, 0, 255), MARKER_TILTED_CROSS); // 입출력 이미지, 마커 출력 위치, Red, X 모양
	drawMarker(img, Point(150, 350), Scalar(0, 0, 255), MARKER_STAR);      // 입출력 이미지, 마커 출력 위치, Red, * 모양
	drawMarker(img, Point(200, 350), Scalar(0, 0, 255), MARKER_DIAMOND);   // 입출력 이미지, 마커 출력 위치, Red, 마름모 모양
	drawMarker(img, Point(250, 350), Scalar(0, 0, 255), MARKER_SQUARE);    // 입출력 이미지, 마커 출력 위치, Red, Square 모양
	drawMarker(img, Point(300, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_UP);  // 입출력 이미지, 마커 출력 위치, Red, 위로 뾰족한 Triangle 모양
	drawMarker(img, Point(350, 350), Scalar(0, 0, 255), MARKER_TRIANGLE_DOWN); // 입출력 이미지, 마커 출력 위치, Red, 아래로 뾰족한 Triangle 모양

	imshow("img", img);   // 영상을 출력
	waitKey();            // 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();  // 모든 창을 닫는다.
}

// Draw Polygon Example
void drawPolys()
{
	// (400 x 400) 모든 픽셀이 흰색인 Mat 클래스 생성
	Mat img(400, 400, CV_8UC3, Scalar(255, 255, 255));

	// Rectangle을 그리는 함수
	rectangle(img, Rect(50, 50, 100, 50), Scalar(0, 0, 255), 2); //입출력 이미지, 좌표, Red, Thickness = 2
	rectangle(img, Rect(50, 150, 100, 50), Scalar(0, 0, 128), -1); //입출력 이미지, 좌표, Brown, 내부 채움

	// Circle을 그리는 함수
	circle(img, Point(300, 120), 30, Scalar(255, 255, 0), -1, LINE_AA); // 입출력 이미지, 중심점, 반지름, SkyBlue, 내부 채움, 안티에일리어싱
	circle(img, Point(300, 120), 60, Scalar(255, 0, 0), 3, LINE_AA);    // 입출력 이미지, 중심점, 반지름, Blue, Thickness = 3, 안티에일리어싱

	// 타원을 그리는 함수
	ellipse(img, Point(120, 300), Size(60, 30), 20, 0, 270, Scalar(255, 255, 0), FILLED, LINE_AA);
	// 입출력 이미지, 중심점, 반지름(x축, y축), 시작 Angle, 끝 Angle, SkyBlue, 내부 채움, 안티에일리어싱
	ellipse(img, Point(120, 300), Size(100, 50), 20, 0, 360, Scalar(0, 255, 0), 2, LINE_AA);
	// 입출력 이미지, 중심점, 반지름(x축, y축), 시작 Angle, 끝 Angle, Green, Thickness = 2, 안티에일리어싱

	// 임의의 모양(계단 모양)을 그리는 함수 
	vector<Point> pts;   // vector로 꼭지점 좌표 저장
	pts.push_back(Point(250, 250)); pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300)); pts.push_back(Point(350, 300));
	pts.push_back(Point(350, 350)); pts.push_back(Point(250, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);  // 입출력 이미지, 좌표 배열, Purple, Thickness = 2

	imshow("img", img);  // 영상을 출력
	waitKey();			 // 키보드가 눌러질 때까지 기다리는 함수

	destroyAllWindows(); // 모든 창을 닫는다.
}

// Draw Text Example with different font style
void drawText1()
{
	// (500 x 800) 모든 픽셀이 흰색인 Mat 클래스 생성
	Mat img(500, 800, CV_8UC3, Scalar(255, 255, 255));

	// 다양한 Pont의 문자열 출력 (입출력 이미지, 문자열, 시작점, 폰트, Thickness, Color(B,G,R))
	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_DUPLEX", Point(20, 150), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX", Point(20, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_TRIPLEX", Point(20, 250), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_COMPLEX_SMALL", Point(20, 300), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255, 0, 0));
	putText(img, "FONT_HERSHEY_SCRIPT_SIMPLEX", Point(20, 350), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_SCRIPT_COMPLEX", Point(20, 400), FONT_HERSHEY_SCRIPT_COMPLEX, 1, Scalar(255, 0, 255));
	putText(img, "FONT_HERSHEY_COMPLEX | FONT_ITALIC", Point(20, 450), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, Scalar(255, 0, 0));

	imshow("img", img);  // 영상을 출력
	waitKey();			 // 키보드가 눌러질 때까지 기다리는 함수

	destroyAllWindows(); // 모든 창을 닫는다.
}

// 이미지 중앙에 문자열 출력하는 함수
void drawText2()
{
	// (200 x 640) 모든 픽셀이 흰색인 Mat 클래스 생성
	Mat img(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";   // 문자열
	int fontFace = FONT_HERSHEY_TRIPLEX;   // 폰트 종류
	double fontScale = 2.0;				   // 폰트 크기
	int thickness = 1;					   // 폰트 두께

	// 출력할 문자열을 저장할 영역의 크기를 구해 sizeText에 저장
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, 0);
	Size sizeImg = img.size();    // 영역의 크기를 저장

	// 문자열을 출력할 좌표 계산
	Point org((sizeImg.width - sizeText.width) / 2, (sizeImg.height + sizeText.height) / 2);
	// org를 그림에서 출력
	circle(img, org , 5, Scalar(0, 0, 255), -1, LINE_AA); // 입출력 이미지, 중심점, 반지름, Red, 내부 채움, 안티에일리어싱
	// 입출력 이미지, 문자열, 좌측 하단 좌표, 폰트 종류, 폰트 크기, Blue, 폰트 두께
	putText(img, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness);
	// 입출력 이미지, 좌표, 또 다른 좌표, Green, Thickness = 1
	rectangle(img, org, org + Point(sizeText.width, -sizeText.height), Scalar(0, 255, 0), 1);

	imshow("img", img);    // 영상을 출력
	waitKey();		       // 키보드가 눌러질 때까지 기다리는 함수

	destroyAllWindows();   // 모든 창을 닫는다.
}