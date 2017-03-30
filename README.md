# Huzzah-Telegram-Lightswitch-Bot
A bot for the Adafruit Feather Huzzah that communicates with the Telegram API to switch a light with a relay.

Requires a library and a board mananger be downloaded:

  1. https://github.com/Gianbacchio/ESP8266-TelegramBot - Install through zip
  
  2. http://arduino.esp8266.com/stable/package_esp8266com_index.json - Include through File->Preferences->Additional board manager URLS, then go to the board manager and install the latest version. Also includes espWiFi8266 library.
  
Connect the switch of your relay to pin 14.
Be sure to update your WiFi SSID and password variables, as well as your BOT API key.
