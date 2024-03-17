#include <Adafruit_ST7735.h> // Hardware-specific library
// wifi lib
#include <WiFi.h>
// http request to SMS API server
#include <HTTPClient.h>
#include <base64.h> // to encode Auth

// define pins for screen output
#define TFT_CS     15 // Chip select line for TFT display
#define TFT_RST    4  // Reset line for TFT (or connect to +5V)
#define TFT_DC     2  // Data/command line for TFT
#define TFT_SDA    23 // Data out from ESP32 to TFT
#define TFT_SCL    18 // Clock from ESP32 to TFT
#define TFT_BL     5  // Backlight control
// door sensor
#define DOOR_SENSOR_PIN  19  // ESP32 pin GPIO19 connected to door sensor's pin

// Wifi SSID and password of client router. 
const char* SSID = " ";
const char* PASSWORD = " ";

// tft screen object 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

bool validateDoorOpen = true;

// init wifi 
void initWifiConnection(){
  WiFi.mode(WIFI_STA); // define ESP32 as Station mode.
  WiFi.disconnect(); // reset wifi resources.

  // "bind" the connection, and loop until success to connect. 
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {

  }
}

// send SMS method that connect API by http request
void sendSMS() {
  // 1. string url


  // 2. Construct SID & Authentication Token header

  
  // 3. to - des phone & from - source phone 

  
  // encode the value to pass it as a POST
  String encodedAuth = base64::encode(auth); 

  // Send HTTPS POST request
  HTTPClient http;
  http.begin(url);
  http.addHeader("Authorization", "Basic " + encodedAuth);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(data);

  delay(1000);

  if (httpResponseCode > 0) {
    printTFT(40, 20, String(httpResponseCode));
  } else {
    printTFT(40, 20, String(httpResponseCode));
  }
  http.end();
  delay(1000);
  cleanSectionTFT(40,20);
  
}

// print to tft screen 
// input: Coordinate & string
void printTFT(int x, int y, String str){
  tft.setCursor(y, x);
  tft.print(str);
}
// clean specific section 
void cleanSectionTFT(int x, int y){
  tft.fillRect(y, x, 100, 10, ST7735_BLACK);
}
// clean & draw BLACK screen
void cleanAllScreen(){
  tft.fillScreen(ST7735_BLACK);
}

void scanWIFI(){
  int n = WiFi.scanNetworks();

  while(n == 0){n = WiFi.scanNetworks();}

  for(int i = 0, j = 50; i < n && i < 3; i++, j += 10){
    printTFT(j, 10, String(WiFi.SSID(i)));
  }
}

void setup() {
  Serial.begin(115200);

  // tft screen section
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK); // fill the screen with black color
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);

  // scan wifi print
  printTFT(20,10, "Search WIFI...");
  scanWIFI();
  delay(5000);

  // init Wifi
  cleanAllScreen();
  printTFT(20,10, "WIFI connecting..");
  initWifiConnection();
  printTFT(30,10, "WIFI connect");
  printTFT(40,10, "succeeded");
  delay(3000);
  cleanAllScreen();

  printTFT(20,10, "WIFI:" + String(SSID));
  printTFT(30,10, "OK...");

  // set pin for DoorOpen sensor 
  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP); // set ESP32 pin to input pull-up mode
}


void loop() {

  if(WiFi.status() == 5){
    cleanAllScreen();
    printTFT(20,10, "connecting back..");
    WiFi.reconnect();
    delay(2000);
    cleanAllScreen();
    printTFT(20,10, "WIFI:" + String(SSID));
    printTFT(30,10, "OK...");
  }
  else{
    if(digitalRead(DOOR_SENSOR_PIN) == HIGH && validateDoorOpen)
    {
      tft.fillRect(20, 80, 50, 20, ST7735_RED);
      sendSMS();
      printTFT(20,10, "WIFI:" + String(SSID));
      printTFT(30,10, "OK...");
      validateDoorOpen = false;
    }
    else if(digitalRead(DOOR_SENSOR_PIN) == LOW){

      tft.fillRect(20, 80, 50, 20, ST7735_GREEN);
      validateDoorOpen = true;
    }
    else{

    } 
  }

}
