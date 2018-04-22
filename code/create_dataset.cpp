#include <iostream>
#include <string.h>
#include <stdio.h>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

//namesapce
using namespace std;
using namespace cv;

int main(){
    //capture video with camera 1
    VideoCapture vdo(0);
    int num=0;//id and num is number of image training
    char id[30], path[100];
    printf("enter id");
    scanf("%s", id);

    //cascade and load
    String face_cascade_name = "haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;

    face_cascade.load(face_cascade_name);

    //loop frame-by-frame
    while(1){
        //define var frame type Mat
        Mat frame;


        //mem vdo to var frame
        vdo >> frame;

        //define var faces type vector rectangle
        vector<Rect> faces;

        //convert frame to gray scale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        //detection face
        face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

        //loop draw rectangular
        for(size_t i=0;i<faces.size();i++){

            //point begin and end of faces
            Point f_begin(faces[i].x, faces[i].y);
            Point f_end(faces[i].x + faces[i].width , faces[i].y + faces[i].height);

            Rect crop = Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
            Mat cropimage = gray(crop);


            num++;
            sprintf(path, "user/user1.%d.jpg", num+100);
            imwrite(path, cropimage);

            waitKey(1);

            //draw rectangular
            rectangle(frame, f_begin, f_end, Scalar(0, 255, 0), 2);
        }
        imshow("face", frame);

        if (num >= 100) break;
        waitKey(1);


    }
    return 0;
}
