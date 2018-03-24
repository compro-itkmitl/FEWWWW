#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

static void read_f(const string& name, vector<Mat>& img, vector<int> labels){

	std::ifstream file(name.c_str(), ifstram::in);

	string line, path, label;
	while(getline(file, line)){

		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, label);
		if(!path.emthy() && !label.emthy()){
			img.push_back(imread(path, 0));
			labels.push_back(atoi(label.c_str()));
		}
	}
}


void LBPHFace(){
	vector<Mat> img;
	vector<int> labels;
	try{
		string name = "check.txt";
		read_f(name, img, labels);

		cout << "size of the images is "<<img.size()<<endl;
		cout << "size of the labels is " << labels.size() << endl;
		cout << "training" << endl;

	}
	catch(cv::Exception& e){
		cerr << "Error open file" << e.msg << endl;
		exit(1);
	}

	Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();

	model -> train(img, labels);
	model -> save("check.yml");
	cout << "finish" << endl;

	waitKey(1000);
}