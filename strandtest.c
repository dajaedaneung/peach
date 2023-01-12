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

      
      if(cameraId_1 == "1"){
        if(code_1 == "NICE"){
            for(int j = 0; j < 12; j++){
              strip1.setPixelColor(j, strip1.Color(0, 255, 0));
          }
          strip1.show();
          }
          else if(code_1 == "NORMAL"){
            for(int j = 0; j < 12; j++){
              strip1.setPixelColor(j, strip1.Color(255, 255, 0));
            }
            strip1.show();
          }
          else if(code_1 == "WARNING"){
            for(int j = 0; j < 12; j++){
              strip1.setPixelColor(j, strip1.Color(255, 0, 0));
            }
          strip1.show();
          }
      }

      if(cameraId_2 == "2"){
          if(code_2 == "NORMAL"){
            for(int j = 0; j < 12; j++){
              strip2.setPixelColor(j, strip2.Color(255, 255, 0));
            }
            strip2.show();
          }else if(code_2 == "NICE"){
            for(int j = 0; j < 12; j++){
              strip2.setPixelColor(j, strip2.Color(0, 255, 0));
            }
            strip2.show();
          }else if(code_2 == "WARNING"){
            for(int j = 0; j < 12; j++){
              strip2.setPixelColor(j, strip2.Color(255, 0, 0));
            }
            strip2.show();
          }
      }


      if(cameraId_3 == "3"){
          if(code_3 == "WARNING"){
            for(int j = 0; j < 12; j++){
              strip3.setPixelColor(j, strip3.Color(255, 0, 0));
            }
            strip3.show();
          }else if(code_3 == "NICE"){
            for(int j = 0; j < 12; j++){
              strip3.setPixelColor(j, strip3.Color(0, 255, 0));
            }
            strip3.show();
          }else if(code_3 == "NORMAL"){
            for(int j = 0; j < 12; j++){
              strip3.setPixelColor(j, strip3.Color(255, 255, 0));
            }
            strip3.show();
          }
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

  delay(10000);  //Send a request every 10 seconds
}
