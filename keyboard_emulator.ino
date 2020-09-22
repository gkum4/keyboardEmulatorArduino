/***
  Teste de Websockets com ESP8266 - Servidor
  José Cintra em Outubro de 2019 - www.josecintra.com/blog/comunicacao-websockets-nodemcu-esp8266">
***/

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <FirebaseArduino.h>

#define btn1 5
#define btn2 4
#define btn3 0
#define btn4 2
#define btn5 14
#define btn6 12
#define FIREBASE_HOST "handy-cell-242812.firebaseio.com"
#define FIREBASE_AUTH "Mo3mCj2YlOOdCAmFuvfj7XF9FUUNo1na8aChWG9s"

     //sensor value, I'm usingg 0/1 button state
int sensorValue1 = 0;        
int sensorValue2 = 0;        
int sensorValue3 = 0; 
int sensorValue4 = 0; 
int sensorValue5 = 0; 
int sensorValue6 = 0; 

WebSocketsClient webSocket; // Recebe dados do cliente

// Autenticação wi-fi - Coloque aqui a sua configuração
const char* ssid     = "langus";
const char* password = "langustin10";

void setup() {

  // Inicialização do LED
  Serial.begin(9600);
  
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);
  pinMode(btn6, INPUT);
  
  // Conexões wi-fi e websocket
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(". ");
    delay(100);
  }
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  String computerIp = Firebase.getString("computerIp");
  
  Serial.println(computerIp);
  
  webSocket.begin(computerIp, 8888, "/");
  
  webSocket.setReconnectInterval(5000);

}

void loop() {
  webSocket.loop();

  if(digitalRead(btn1) == LOW) sensorValue1 = 1;
  if(digitalRead(btn2) == LOW) sensorValue2 = 1;
  if(digitalRead(btn3) == LOW) sensorValue3 = 1;
  if(digitalRead(btn4) == LOW) sensorValue4 = 1;
  if(digitalRead(btn5) == LOW) sensorValue5 = 1;
  if(digitalRead(btn6) == LOW) sensorValue6 = 1;
  
  if(digitalRead(btn1) == HIGH) sensorValue1 = 0;
  if(digitalRead(btn2) == HIGH) sensorValue2 = 0;
  if(digitalRead(btn3) == HIGH) sensorValue3 = 0;
  if(digitalRead(btn4) == HIGH) sensorValue4 = 0;
  if(digitalRead(btn5) == HIGH) sensorValue5 = 0;
  if(digitalRead(btn6) == HIGH) sensorValue6 = 0;

  if ( sensorValue2 == 1 && sensorValue5 == 1) {
    setup();
    delay(1000);
  }

  if ( sensorValue1 == 1) {
    Serial.println("message sent");
    webSocket.sendTXT("1");
    delay(110);
  }
  if ( sensorValue2 == 1) {
    Serial.println("message sent");
    webSocket.sendTXT("2");
    delay(110);
  }
  if ( sensorValue3 == 1) {
    Serial.println("message sent");
    webSocket.sendTXT("3");
    delay(110);
  }
  if ( sensorValue4 == 1) {
    Serial.println("message sent");
    webSocket.sendTXT("4");
    delay(110);
  }
  if ( sensorValue5 == 1) {
    Serial.println("message sent");
    webSocket.sendTXT("5");
    delay(110);
  }
  if ( sensorValue6 == 1) {
    Serial.println("message sent");
    webSocket.sendTXT("6");
    delay(110);
  }
}
