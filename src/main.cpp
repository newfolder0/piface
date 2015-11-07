/**
 * @file objectDetection2.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face) in a video stream - Using LBP here
 */
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectFaces(Mat frame);
void sendLargeFace();
void sendData();

/** Modes */
const bool DEBUG = false;
const int CAM = 0;  // 0 for laptop
const String CASCADE = "lbp"; // haar or lbp

/** Global variables */
String cascade_file = "./src/cascades/" + CASCADE + "cascade_frontalface.xml";
CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";
vector<Rect> faces;  // data store faces
vector<int> data; // data to send


/**
 * @function main
 */
int main( void ) {
    VideoCapture capture;
    Mat frame;

    // load the cascade
    if( !face_cascade.load(cascade_file)) { printf("--(!)Error loading face cascade\n"); return -1; };

    // read the video stream
    capture.open(CAM);
    if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

    while (capture.read(frame)) {
        if(frame.empty()) {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        // need to return faces? Or pointers?

        // apply the classifier to the frame
        detectFaces(frame);

        // send largest face to arduino
        sendLargeFace();

        // bail out if escape was pressed
        int c = waitKey(10);
        if((char)c == 27) { break; };
    }
    return 0;
}

/**
 * @function detectFaces
 */
void detectFaces(Mat frame) {
    Mat frame_grey;

    cvtColor(frame, frame_grey, COLOR_BGR2GRAY);
    equalizeHist(frame_grey, frame_grey);

    // detect faces - store points instead?
    face_cascade.detectMultiScale(frame_grey, faces, 1.1, 2, 0, Size(80, 80));

    if (DEBUG) {
      for(size_t i = 0; i < faces.size(); i++) {

        // draw the face
        Point centre(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
        ellipse(frame, centre, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(255, 0, 0), 2, 8, 0);
      }

      // show video
      imshow(window_name, frame);
    }

}

/**
 * @function sendLargeFace
 */
void sendLargeFace() {
  int l = 0; // index of largest face

  // find largest face
  for (int i = 1; i < faces.size(); i++) {
    if (faces[i].area() > faces[l].area()) l = i;
  }

  // get centre of face
  Point centre(faces[l].x + faces[l].width/2, faces[l].y + faces[l].height/2);
  data.clear();
  data.push_back(centre.x);
  data.push_back(centre.y);

  // send face
  sendData();
}

 /**
  * @function sendData
  */
void sendData() {
  FILE *file;
  std::ostringstream buffer;

  // build string to send
  buffer << "[";
  for (int i = 0; i < data.size(); i++) {
    if (i > 0) buffer << ",";
    buffer << data[i];
  }
  buffer << "]";

  if (DEBUG) printf("%s\n", buffer.str().c_str());  // print to console

  file = fopen("/dev/ttyACM0", "w");  // open device
  fprintf(file, "%s", buffer.str().c_str());  // send buffer
  fclose(file);
}