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
 //Write your code
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("Muhammed Essa"); //You can write 16 Characters per line .
delay(1000);//Delay used to give a dynamic effect
lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
lcd.print("NodeMcu");
delay(8000); 

lcd.clear();//Clean the screen
lcd.setCursor(0,0); 
lcd.print(" Welcome ");
lcd.setCursor(0,1);
lcd.print("LIKE | SHARE");
delay(8000); 
}
