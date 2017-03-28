#include <ESP8266WiFi.h> //Used for WiFi chip
#include <WiFiClientSecure.h> //Used for SSL Connection
#include <ESP8266TelegramBOT.h> //Simplifies communication with Telegram Bot API

int relayPin = 14; //Pinout connected to relay switch

const char ssid[] = "FNSBSD-BYOD"; //SSID of network to connect to
const char pass[] = "PersonalDevice"; //password of network to connect to

const char* BotToken = "347260846:AAGp8JUdAVSD-o6XoE4fw2uXBeAk9XNtXVY"; //From Telegram BotFather, used for authentication
const char* BotName = "SwitchBot"; //Established through BotFather
const char* BotUsername = "LightSwitchBot"; //Established through BotFather

TelegramBOT lightBot(BotToken, BotName, BotUsername); //creates object lightBot from included class TelegramBot

int scanTime = 5000; //time between scans for messages
unsigned long lastScan; //time value of last message scan

void setup() {
  Serial.begin(115200); //Feather Huzzah uses faster-than-usual serial speed
  pinMode(relayPin, OUTPUT); //Relay switch will be written to
  delay(3000); //Give Serial time to connect

  WiFi.begin(ssid, pass); //Connect to specified WiFi network
  delay(5000); //Give WiFi time to connect
  Serial.println("wifi status:" + WiFi.status()); //Ensure WiFi is connected
  
  lightBot.begin(); //calls upon begin functionality of object lightBot, starting communication with Telegram
}

void loop() {
  if (millis() > lastScan + scanTime) { //Runs if uptime is more than five seconds greater than the last time the code was run
    lightBot.getUpdates(lightBot.message[0][1]); //connects to Telegram API to get messages
    for (int i = 1; i < lightBot.message[0][0].toInt() + 1; i++) { //Runs for each message received
      if (lightBot.message[i][5] == "/SwitchOn") { //Runs if plaintext of received message is "/SwitchOn" (6th element in array is plaintext message)
        switchOn(); //See declared function
      }
      if (lightBot.message[i][5] == "/SwitchOff") { //Runs if plaintext of received message is "/SwitchOn"
        switchOff(); //See declared function
      }
    }
    lastScan = millis(); //Write Huzzah uptime to lastScan, used in condition of if statement
  }
}

void switchOn() {
  digitalWrite(relayPin, HIGH); //Write relay swtich to high; Normally Open is now closed, Normally Closed now open
  for (int i = 1; i < lightBot.message[0][0].toInt() + 1; i++) { //for each message received, run code
    lightBot.sendMessage(lightBot.message[i][4], "Lights turned on", ""); //Send message back to user that lights are on
    delay(100); //Gives message time to send
  }
}

void switchOff() {
  digitalWrite(relayPin, LOW); //Write relay swtich to low; Normally Open is now open, Normally Closed now closed
  for (int i = 1; i < lightBot.message[0][0].toInt() + 1; i++) { //for each message received, run code
    lightBot.sendMessage(lightBot.message[i][4], "Lights turned off", ""); //Send message back to user that lights are off
    delay(100); //Gives message time to send
  }
}
