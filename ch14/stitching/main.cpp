#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// ubuntu 18.04에서 실행시킬 때, compile후 terminal창에서 인자를 직접 넣어주어야 합니다.
// ctrl + alt + C를 눌러 컴파일 한 후, 터미널 창에 ./stitching img1.jpg img2.jpg img3.jpg으로 excute하면 됩니다.

// 영상 이어 붙이기 예제
int main(int argc, char* argv[])
{
	// 명령형 인자 개수가 3보다 작으면 프로그램 종료
	if (argc < 3) {
		cerr << "Usage: stitching.exe <image_file1> <image_file2> [<image_file3> ...]" << endl;
		return -1;
	}

	vector<Mat> imgs;
	for (int i = 1; i < argc; i++) {
		Mat img = imread(argv[i]);	// 명령형 인자로 전달 받은 파일을 Mat 형태로 저장

		// 이미지를 잘 불러왔는지 확인
		if (img.empty()) {
			cerr << "Image load failed!" << endl;
			return -1;
		}

		imgs.push_back(img);	// vector에 image를 담는다.
	}

	Ptr<Stitcher> stitcher = Stitcher::create();	// Stitcher 객체 생성

	Mat dst;
	Stitcher::Status status = stitcher->stitch(imgs, dst);	// Stitching 수행 후 결과 영상에 저장

	// Stitcing이 잘 되는지 확인
	if (status != Stitcher::Status::OK) {
		cerr << "Error on stitching!" << endl;
		return -1;
	}

	imwrite("result.jpg", dst);	// 결과 영상 저장

	imshow("dst", dst);	// 이미지 출력

	waitKey();		// 키 입력을 기다리는 함수
	return 0;
}