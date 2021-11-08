
#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1  # if oled doesn't has rst pin else change to 4
#define SCREEN_ADDRESS 0x3C  # OLED adress 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SSID        "WIFI_NAME"
#define PASSWORD    "PASSWORD"
#define LINE_TOKEN  "LINE_TOKEN"

int motion = D7;
int light = D4;
int buzz = D3;
int led = D8;
int motion_value = 0;

void setup() {
  pinMode(motion, INPUT);
  pinMode (light, INPUT);
  pinMode (buzz, OUTPUT);
  pinMode (led, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display(); delay(2000);
  display.clearDisplay();  
  
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);


  while(WiFi.status() != WL_CONNECTED) {
      digitalWrite(led, LOW); 
      Serial.print("."); 
      delay(10); 
      }
    
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Connected to");
  display.println(WiFi.localIP());
  display.display();
  
  digitalWrite(led, HIGH);
  
  display.clearDisplay();

  LINE.setToken(LINE_TOKEN);
  LINE.notify("Wifi is ready");

}

String found(){

    display.clearDisplay();
    display.setTextColor(WHITE); // 'inverted' text
    display.setTextSize(2);
    display.setCursor(0,28);
    display.println("Found People");
    display.display();
    delay(10);
    display.clearDisplay();
  }

 String not_found(){
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.setTextSize(2);
    display.println("Not Found People");
    display.display();
    display.clearDisplay();
  }

 String disconnected(){

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0,28);
    display.setTextSize(2);
    display.println("WIFI DISCONNECTED");
    display.display();
    delay(10);
    display.clearDisplay();
  }

void loop() {

light = analogRead(A0);


while(WiFi.status() == WL_CONNECTED){
  motion_value = digitalRead(motion);
  if(motion_value == 1){
      found();
      digitalWrite(buzz , HIGH);
      delay(20);
      Serial.println("Motion Detected");
      LINE.notify("Motion detected!");
      
    }
   if(motion_value != 1){
    Serial.println("-");
    digitalWrite(buzz , LOW);
      not_found();
    }
  //LINE.notify(motion_value);
  }

  disconnected();

  }
