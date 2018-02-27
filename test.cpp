#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp> 
#include <vector>
#include <cstdio>

using namespace std;
using namespace cv;

int main()
{
	Mat grayImage, dstImage;
	// 定义7种颜色，用于标记人脸
	Scalar colors[] =
	{
		// 红橙黄绿青蓝紫
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};
	// 【1】加载分类器
	CascadeClassifier cascade;
	printf("load xml/n");
	cascade.load("haarcascade_frontalface_alt.xml");

	CvCapture* capture = 0;
	//capture = cvCaptureFromAVI("vid.wmv");
	capture = cvCaptureFromCAM(0);
	if (!capture)
	{
		cerr << "cannot initialize video!" << endl;
		return -1;
	}
	Mat Image, current_shape;
	for (;;){
		IplImage* iplImg = cvQueryFrame(capture);
		//Image(iplImg,true);
		Image = cvarrToMat(iplImg);
		flip(Image, Image, 1);//使用摄像头时需要翻转图像

		Mat readImage;
		readImage = imread("bald_guys.jpg",0);
		cvtColor(Image, grayImage, CV_BGR2GRAY); // 生成灰度图，提高检测效率
		// 【3】检测
		vector<Rect> rect;
		cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用

		printf("检测到人脸个数：%d\n", rect.size());
		/*
		// 【4】标记--在脸部画圆
		for (int i = 0; i < rect.size(); i++)
		{
			Point center;
			int radius;
			center.x = cvRound((rect[i].x + rect[i].width * 0.5));
			center.y = cvRound((rect[i].y + rect[i].height * 0.5));

			radius = cvRound((rect[i].width + rect[i].height) * 0.25);
			circle(Image, center, radius, colors[i % 7], 2);
		}
		*/
		for (vector<Rect>::const_iterator r = rect.begin(); r != rect.end(); r++)
        rectangle(Image, cvPoint(r->x, r->y), cvPoint(r->x + r->width - 1, r->y + r->height - 1), Scalar(255, 0, 255), 3, 8, 0);

		//文字标注
		//putText(imgForShow, p.first, Point(BBox.x, BBox.y), FONT_HERSHEY_PLAIN, 2, Scalar(255, 0, 0));
		namedWindow("1", CV_WINDOW_AUTOSIZE);
		imshow("1", Image);
		waitKey(3);
	}

	return 0;
}
