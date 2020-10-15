#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수를 사용하기 위한 선언 
void unsharp_mask();

int main(void)
{
	unsharp_mask();

	return 0;
}

// Unsharp 마스크 필터 예제
void unsharp_mask()
{
	// rose.bmp를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// 이미지 출력
	imshow("src", src);

	for (int sigma = 1; sigma <= 5; sigma++) {
		
		// 가우시안 영상 생성
		// sigma 수를 변경해가며 가우시안 필터링 수행
		// (원본 영상, 결과 영상, 가우시안 커널 크기, sigma)
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		// 가중치를 이용하여 샤프닝 결과 영상 생성
		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		// 사용한 가우시안 sigma를 화면에 출력
		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, 
				Scalar(255), 1, LINE_AA);

		// 이미지 출력
		imshow("dst", dst);
		waitKey();			  // 키 입력을 기다리는 함수
	}

	destroyAllWindows();      // 모든 창이 소멸
}