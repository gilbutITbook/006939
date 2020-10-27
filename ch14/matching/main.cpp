#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// 함수 사용을 위해 미리 선언
void keypoint_matching();
void good_matching();
void find_homography();

// 주석을 이용하여 원하는 부분만 출력
int main(void)
{
	keypoint_matching();
	good_matching();
	find_homography();

	return 0;
}

// KeyPoint Matching 예제
void keypoint_matching()
{
	// box.png, box_in_scene.png를 1 채널 GrayScale 이미지로 Mat 형태로 저장
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();	// ORB 클래스 객체를 생성하여 feature 스마트 포인터에 저장

	vector<KeyPoint> keypoints1, keypoints2;	// Keypoint를 담을 Vector 2개 생성
	Mat desc1, desc2;	// 기술자를 담을 Mat 2개 생성
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);	// 특징점을 검출하고 기술자를 동시에 계산
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);	// (입력 영상, 마스크 행렬, 검출된 키포인트 정보, 계산된 기술자 행렬)
	cout << "desc1.size(): " << desc1.size() << endl;
	cout << "desc2.size(): " << desc2.size() << endl;

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);	// BF(Bruce-Force)Matcher 클래스 객체 생성 (해밍 거리를 사용하여 거리 계산)

	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);	// match()를 이용하여 desc1과 desc2를 매칭, 그 결과를 matches에 저장

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);	// 두 영상을 가로로 이어 붙이고, 매칭 결과를 다양한 색상으로 표현
	// (입력 영상1, 특징점1, 입력 영상2, 특징점2, 매칭 정보, 출력 영상)

	imshow("dst", dst);	// 이미지 출력

	waitKey();			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}

// Key Point Matching 후 좋은 매칭 선별 예제
void good_matching()
{
	// box.png, box_in_scene.png를 1 채널 GrayScale 이미지로 Mat 형태로 저장
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();	// ORB 클래스 객체를 생성하여 feature 스마트 포인터에 저장

	vector<KeyPoint> keypoints1, keypoints2;	// Keypoint를 담을 Vector 2개 생성
	Mat desc1, desc2;	// 기술자를 담을 Mat 2개 생성
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);	// 특징점을 검출하고 기술자를 동시에 계산
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);	// (입력 영상, 마스크 행렬, 검출된 키포인트 정보, 계산된 기술자 행렬)

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);	// BF(Bruce-Force)Matcher 클래스 객체 생성 (해밍 거리를 사용하여 거리 계산)

	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);	// match()를 이용하여 desc1과 desc2를 매칭, 그 결과를 matches에 저장

	std::sort(matches.begin(), matches.end());	// 특징점 매칭 결과 정렬
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);	// 특징점 매칭 결과 중 상위 50개 선별

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	// 두 영상을 가로로 이어 붙이고, 매칭 결과를 다양한 색상으로 표현
	// (입력 영상1, 특징점1, 입력 영상2, 특징점2, 매칭 정보, 출력 영상, 맨 마지막 flag - 매칭 되지 않은 특징점은 화면에 표시 안함)

	imshow("dst", dst);	// 이미지 출력

	waitKey();			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}

void find_homography()
{
	// box.png, box_in_scene.png를 1 채널 GrayScale 이미지로 Mat 형태로 저장
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	// 이미지를 잘 불러왔는지 확인
	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();	// ORB 클래스 객체를 생성하여 feature 스마트 포인터에 저장

	vector<KeyPoint> keypoints1, keypoints2;	// Keypoint를 담을 Vector 2개 생성
	Mat desc1, desc2;	// 기술자를 담을 Mat 2개 생성
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);	// 특징점을 검출하고 기술자를 동시에 계산
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);	// (입력 영상, 마스크 행렬, 검출된 키포인트 정보, 계산된 기술자 행렬)

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);	// BF(Bruce-Force)Matcher 클래스 객체 생성 (해밍 거리를 사용하여 거리 계산)

	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);	// match()를 이용하여 desc1과 desc2를 매칭, 그 결과를 matches에 저장

	std::sort(matches.begin(), matches.end());	// 특징점 매칭 결과 정렬
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);	// 특징점 매칭 결과 중 상위 50개 선별

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	// 두 영상을 가로로 이어 붙이고, 매칭 결과를 다양한 색상으로 표현
	// (입력 영상1, 특징점1, 입력 영상2, 특징점2, 매칭 정보, 출력 영상, 맨 마지막 flag - 매칭 되지 않은 특징점은 화면에 표시 안함)

	vector<Point2f> pts1, pts2;	// query영상과 train영상의 특징점 좌표를 추출하여 vector로 저장
	for (size_t i = 0; i < good_matches.size(); i++) {
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(pts1, pts2, RANSAC);	// pts1 점들과 pts2 점들을 가지고 RANSAC을 이용하여 Homography 행렬을 찾는다.

	vector<Point2f> corners1, corners2;	//src의 모서리를 corners1에 저장
	corners1.push_back(Point2f(0, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, H);	// Homography 행렬을 이용하여 점들을 corners2로 이동시킨다.

	vector<Point> corners_dst;
	// 범위 기반 반복문 사용, corners2 벡터에 있는 모든 원소들을 하나씩 꺼내서 사용
	for (Point2f pt : corners2) {
		corners_dst.push_back(Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
		// 매칭 영상 dst에서 corners2 점들이 위치하는 좌표를 corners_dst에 저장한다.
	}

	polylines(dst, corners_dst, true, Scalar(0, 255, 0), 2, LINE_AA);	
	// 입출력 이미지, 좌표 배열, 폐곡선, Green, Thickness = 2, 안티에일리어싱

	imshow("dst", dst);	// 이미지 출력

	waitKey();			// 키 입력을 기다리는 함수
	destroyAllWindows();			// 모든 창이 소멸
}