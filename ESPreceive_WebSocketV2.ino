#include <Arduino.h>
 
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
 
WebSocketsClient webSocket;
 
const char *ssid     = "Galaxy A33 5G7E8F";
const char *password = "bunz4815";
 
unsigned long messageInterval = 5000;
bool connected = false;

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
String rcMSG = "";
 
#define Serial Serial
 
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("Server getrennt\n");
            connected = false;
            delay(2000);
            break;
        case WStype_CONNECTED: {
            Serial.printf("Mit Server verbunden\n");
            connected = true;
 
            // send message to server when Connected
            Serial.println("[WSc] SENT: Connected");
            //webSocket.sendTXT("Connected");
        }
            break;
        case WStype_TEXT:{
            String message = (char*)payload; // Payload in String umwandeln
          // Führende und nachfolgende Anführungszeichen entfernen (falls vorhanden)
          int start = message.indexOf('"');
          if (start >= 0) {
          int end = message.lastIndexOf('"');
          if (end > start) {
          message = message.substring(start + 1, end);
          }
          }
          Serial.println(message);
            break;
        }
        case WStype_BIN:
            Serial.printf("[WSc] get binary length: %u\n", length);
            hexdump(payload, length);
            break;
                case WStype_PING:
                        // pong will be send automatically
                        Serial.printf("[WSc] get ping\n");
                        break;
                case WStype_PONG:
                        // answer to a ping we send
                        Serial.printf("[WSc] get pong\n");
                        break;
    }
} 

 
void setup() {
    Serial.flush();
    Serial.begin(9600);
 
//  Serial.setDebugOutput(true);
 
    Serial.println();
    Serial.println();
    Serial.println();
 
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
 
    WiFi.begin(ssid, password);
 
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }
    Serial.print("Local IP: "); Serial.println(WiFi.localIP());
    // server address, port and URL
    webSocket.begin("ws://amp.kongcrew.de", 7778, "/", "ws");
 
    // event handler
    webSocket.onEvent(webSocketEvent);
}
 
unsigned long lastUpdate = millis();
 
 
void loop() {
    webSocket.loop();
    if (connected){
        if (stringComplete) {
        stringComplete=false;
        String cmd = parseInput();

        if (cmd.equals("Add")) {
          String msg = "{\"type\":\"Add\",\"Filament\":\"";
          msg+=inputString;
          msg+="\"}";
          webSocket.sendTXT(msg);
          Serial.println(inputString); 
        }
        else if(cmd.equals("Del")){
          String msg = "{\"type\":\"Del\",\"Filament\":\"";
          msg+=inputString;
          msg+="\"}";
          webSocket.sendTXT(msg);
          Serial.println(inputString); 
        }
      inputString = "";
      }
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
    else{
      inputString += inChar;
    }
  }
}

String parseInput(){
  String tmp = inputString.substring(0,inputString.indexOf(":"));
  inputString = inputString.substring(inputString.indexOf(": ")+2);

  int i=0;
  while (i >= 0){
    i = inputString.indexOf(" ");
    inputString.remove(i,1);
  }

  /*
  for(int i = 0; i<inputString.length();i++){
    if(inputString.charAt(i) == ('-')){
      
    }
  }
  /**/
  return tmp;
}