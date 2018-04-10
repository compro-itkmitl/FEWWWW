#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
//This is opencv Libary path

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;
//use namespace because not write name libary

int main(){
    cout << "start face rec PLEASE WAIT..." << endl;
	
	//define model face recognizer
    Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
	//read model
	model -> read("trainingdata.yml");
	
	//cascade face
	CascadeClassifier face_cascade;
	string classifier = "haarcascade_frontalface_alt.xml";
	face_cascade.load(classifier);

	string window = "cap_faceDetection";

	//capture vdo camera 1
	VideoCapture vdo(0);
	namedWindow(window, 1);

	while(1){
		//define val type Mat
		Mat frame, gray_scale;

		//define type vector rectangular
		vector<Rect> faces;

		vdo >> frame;


		//check vdo is emthy
		if(!frame.empty()){
			cvtColor(frame, gray_scale, COLOR_BGR2GRAY);
			equalizeHist(gray_scale, gray_scale);

			//detect
			face_cascade.detectMultiScale(gray_scale, faces, 1.1, 3, 0|CASCADE_SCALE_IMAGE, Size(60, 60));

			//define label of user and confidence and name
			int label = 0;
			double confidence = 0;
			string name_user = "";

			for(int i=0;i<faces.size();i++){
				//point begin and end of faces
				Rect face_num = faces[i];
            	Point f_begin(faces[i].x, faces[i].y);
            	Point f_end(faces[i].x + faces[i].width , faces[i].y + faces[i].height);

            	Rect crop = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
           		Mat cropimage = gray_scale(crop);
				imshow("f", cropimage);

				rectangle(frame, face_num,CV_RGB(0, 255, 0), 2);

				int predict_label = -1;
				double confidence = 0.0;
				model -> predict(cropimage,predict_label, confidence);

				cout << confidence << endl;
				if(predict_label == 1){
					if(confidence <= 45){
						name_user = "khing";
					}
					else{
						name_user = "unknown";
					}
				}
				else if(predict_label == 2){
					if(confidence <= 50){
						name_user = "platty";
					}
					else{
						name_user = "unknown";
					}
				}
				else{
					if(confidence <= 50){
						name_user = "Ped";
					}
					else{
						name_user = "unknown";
					}
				}
				putText(frame, name_user, Point(faces[i].x, faces[i].y+faces[i].height), FONT_HERSHEY_COMPLEX_SMALL, 3.0, CV_RGB(0, 0, 0), 3.0);
				
			}
			
			imshow(window, frame);
			waitKey(1);
			

		}

	}
	return 0;
}