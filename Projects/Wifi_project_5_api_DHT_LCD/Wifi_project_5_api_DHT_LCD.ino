#include <ESP8266WiFi.h> 
#include <dht.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

  
dht DHT;
#define DHT11_PIN 2

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 


const char *ssid =  "Fedora_2G";     // replace with your wifi ssid and wpa2 key
const char *password =  "Muhammed1984$";

const char* serverName = "http://nodemcu.codeforiraq.org/insert.php";
//String apiKey = "MuhammedEssa"; 
String sensorName = "Muhammed Essa";


 
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
  




void loop() {



  int chk = DHT.read11(DHT11_PIN);
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print(  WiFi.localIP()   );
  delay(1000);
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.println(DHT.temperature);
  lcd.print("H:");
  lcd.println(DHT.humidity); 
  delay(1000);
   
    
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
  
  
  http.begin(serverName);     //Specify request destination
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST("{\"name\":\""+sensorName
                           +"\",\"ip_address\":\""+WiFi.localIP().toString()
                           +"\",\"temperature\":\""+String(DHT.temperature)
                           +"\",\"humidity\":\""+String(DHT.humidity)
                           +"\",\"active\":\"Ture\"}");
  String payload = http.getString();    //Get the response payload

 Serial.println(serverName);   
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
  
  delay(5000);  //GET Data at every 5 seconds


  }
}



   
