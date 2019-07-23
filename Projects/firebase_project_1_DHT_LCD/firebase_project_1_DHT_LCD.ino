#include <ESP8266WiFi.h> 
#include <dht.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


const char *ssid =  "Fedora_2G";     // replace with your wifi ssid and wpa2 key
const char *password =  "Muhammed1984$";
 
dht DHT;

#define DHT11_PIN 2


 
void setup() {

  // initialize LCD
  lcd.begin(16,2);
  // turn on LCD backlight                      
  lcd.backlight();

  
  Serial.begin(115200);
 
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void loop(){

  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(  WiFi.localIP()   );
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Temp");
  lcd.println(DHT.temperature);
  lcd.print("Hum");
  lcd.println(DHT.humidity);
   
  delay(1000);
  lcd.clear(); 

 
             
}
