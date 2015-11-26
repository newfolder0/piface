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

/** Config vars */
const bool DEBUG = true;
const int CAM = 1;  // 0 for laptop
const int X_MAX = 640; // camera is 640x480
const int Y_MAX = 480; // camera is 640x480
const char* LBP_CASCADE = "lbpcascade_frontalface.xml"; // haar or lbp
const char* HAAR_CASCADE = "haarcascade_frontalface_alt.xml";
const String CASCADE = HAAR_CASCADE;
const int PERSISTENCE = 5;

/** Global variables */
String cascade_file = "./src/cascades/" + CASCADE;
CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";
vector<Rect> faces;  // data store faces
vector<Rect> newFaces;  // newly detected faces
int changeCount = PERSISTENCE;
vector<int> data; // data to send


/**
 * @function main
 */
int main(int argc, char* argv[]) {
    // if (argc > 1)

    printf("\n%i", argc);
    for (int i = 0; i < argc; i++) {
        printf("\n%s", argv[i]);
    }

    Mat frame;

    // load the cascade
    if( !face_cascade.load(cascade_file)) { printf("--(!)Error loading face cascade\n"); return -1; };

    // read the video stream - 640x480
    VideoCapture capture(CAM);
    if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

    // these don't seem to work, if fixed remove any resize step
    // capture.set(CV_CAP_PROP_FRAME_WIDTH, X_MAX);
    // capture.set(CV_CAP_PROP_FRAME_HEIGHT, Y_MAX);
    // capture.set(CV_CAP_PROP_FPS, 1);


    // for (int i = 0; i<1; i++) {
    for (;;) {
        capture.read(frame);    // capture frame

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

        // usleep(100000); // delay introduced to slow data rate - should slow FPS
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

    // classifier settings
    double scaleFactor = 1.1;   // bigger is faster but less thorough with face size, default = 1.1
    int minNeighbours = 2;  // bigger means higher quality with less false positives (doesn't affect speed), default = 2
    int flags = 0;  // default = 0, CV_HAAR_DO_CANNY_PRUNING might speed things up - or CV_HAAR_FIND_BIGGEST_OBJECT
    int minSize = 5;    // minimum detected face size (square), default = 80

    // detect faces
    face_cascade.detectMultiScale(frame_grey,
                                newFaces,
                                scaleFactor,
                                minNeighbours,
                                flags,
                                Size(minSize,minSize));

    // if number of faces changes then persist for a few frames - for jitter
    // currently kicks in when number of faces changes
    // might be better if it is only when all disappear or largest changes
    if (newFaces.size() == faces.size()) {
        faces = newFaces;
    } else {
        if (changeCount < PERSISTENCE) {
            changeCount++;
        } else {
            faces = newFaces;
            changeCount = 0;
        }
    }

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
    int x, y, width;    // coordinates of centre of face, width of face
    int numFaces = faces.size();

    if (numFaces > 0) { // if at least one face exists

        int l = 0;  // instantiate index of largest face

        // find largest face in vector of faces
        for (int i = 1; i < faces.size(); i++) {
            if (faces[i].area() > faces[l].area()) l = i;
        }

        // get centre of face
        x = faces[l].x + faces[l].width/2;
        y = faces[l].y + faces[l].height/2;
        y = Y_MAX - y;  // invert vertical axis

        width = faces[l].width;

    } else {    // if no faces found
        // default values
        x = X_MAX / 2;
        y = Y_MAX / 2;
        width = 0;
    }

    data.clear();
    data.push_back(x);
    data.push_back(y);
    data.push_back(width);
    data.push_back(numFaces);

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

    if (file == NULL) printf("ERROR: Failed to connect to Arduino device!\n");
    else {  // send buffer and close device
        fprintf(file, "%s", buffer.str().c_str());
        fclose(file);
    }
}
