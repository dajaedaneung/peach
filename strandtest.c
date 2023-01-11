#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* wifi = "bssm_free";
const char* password = "bssm_free";



//고정적으로 사용할 내용을 미리 선언
#define LED_PIN1 D5     //네오픽셀에 신호를 줄 핀번호
#define LED_PIN2 D6     //네오픽셀에 신호를 줄 핀번호
#define LED_PIN3 D7     //네오픽셀에 신호를 줄 핀번호
// #define LED_PIN4 D8
   //아두이노에 연결된 네오픽셀의 개수
   //red : 3
   //yellow : 2
   //blue : 1
int a = 3;
int b = 1;
int c = 2; // or 2 or 3
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
  Serial.begin(9600);
   
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
  if(code == "NICE"){
    for(int j = 0; j < 12; j++){
        strip1.setPixelColor(j, strip1.Color(0, 255, 0));
    }
    strip1.show();
  }
  else if(code == "NORMAL"){
    for(int j = 0; j < 12; j++){
        strip1.setPixelColor(j, strip1.Color(255, 255, 0));
    }
    strip1.show();
  }
  else if(code == "WARNING"){
    for(int j = 0; j < 12; j++){
        strip1.setPixelColor(j, strip1.Color(255, 0, 0));
    }
    strip1.show();
  }


  if(code == "NORMAL"){
    for(int j = 0; j < 12; j++){
        strip2.setPixelColor(j, strip2.Color(255, 255, 0));
    }
    strip2.show();
  }else if(code == "NICE"){
    for(int j = 0; j < 12; j++){
        strip2.setPixelColor(j, strip2.Color(0, 255, 0));
    }
    strip2.show();
  }else if(code == "WARNING"){
    for(int j = 0; j < 12; j++){
        strip2.setPixelColor(j, strip2.Color(255, 0, 0));
    }
    strip2.show();
  }



  if(code == "WARNING"){
    for(int j = 0; j < 12; j++){
        strip3.setPixelColor(j, strip3.Color(255, 0, 0));
    }
    strip3.show();
  }else if(code == "NICE"){
    for(int j = 0; j < 12; j++){
        strip3.setPixelColor(j, strip3.Color(0, 255, 0));
    }
    strip3.show();
  }else if(code == "NORMAL"){
    for(int j = 0; j < 12; j++){
        strip3.setPixelColor(j, strip3.Color(255, 255, 0));
    }
    strip3.show();
  }
  
  // 스트립 길이를 따라서 설정된 색으로 채운다.
  // strip.Color(Red,   Green,   Blue) 스트립의 색상을 RGB순서대로 세팅해준다.각RGB마다 0~255까지 설정가능
  // colorWipe(스트립 색상, 딜레이 시간)
  
  // colorWipe(strip.Color(  80,   188, 223), 0); // Blue
  
  // colorWipe(strip.Color(  0,   0, 255), 60);

  // colorWipe(strip.Color(  0,   0, 0), 0);
  
  // colorWipe(strip.Color(  0,   0, 0), 80); // Blue

  // 극장간판에 달린 전구가 빛나는것과 유사한 효과
  // theaterChase(스트립 색상, 딜레이 시간)
  
  
  //해당 함수들은 밑에 구현되어있다.
}s
// void colorWipe(uint32_t color, int wait) {
  
//   for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
//     strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
//     strip.show();                          //  Update strip to match
//     delay(wait);  
//              //  Pause for a moment
//   }

// }



