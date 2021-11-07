
#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>


// Declare wifi name and password
#define SSID        "WIFI NAME"
#define PASSWORD    "PASSWORD"
#define LINE_TOKEN  "LINE TOKEN"

//Declare pin
int motion = D7;
int light = D4;
int buzz = D3;
int led = D8;

// Void setup
void setup() {
  pinMode(motion, INPUT);
  pinMode (light, INPUT);
  pinMode (buzz, OUTPUT);
  pinMode (led, OUTPUT);

  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  digitalWrite(led, HIGH);
  LINE.setToken(LINE_TOKEN);
  LINE.notify("Wifi is ready");

}

void loop() {


light = analogRead(A0);
motion = digitalRead(D7);

// If Light come and motion detected
if(light <= 750 && motion == 1){
  Serial.println("Motion Detected (Day)");
  digitalWrite(buzz , LOW);
  LINE.notify("Motion detected! (DAY)");
  delay(5);
  }

// If Light come out and motion detected
if(light >= 900 && motion == 1){
  Serial.println("Motion Detected (Night)");
  digitalWrite(buzz , HIGH);
  LINE.notify("Motion detected! (NIGHT)");
  delay(5);
  }
  else{
    digitalWrite(buzz , LOW);
    }
  }
