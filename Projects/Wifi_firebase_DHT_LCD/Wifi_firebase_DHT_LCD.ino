#include <ESP8266WiFi.h> 
#include <dht.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

#include <FirebaseArduino.h>


#define FIREBASE_HOST "nodemcu-3e3b1.firebaseio.com"
#define FIREBASE_AUTH "mDg44wI5qtoWBL2ghwafjOa9EXKwkfvQEDuRPm9g"


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


 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   
}

void loop(){
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
  lcd.clear(); 

    // set value
  Firebase.setFloat("Temperature", DHT.temperature);
  // handle error
  if (Firebase.failed()) {
  Serial.print("setting /number failed:");
  Serial.println(Firebase.error());  
  return;
  }

     // set value
  Firebase.setFloat("Humidity", DHT.humidity);
  // handle error
  if (Firebase.failed()) {
  Serial.print("setting /number failed:");
  Serial.println(Firebase.error());  
  return;
  }

    Firebase.setString("name", "Muhammed Essa");
// handle error
if (Firebase.failed()) {
Serial.print("setting /message failed:");
Serial.println(Firebase.error());  
return;
}

 
  Firebase.setString("ip", WiFi.localIP().toString() );
// handle error
if (Firebase.failed()) {
Serial.print("setting /message failed:");
Serial.println(Firebase.error());  
return;
}


// set bool value
Firebase.setBool("active", false);
// handle error
if (Firebase.failed()) {
Serial.print("setting /truth failed:");
Serial.println(Firebase.error());  
return;
}






  
            
}
