#include <ESP8266HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>


const char* wifi = "bssm_free";
const char* password = "bssm_free";
const String url = "http://10.150.150.191:8080/density/now?camera=1";
WiFiClient wifiClient;



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
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(wifi, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
}

void loop(){
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.GET(); 
      //Send the actual POST request
    if (httpCode > 0) {
 
        // String vom Webseiteninhalt speichern
        String payload = http.getString();
        Serial.println(httpCode);
        // Hier kann mit dem Wert weitergearbeitet werden
         // ist aber nicht unbedingt notwendig
        Serial.println("불러온 JSON파일 값 : " + payload);
        Serial.print("테스트테스트");
        
        
      
  }else{
      // Falls HTTP-Error
      Serial.printf("HTTP-Error: ", http.errorToString(httpCode).c_str());
    }
 
    // Wenn alles abgeschlossen ist, wird die Verbindung wieder beendet
    http.end();
    
  }else {
    Serial.printf("HTTP-Verbindung konnte nicht hergestellt werden!");
  }
  
  delay(10000);  //Send a request every 10 seconds
  
}






