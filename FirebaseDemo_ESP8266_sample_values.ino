//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "iot-app-124fc.firebaseio.com"
#define FIREBASE_AUTH "GNdXmcSHNjm25qlpOjUuBxqhyrbnzSBbWSWiTkVD"
#define WIFI_SSID "Batman"
#define WIFI_PASSWORD "batman.12345"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);
}


int n = 0;
float x;

void loop() {

  if(Serial.available()) {
      x = Serial.parseInt();
      Serial.println(x);
    
  // set value
  Firebase.setFloat("Distance ", x);}
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number1 failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  Serial.print("pushed: /logs/");
  delay(1000);
}
