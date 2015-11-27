/*
    header block
 */
#ifndef SERIAL_CSV
#define SERIAL_CSV

#define faceX data[0]
#define faceY data[1]
#define faceSize data[2]
#define numFaces data[3]

// CONFIGURATION VARS
int data[8];                    // array for holding received data
const bool dataPersist = true;  // choose whether to keep old data if no RX    mood = 1;

// OTHER GLOBALS
String inputString = "";        // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
const int dataSize = sizeof(data)/sizeof(int);  // calc size of data array
bool serialInitialised = false; // has init been run?

// int faceX = 0;
// int faceY = 0;
// int faceSize = 0;
// int numFaces = 0;

void initSerial() {
    // initialize serial:
    if(!Serial) Serial.begin(9600);
    // reserve 200 bytes for the inputString:
    inputString.reserve(128);
    serialInitialised = true;
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline or end bracket, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == ']') {
      stringComplete = true;
    }
  }
}

void parseSerial(String str) {
  // ****better to use strchr, strtok, atoi from standard C - faster
  // trim to square brackets
  int start = str.indexOf('[');
  int end = str.indexOf(']');
  if (start >= 0 && end >= 0) str = str.substring(start + 1, end) + ",";
  else str = "";  // no good data

  // step through CSVs
  int index = 0;
  while (str.length() > 0) {
    int comma = str.indexOf(','); // find next comma
    data[index] = str.substring(0, comma).toInt();  // store all before comma
    str = str.substring(comma+1, str.length()); // trim taken data from str
    index++;  // increment through data array
  }
  if (!dataPersist) while (index < dataSize) {
    data[index] = 0; // clear out remaining data
    index++;
  }
}

void printData() {
  String xs = "x=";  // hacky fix for string concatenation below
  xs = xs + data[0] + "\ty=" + data[1];
  xs = xs + "\tsize=" + data[2] + "\tfaces=" + data[3];
  Serial.println(xs);
}

void loopSerial() {
    if (!serialInitialised) initSerial();   // initialise if not already

    // print X, Y when a newline arrives:
    if (stringComplete) {
        // parse serial str into data
        parseSerial(inputString);

        // move data to readable vars - actually do this as define for speed?
        // printData();
        // faceX = data[0];
        // faceY = data[1];
        // faceSize = data[2];
        // numFaces = data[3];

        // clear the string, ready for next time:
        inputString = "";
        stringComplete = false;
    }
}

#endif
