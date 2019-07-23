#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

void setup()
{
  // initialize LCD
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Omer Ahmed");
  lcd.setCursor(0,1);
  lcd.print("Hussain Ali");
  delay(1000);
  lcd.setBacklight(LOW);
  delay(1000);
}
