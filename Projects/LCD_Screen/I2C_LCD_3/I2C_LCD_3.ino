#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
 
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
 // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Hello, NodeMcu!");
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Muhammed, Essa!");
  delay(1000);
  lcd.clear(); 
}
