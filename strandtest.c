#include <ESP8266HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include<ArduinoJson.h>

#define LED_PIN1 D5     //네오픽셀에 신호를 줄 핀번호
#define LED_PIN2 D6     //네오픽셀에 신호를 줄 핀번호
#define LED_PIN3 D7     //네오픽셀에 신호를 줄 핀번호

const char* wifi = "bssm_free";
const char* password = "bssm_free";
const String url = "http://10.150.150.191:8080/density/all?camera=1";


  int R1 = 0;
  int R2 = 0;
  int R3 = 0;
  int G1 = 0;
  int G2 = 0;
  int G3 = 0;
  int delay_time = 100;

WiFiClient wifiClient;

Adafruit_NeoPixel strip1(11, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(11, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(11, LED_PIN3, NEO_GRB + NEO_KHZ800);

// Adafruit_NeoPixel strip(LED_COUNT, LED_PIN3, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip(LED_COUNT, LED_PIN4 NEO_GRB + NEO_KHZ800);
// 라이브러리에서 네오픽셀 객체를 선언
// 첫번째 인자 = 네오픽셀의 개수
// 두번째 인자 = 신호를 출력할 핀번호
// 세번째 인자 = 네오픽셀의 종류에따라 맞는 것을 아래대로 설정해주면 된다.
/*
     * 종류에 따른 설정
     * NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs) 
     * NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
     * 
     * NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
     * NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
     * NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
     */

void setup() {
  Serial.begin(115200);
  delay(4000);  //Delay needed before calling the WiFi.begin

  WiFi.begin(wifi, password);

  while (WiFi.status() != WL_CONNECTED) {  //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
   
  strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();            // 네오픽셀에 빛을 출력하기 위한 것인데 여기서는 모든 네오픽셀을 OFF하기 위해서 사용한다.
  strip1.setBrightness(10);
  
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.show();            // 네오픽셀에 빛을 출력하기 위한 것인데 여기서는 모든 네오픽셀을 OFF하기 위해서 사용한다.
  strip2.setBrightness(10); // 네오픽셀의 밝기 설정(최대 255까지 가능)
  
  strip3.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip3.show();            // 네오픽셀에 빛을 출력하기 위한 것인데 여기서는 모든 네오픽셀을 OFF하기 위해서 사용한다.
  strip3.setBrightness(10); // 네오픽셀의 밝기 설정(최대 255까지 가능)

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.GET();
    //Send the actual POST request
    if (httpCode > 0) {

      // String vom Webseiteninhalt speichern
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      // Parameters
      const String cameraId_1 = root["densityList"][0]["cameraId"];
      const String cameraId_2 = root["densityList"][1]["cameraId"];
      const String cameraId_3 = root["densityList"][2]["cameraId"];

      const String code_1 = root["densityList"][0]["code"];
      const String code_2 = root["densityList"][1]["code"];
      const String code_3 = root["densityList"][2]["code"];

      Serial.println(cameraId_1 + "와" + code_1);
      Serial.println(cameraId_2 + "와" + code_2);
      Serial.println(cameraId_3 + "와" + code_3);


    if(code_1 == "NICE"){
      R1 = 0;
      G1 = 255;
    }else if(code_1 == "CAUTION"){
      R1 = 255;
      G1 = 255;
    }else{
      R1 = 255;
      G1 = 0;
    }

    if(code_2 == "NICE"){
      R2 = 0;
      G2 = 255;
    }else if(code_2 == "CAUTION"){
      R2 = 255;
      G2 = 255;
    }else{
      R2 = 255;
      G2 = 0;
    }


    if(code_3 == "NICE"){
      R3 = 0;
      G3 = 255;
    }else if(code_3 == "CAUTION"){
      R3 = 255;
      G3 = 255;
    }else{
      R3 = 255;
      G3 = 0;
    }

  for(int i = 0; i<12; i++){
      strip1.setPixelColor(i, R1, G1, 0);
      strip2.setPixelColor(i, R2, G2, 0);
      strip3.setPixelColor(i, R3, G3, 0);
      strip1.show();
      strip2.show();
      strip3.show();
      delay(delay_time);
  }

  
  for(int i = 0; i<12; i++){
      strip1.setPixelColor(i, 0, 0, 0);
      strip2.setPixelColor(i, 0, 0, 0);
      strip3.setPixelColor(i, 0, 0, 0);
      strip1.show();
      strip2.show();
      strip3.show();
      delay(delay_time);
  }

    } else {
      // Falls HTTP-Error
      Serial.printf("HTTP-Error: ", http.errorToString(httpCode).c_str());
    }

    // Wenn alles abgeschlossen ist, wird die Verbindung wieder beendet
    http.end();

  } else {
    Serial.printf("HTTP-Verbindung konnte nicht hergestellt werden!");
  }

}
