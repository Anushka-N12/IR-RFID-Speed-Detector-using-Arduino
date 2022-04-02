/*
   --------------------------------------------------------------------------------------------------------------------
   This program first reads data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID Reader on the Arduino SPI interface.
   Typical pin layout used:
   ---------------------------------------
               MFRC522      Arduino
               Reader/PCD   Uno/101
   Signal      Pin          Pin
   ---------------------------------------
   RST/Reset   RST          9
   SPI SS      SDA(SS)      10
   SPI MOSI    MOSI         11 / ICSP-4
   SPI MISO    MISO         12 / ICSP-1
   SPI SCK     SCK          13 / ICSP-3

   When a card/tag is sensed, '1' is printed onto the serial monitor.
   Then, the IR sensors measure the car's speed using time stamps and prints it onto the serial monitor.
   If this speed is within a safe range, the green LED lights up for 3 seconds to indicate so.
   If not, the red one lights up instead.

   A yellow LED lights up for 15s in between to ensure all data is accepted by Thingspeak.
   --------------------------------------------------------------------------------------------------------------------
*/

#include <deprecated.h>        // Includes neccessary libraries
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>
#include <speed_ir.h>   //including custom library for calculating speed

#define RST_PIN         9           // According to connections
#define SS_PIN          10
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Creates MFRC522 instance

int x; //Variable introduced to get desired output

void setup() {  //executes once
  Serial.begin(9600);     // Initiates a serial communication
  SPI.begin();           // Initiates  SPI bus
  mfrc522.PCD_Init();   // Initiates MFRC522
  pinMode(A0, INPUT);   //These pins are connected to the 2 IR sensors
  pinMode(A1, INPUT);
  pinMode(2, OUTPUT);//initializes green LED
  pinMode(3, OUTPUT);//initializes red LED
  pinMode(4, OUTPUT);  //This yellow LED will indicate when car can pass in a way Thingspeak will recieve all values
}

void loop() {  //loops until switched off
  if ( ! mfrc522.PICC_IsNewCardPresent() && x == 0) {  //checks for new card
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {           // Tries to read card
    x = 0;
    return;
  }
  Serial.println(1);   //when card is sensed
  digitalWrite(4, HIGH); // for yellow LED, tells new cars to wait
  x = 1;
  int timer1; //declaring variables for below function
  int timer2;
  float distance = 5.0;
  float speed = ir_speed(timer1, timer2, distance);  //function to get speed using IR sensors
  delay(10000);
  delay(5000);
  Serial.println(speed);
  digitalWrite(4, LOW);
  if (speed < 20 || speed > 120)  {  //if speed in out of safe range
    digitalWrite(3, HIGH);  //red LED lights up for 3 seconds
    delay(3000);
    digitalWrite(3, LOW);
  }
  else  {  //when car is moving in safe speed
    digitalWrite(2, HIGH);  //green LED lights up for 3 seconds
    delay(3000);
    digitalWrite(2, LOW);
  }
}
