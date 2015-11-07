/*

 */

// CONFIGURATION VARS
int data[8];                    // array for holding received data
const bool dataPersist = true;  // choose whether to keep old data if no RX

// OTHER GLOBALS
String inputString = "";        // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
const int dataSize = sizeof(data)/sizeof(int);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(128);
}

void loop() {
  // print X, Y when a newline arrives:
  if (stringComplete) {
    // parse serial str into data
    parseSerial(inputString);

    sendData();

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
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

void sendData() {
  String xs = "x=";  // hacky fix for string concatenation below
  Serial.println(xs + data[0] + "\ty=" + data[1]);
}
