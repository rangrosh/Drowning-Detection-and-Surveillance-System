  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <ESP8266WiFiMulti.h>
  #include <ESP8266HTTPClient.h>
  #define USE_SERIAL Serial
  ESP8266WiFiMulti WiFiMulti;
  String result="";
  const int buzzer = 2;
  void setup() {
     USE_SERIAL.begin(9600);
    // USE_SERIAL.setDebugOutput(true);
     USE_SERIAL.println();
     USE_SERIAL.println();
     USE_SERIAL.println();
     pinMode(buzzer , OUTPUT); 
     for(uint8_t t = 4; t > 0; t--) {
       //  USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
         USE_SERIAL.flush();
         delay(1000);
     }
     WiFi.mode(WIFI_STA);
     // provide our SSID and Password for WIFI network connection
     WiFiMulti.addAP("Redmi", "nibbason");
  }
  void loop() {
     result="CHILL";
     // wait for WiFi connection
     if((WiFiMulti.run() == WL_CONNECTED)) {
         HTTPClient http;
         USE_SERIAL.println("Sending Get Request to Server.......");
         http.begin("http://192.168.43.168"); //HTTP URL for hosted server(local server)
         //192.168.43.161 - HOST     PORT: 3000 and /api is the target api we need to hit to get response
         int httpCode = http.GET();
        // USE_SERIAL.println("After GET Request");
         // httpCode will be negative on error
         if(httpCode > 0) {
             if(httpCode == HTTP_CODE_OK) {
               //HTTP_CODE_OK means code == 200
                 String payload = http.getString();// gives us the message received by the GET Request
                 for(int i=0;i<=1000;i++){
                  if(payload[i]=='D'){
                    if(payload[i+1]=='r' && payload[i+2]=='o' && payload[i+3]=='w' ){
                      result = "DROWNING!!!!";
                      digitalWrite(buzzer, HIGH);
                      delay(100);
                      digitalWrite(buzzer, LOW);
                      delay(100);
                      digitalWrite(buzzer, HIGH);
                      delay(100);
                      digitalWrite(buzzer, LOW);
                      delay(100);
                      digitalWrite(buzzer, HIGH);
                      delay(100);
                      digitalWrite(buzzer, LOW);
                      delay(100);
                      digitalWrite(buzzer, HIGH);
                      delay(100);
                      digitalWrite(buzzer, LOW);
                    }
                  }
                  
                 }
                 USE_SERIAL.println(result);// Displays the message onto the Serial Monitor
             }
         } else {
             USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
         }
         http.end();
     }
     delay(3000);// repeat the cycle every 5 seconds.
  }
