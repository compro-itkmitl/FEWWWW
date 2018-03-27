#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;
using namespace cv::face;

int main(){
	cout << "face recognizing is begin" << endl;

	//load trainer data
	Ptr<LBPHFaceRecognizer> model_face = createLBPHFaceRecognizer();
	model_face -> load("trainingdata.yml");

	//load face algolithm haar cascading
	string face_classifier = "haarcascade_frontalface_alt.xml";
	CascadeClassifier face_cascade;
	face_cascade.load(face_classifier);

	//record vdo camera 1 (0 is camera 1 and 1 is camera 2)
	VideoCapture vdo(0);
	//count frame
	int count = 0;
	while(1){
		count++;
		//create frame type Mat
		Mat frame, grayscale, og;
		
		//create vector name faces type Rectangular
		vector<Rect> face;

		//add vdo frame by frame to var. frame
		vdo >> frame

		//check frame not emthy
		if(!frame.emthy()){
			//convert color image bgr to grayscale and save in var.grayscale
			cvtColor(frame, grayscale, COLOR_BGR2GRAY);
			equalizeHist(grayscale, grayscale);

			//detect
			face_cascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

			//username
			string user_name;
			for(int i=0;i<faces.size();i++){
				 //point begin and end of faces
            	Point f_begin(faces[i].x, faces[i].y);
            	Point f_end(faces[i].x + faces[i].width , faces[i].y + faces[i].height);

            	Rect crop = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
            	Mat cropimage = gray(crop);

            	waitKey(1);

            	//draw rectangular
            	rectangle(frame, f_begin, f_end, Scalar(0, 255, 0), 2);
			}
			
		}
		char c=(char)waitKey(30);
		if (c == 27) break;
	}

	destroyAllWindows();
	return 0;
}