#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN 2
 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

void setup()
{
  // initialize LCD
  lcd.begin(16,2);
  // turn on LCD backlight                      
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{


  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
   



  
 // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Temp: ");
  lcd.print(DHT.temperature );
  delay(1000);
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(DHT.humidity );
  delay(2000);
  lcd.clear(); 
}
