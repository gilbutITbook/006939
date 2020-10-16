#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src;   // 입력 영상 선언
Point2f srcPts[4], dstPts[4];  // 입력 영상과 출력 영상의 네 점 좌표를 저장할 배열 선언 

// 함수 사용을 위해 미리 선언
void on_mouse(int event, int x, int y, int flags, void* userdata);

// Perspective Transform Example
int main()
{
	// card.bmp를 Mat 형태로 저장
	src = imread("card.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	namedWindow("src");      // src라는 window 생성
	setMouseCallback("src", on_mouse);   // src에 마우스 콜백 함수 등록

	// 이미지 출력
	imshow("src", src);
	waitKey(0);			      // 키 입력을 기다리는 함수

	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*)
{
	static int cnt = 0;						// 버튼이 눌린 횟수 count

	if (event == EVENT_LBUTTONDOWN) {		// 마우스 이벤트 중 마우스 왼쪽 버튼이 눌러지는 이벤트만 처리
		if (cnt < 4) {
			srcPts[cnt++] = Point2f(x, y);  // src에서 눌려진 좌표를 srcPts에 저장 후 1 증가

			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);  // 반지름이 5인 원 그리기
			imshow("src", src);				// 이미지 출력

			if (cnt == 4) {					// 4번 눌렀을 때
				int w = 200, h = 300;		// width, height 지정

				// 꼭지점에 해당하는 좌표를 배열에 담는다.
				dstPts[0] = Point2f(0, 0);
				dstPts[1] = Point2f(w - 1, 0);
				dstPts[2] = Point2f(w - 1, h - 1);
				dstPts[3] = Point2f(0, h - 1);

				// 투시 변환 행렬 계산 (입력 4개의 좌표, 결과 4개의 좌표)
				// output :3x3 Mat
				Mat pers = getPerspectiveTransform(srcPts, dstPts); 

				// 투시 변환 행렬 생성
				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h));  //(입력 영상, 결과 영상, 투시 변환 행렬, Size)

				imshow("dst", dst);   // 이미지 출력
			}
		}
	}
}