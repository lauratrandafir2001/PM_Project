#include <RFID.h>
#include "TMRpcm.h"
#include <SD.h> // Include the SD library
TMRpcm tmrpcm;

const int chipSelect = 4; // SD card chip select pin
RFID rfid(10, 9);
String rfidCard;

String rfidCard_left = String("160 8 103 133");
String rfidCard_right = String("184 183 210 51");

void setup() {
  Serial.begin(9600);
  tmrpcm.speakerPin = 6;
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
 if (!SD.begin(chipSelect)) {
  Serial.println("SD card initialization failed!");
}
  Serial.println("SD card initialized successfully!");
}
void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      
        rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
        
        tmrpcm.setVolume(4);
        if(rfidCard == rfidCard_left){
              tmrpcm.play("music1.WAV");
              Serial.println("This is music1 file");
      
        } if(rfidCard == rfidCard_right){
           
          tmrpcm.play("music2.WAV");
          
          Serial.println("This is music2 file");
        }
        delay(2000);
    }
    rfid.halt();
  }

  
}