#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void detect_keypoints();

int main(void)
{
	detect_keypoints();

	return 0;
}

// KeyPoint 검출 예제
void detect_keypoints()
{
	// box_in_scene.png를 GrayScale 이미지로 Mat 형태로 저장
	Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();	// ORB 클래스 객체를 생성하여 feature 스마트 포인터에 저장

	vector<KeyPoint> keypoints;	// Keypoint를 저장할 Vector 생성
	feature->detect(src, keypoints);	// ORB 알고리즘을 이용하여 특징점 찾기
	// (입력 영상, 검출된 키포인트 정보)

	Mat desc;	// 특징점 기술자를 추출할 기술자 행렬 생성 (열 - 사용하는 알고리즘에 의해 결정, 행 - 특징점의 갯수)
	feature->compute(src, keypoints, desc);	// (입력 영상, 미리 검출해 둔 Keypoint 정보, 계산된 기술자 행렬)

	// feature->detectAndCompute(src, Mat(), keypoints, desc);	// detect()와 compute()를 동시에 수행
	// (입력 영상, 마스크 행렬, keypoint 담을 Vector, 기술자 행렬)

	cout << "keypoints.size(): " << keypoints.size() << endl;
	cout << "desc.size(): " << desc.size() << endl;

	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);	// 키포인트 위에 원을 그려서 표시한 영상 반환
	// (입력 영상, 검출된 keypoints, 출력 영상, Key point Color, Key point 그리기 방법)

	// 이미지 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey();			// 키보드가 눌러질 때까지 기다리는 함수
	destroyAllWindows();			// 모든 창을 닫는다.
}