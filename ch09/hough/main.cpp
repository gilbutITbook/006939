#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void hough_lines();
void hough_line_segments();
void hough_circles();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	hough_lines();
	hough_line_segments();
	hough_circles();

	return 0;
}

void hough_lines()
{
	// building.jpg를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat edge;  // 캐니 엣지 결과 영상 생성
	Canny(src, edge, 50, 150);		// 케니 엣지 검출기 적용
	// (원본 영상, 결과 영상, 최소 Threshold, 최대 Threshold)

	vector<Vec2f> lines;  //line을 저장할 Vec2f 생성
	HoughLines(edge, lines, 1, CV_PI / 180, 250);  // 허프 변환 직선 검출 수행 , Output :rho, theta
	// (입력 영상(보통 엣지 영상), 결과를 담을 Vector, 축적 배열의 픽셀 단위, 축적 배열의 Angle 단위, 직선으로 판단할 Threshold)
	
	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);  	// GrayScale 영상을 BGR 영상으로 변환

	for (size_t i = 0; i < lines.size() ; i++) {  // 직선의 갯수만큼 반복문 수행 
		float rho = lines[i][0], theta = lines[i][1];  // 벡터의 원소를 rho, theta에 저장
		float cos_t = cos(theta), sin_t = sin(theta);  // cos과 sin 구하기
		float x0 = rho * cos_t, y0 = rho * sin_t;      // 직선을 지나는 한 점(원점에서 직선에 수선을 내렸을 때 만나는 점)
		float alpha = 1000;  // 충분히 크게 설정하여 pt1과 pt2가 바깥에 있도록 하기

		Point pt1(cvRound(x0 - alpha * sin_t), cvRound(y0 + alpha * cos_t));  // 선을 그릴 때 필요한 한 점(pt1)
		Point pt2(cvRound(x0 + alpha * sin_t), cvRound(y0 - alpha * cos_t));  // 선을 그릴 때 필요한 한 점(pt2)
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
		// line 함수 (입출력 이미지, 시작점, 끝점, Red , 안티에일리어싱)
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);				// 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();	// 모든 창을 닫는다.
}

//확률적 허프 변환 선분 검출 예제
void hough_line_segments()
{
	// building.jpg를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 엣지 영상 생성
	Mat edge;
	Canny(src, edge, 50, 150);   // 케니 엣지 검출기 적용
	// (원본 영상, 결과 영상, 최소 Threshold, 최대 Threshold)

	vector<Vec4i> lines;		//line을 저장할 Vec4i 생성
	HoughLinesP(edge, lines, 1, CV_PI / 180, 160, 50, 5);  // 허프 변환 직선 검출 수행 , Output :시작점, 끝점
	// (입력 영상(보통 엣지 영상), 결과를 담을 Vector, 축적 배열의 픽셀 단위, 축적 배열의 Angle 단위, 직선으로 판단할 Threshold, 검출할 선분의 최소 길이, 직선으로 여길 최대 엣지 점 사이)

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);   // GrayScale 영상을 BGR 영상으로 변환

	// 범위 기반 반복문 사용, line 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
		// line 함수 (입출력 이미지, 시작점, 끝점, Red , 안티에일리어싱)
	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);				// 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// 허프 원 검출 Example
void hough_circles()
{
	// coins.png를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("coins.png", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat blurred;  // Blur 영상 생성
	blur(src, blurred, Size(3, 3));
	// 마스크의 크기가 (3 x 3)인 평균 필터 마스크를 수행하여 dst에 저장

	vector<Vec3f> circles;	// 원의 중심좌표(x,y) 반지름을 담는 Vector 생성
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);
	// (입력 영상(GrayScale), 출력 벡터, method, 인접한 원 중심의 최소 거리, Canny edge 높은 Threshold, 축적 배열에서 원 검출을 위한 Threshold)

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);		// GrayScale 영상을 BGR 영상으로 변환

	// 범위 기반 반복문 사용, circles 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]));  // 중심 좌표 저장
		int radius = cvRound(c[2]);					 // 반지름 저장
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
		// 원 그리는 함수(입출력 이미지, 중심점, 반지름, Red, Thickness = 2, 안티에일리어싱)

	}

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);					// 키 입력을 기다리는 함수
	destroyAllWindows();		// 모든 창이 소멸
}
