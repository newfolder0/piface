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

int main() {

  std::ostringstream buffer;
  int x = 4;
  int y = 6;

  vector<int> data;
  data.push_back(x);
  data.push_back(y);

  FILE *file;

  // build string to send
  buffer << "[";
  for (int i = 0; i < data.size(); i++) {
    if (i > 0) buffer << ",";
    buffer << data[i];
  }
  buffer << "]";

  printf("Sending: %s\n", buffer.str().c_str());

  file = fopen("/dev/ttyACM0", "w");  // open device
  fprintf(file, "%s", buffer.str().c_str());  // send buffer
  fclose(file);
}
