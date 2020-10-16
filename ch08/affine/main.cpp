#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void affine_transform();
void affine_translation();
void affine_shear();
void affine_scale();
void affine_rotation();
void affine_flip();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	affine_transform();
	affine_translation();
	affine_shear();
	affine_scale();
	affine_rotation();
	affine_flip();

	return 0;
}

// Affine Transform Example
void affine_transform()
{
	// tekapo.bmp를 Mat 형태로 저장
	Mat src = imread("tekapo.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 세점 좌표를 Point2f의 배열로 선언
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(0, 0);                     // 입력 영상 왼쪽 위 꼭지점
	srcPts[1] = Point2f(src.cols - 1, 0);	       // 입력 영상 오른쪽 위 꼭지점
	srcPts[2] = Point2f(src.cols - 1, src.rows - 1);  // 입력 영상 오른쪽 아래 꼭지점
	dstPts[0] = Point2f(50, 50);				   // 결과 영상 왼쪽 위 꼭지점
	dstPts[1] = Point2f(src.cols - 100, 100);	   // 결과 영상 오른쪽 위 꼭지점
	dstPts[2] = Point2f(src.cols - 50, src.rows - 50);  // 결과 영상 오른쪽 아래 꼭지점

	// Affine 변환 행렬을 구하는 함수 (입력 영상에서 세 점 좌표, 결과 영상에서 세 점 좌표)
	Mat M = getAffineTransform(srcPts, dstPts);

	// 결과 영상 생성
	Mat dst;
	// Affine 변환 영상 생성
	warpAffine(src, dst, M, Size());  	// (원본 영상, 결과 영상, 어파인 행렬, 결과 영상 크기) 

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();			    // 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// 이동 변환 Example
void affine_translation()
{
	// tekapo.bmp를 Mat 형태로 저장
	Mat src = imread("tekapo.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 위 코드는 OpenCV 4.0부터 지원
	//Mat M = Mat_<double>({ 2, 3 }, { 1, 0, 150, 0, 1, 100 });
	Mat M = (Mat_<double>(2,3) << 1, 0, 150, 0, 1, 100);  // 가로로 150 pixel, 세로로 100 pixel 이동

	// 결과 영상 생성
	Mat dst;
	// Affine 변환 영상 생성
	warpAffine(src, dst, M, Size());     // (원본 영상, 결과 영상, 어파인 행렬, 결과 영상 크기) 

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// 전단 변환 Example - 한쪽 방향으로 밀어서 평행 사변형을 만든다.
void affine_shear()
{
	// tekapo.bmp를 Mat 형태로 저장
	Mat src = imread("tekapo.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	double mx = 0.3;
	//Mat M = Mat_<double>({ 2, 3 }, { 1, mx, 0, 0, 1, 0 });  // OpenCV 4.0부터 지원
	Mat M = (Mat_<double>(2,3) <<  1, mx, 0, 0, 1, 0 );  // 가로 방향으로 0.3 정도 밀린 변환 행렬 설정

	// 결과 영상 생성
	Mat dst;
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows)); // (원본 영상, 결과 영상, 어파인 행렬, 결과 영상 크기) 
	// 전단 변환에 의해 영상이 잘리지 않도록 사이즈 조절

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// 크기 변환 Example
void affine_scale()
{
	// tekapo.bmp를 Mat 형태로 저장
	Mat src = imread("rose.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst1, dst2, dst3, dst4;
	// Interpolation에 따른 차이 확인
	resize(src, dst1, Size(), 4, 4, INTER_NEAREST);  //x 방향 4배, y 방향 4배 확대, 
	resize(src, dst2, Size(1920, 1280));			 // (1920x1280으로 확대) 기본 Interpolation
	resize(src, dst3, Size(1920, 1280), 0, 0, INTER_CUBIC);  // (1920x1280으로 확대) 3차 회선 Interpolation
	resize(src, dst4, Size(1920, 1280), 0, 0, INTER_LANCZOS4);  // (1920x1280으로 확대) 란초스 Interpolation

	// 이미지 출력
	imshow("src", src);
	imshow("dst1", dst1(Rect(400, 500, 400, 400)));    // 결과 영상 중 (400,500) 지점부터 (400x400) 크기 영상 출력
	imshow("dst2", dst2(Rect(400, 500, 400, 400)));
	imshow("dst3", dst3(Rect(400, 500, 400, 400)));
	imshow("dst4", dst4(Rect(400, 500, 400, 400)));

	waitKey();				// 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// 회전 변환 Example
void affine_rotation()
{	
	// tekapo.bmp를 Mat 형태로 저장
	Mat src = imread("tekapo.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Point2f cp(src.cols / 2.f, src.rows / 2.f);   // 영상의 중심 좌표를 선언
	// 영상의 중심 좌표를 기준으로 반시계 방향으로 20도 scale 변화는 1인 변환 행렬 생성
	Mat M = getRotationMatrix2D(cp, 20, 1);   //(중심 좌표, 회전 Angle, Scale 비율)

	// 결과 영상 생성
	Mat dst;
	warpAffine(src, dst, M, Size());    // (원본 영상, 결과 영상, 어파인 행렬, 결과 영상 크기)

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();			    // 키 입력을 기다리는 함수
	destroyAllWindows();    // 모든 창이 소멸
}

// 대칭 변환 Example
void affine_flip()
{
	// tekapo.bmp를 Mat 형태로 저장
	Mat src = imread("eastsea.bmp");

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 이미지 출력
	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1, 0, -1 };
	for (int i = 0; i < 3; i++) {
		// 대칭 변환 수행
		flip(src, dst, flipCode[i]);   // (원본 영상, 결과 영상, flip code)

		// 화면에 문자열 출력
		String desc = format("flipCode: %d", flipCode[i]);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 1, LINE_AA);

		// 이미지 출력
		imshow("dst", dst);
		waitKey();			 // 키 입력을 기다리는 함수
	}

	destroyAllWindows();     // 모든 창이 소멸
}