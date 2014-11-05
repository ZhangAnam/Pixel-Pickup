//============================================================================
// Name        : Pixel-Pickup.cpp
// Author      : ZhangAnam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define KEY_ESC 27
#define VK_LEFT 81
#define VK_UP 82
#define VK_RIGHT 83
#define VK_DOWN 84

using namespace std;
using namespace cv;

typedef struct _subRect
{
	int width;
	int height;
	int x;
	int y;
} subRect;

void on_Mouse(int event, int x, int y, int flag, void* param){
	subRect* rect = (subRect*) param;
	rect->x = x;
	rect->y = y;

	if(event == CV_EVENT_LBUTTONUP)
	{
		cout << "x:" << x << "  |   y:" << y << endl;
	}
}

int main() {
	subRect rect;
	rect.height = 100;
	rect.width = 100;
	rect.x = 0;
	rect.y = 0;

	VideoCapture cap(0);
	while(true){
		Mat frame;
		cap >> frame;
		int key = waitKey(30) %256;
		switch(key){
		case VK_UP:
			if(frame.rows > 0 && rect.width < frame.cols - 1 - 5 && rect.height < frame.rows- 1 - 5){
				rect.height +=5;
				rect.width +=5;
			}
			break;
		case VK_DOWN:
			if(frame.rows > 0 && rect.width >5   && rect.height > 5){
				rect.height -=5;
				rect.width -=5;
			}
			break;
		case VK_LEFT:
			if(frame.cols > 0 && rect.width > 20 && rect.height > 20){
				rect.height -=20;
				rect.width -=20;
			}
			break;
		case VK_RIGHT:
			if(frame.cols > 0 && rect.width < frame.cols - 1 - 20 && rect.height < frame.rows- 1 - 20 ){
				rect.height +=20;
				rect.width +=20;
			}
			break;
		}

		if(key == KEY_ESC){
			break;
		}

		setMouseCallback("video",on_Mouse,(void*)&rect);
		int x1 = rect.x - rect.width/2;
		int x2 = rect.x + rect.width/2;
		int y1 = rect.y - rect.height/2;
		int y2 = rect.y + rect.height/2;
		if(x1<0){
			x2-=x1;
			x1 = 0;
		}
		if(x2>frame.cols-1){
			x1+=frame.cols-1-x2;
			x2 = frame.cols-1;
		}
		if(y1<0){
			y2-=y1;
			y1 = 0;
		}
		if(y2>frame.rows-1){
			y1+=frame.rows-1-y2;
			y2 = frame.rows-1;
		}
		Mat detail;
		resize(frame.rowRange(y1,y2).colRange(x1,x2),detail,Size(301,301));
		line(detail,Point2i(150,130),Point2i(150,170),Scalar(0,0,255));
		line(detail,Point2i(130,150),Point2i(170,150),Scalar(0,0,255));

		rectangle(frame,Point2i(x1,y1),Point2i(x2,y2),Scalar::all(255),3);

		if (!frame.empty()){
			imshow("video",frame);
			imshow("detail",detail);
		}

	}
	cap.release();
	return 0;
}
