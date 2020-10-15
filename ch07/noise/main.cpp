#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
void noise_gaussian();
void filter_bilateral();
void filter_median();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	noise_gaussian();
	filter_bilateral();
	filter_median();

	return 0;
}

// 가우시안 잡음 추가 예제
void noise_gaussian()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 이미지 출력
	imshow("src", src);

	// 표준편차를 10씩 증가하면서 변화 관찰
	for (int stddev = 10; stddev <= 30; stddev += 10) {
		// Noise 행렬  32비트, signed, 1채널 생성 (음수까지 받아야 하므로)
		Mat noise(src.size(), CV_32SC1);
		// 난수를 이용하여 Noise 추가
		randn(noise, 0, stddev); //(입출력 영상, 가우시안 분포 평균, 가우시안 분포 표준편차)

		// 결과 영상 생성
		Mat dst;
		// 영상의 덧셈을 이용하여 결과 영상 생성
		add(src, noise, dst, Mat(), CV_8U);  // (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치, 마스크 행렬, 출력 행렬 깊이)

		// 사용한 표준편차를 화면에 출력
		String desc = format("stddev = %d", stddev);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		// 이미지 출력
		imshow("dst", dst);
		waitKey();              // 키 입력을 기다리는 함수
	}

	destroyAllWindows();        // 모든 창이 소멸
}

// 양방향 필터 예제 - 엣지 성분은 유지하면서 가우시안 잡음 제거
void filter_bilateral()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Noise 행렬  32비트, signed, 1채널 생성 (음수까지 받아야 하므로)
	Mat noise(src.size(), CV_32SC1);
	// 난수를 이용하여 Noise 추가
	randn(noise, 0, 5);  //(입출력 영상, 가우시안 분포 평균, 가우시안 분포 표준편차)
	add(src, noise, src, Mat(), CV_8U);  // (입력영상1, 입력영상2, 결과영상- 입력영상과 채널 수가 일치, 마스크 행렬, 출력 행렬 깊이)

	// 가우시안 블러 결과 생성
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);     // (입력 영상, 결과 영상, 가우시안 커널 크기, sigma)

	// 양방향 필터 결과 생성
	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);  
	// (입력 영상, 결과 영상, 필터링에 사용할 이웃 픽셀과의 거리, Color space(밝기 Space)에서 가우시안 필터 표준편차, 좌표 space에서 가우시안 필터 표준편차)

	// 이미지 출력
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();             // 키 입력을 기다리는 함수
	destroyAllWindows();   // 모든 창이 소멸
}

// Median 필터링 예제
void filter_median()
{
	// lenna.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	
	// salt & pepper noise 만들기
	int num = (int)(src.total() * 0.1);    // src 영상에서 10% 해당하는 pixel 갯수 생성
	for (int i = 0; i < num; i++) {
		int x = rand() % src.cols;         // (0 ~ 열의 갯수) 중 하나를 random하게 선택   
		int y = rand() % src.rows;		   // (0 ~ 행의 갯수) 중 하나를 random하게 선택
		src.at<uchar>(y, x) = (i % 2) * 255;  // Pixel Value를 0 또는 255로 설정
	}

	// 표준 편차가 1인 가우시안 필터 영상 생성
	Mat dst1;
	GaussianBlur(src, dst1, Size(), 1);     // (입력 영상, 결과 영상, 가우시안 커널 크기, sigma)

	// 커널 크기가 3인 Median 필터 영상 생성
	Mat dst2;
	medianBlur(src, dst2, 3);               // (입력 영상, 결과 영상, 커널의 크기(3이상의 홀수))

	// 이미지 출력
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();			   // 키 입력을 기다리는 함수
	destroyAllWindows();   // 모든 창이 소멸
}
