#include <ParallaxSerialLCD.h>
#include <SoftwareSerial.h>

#define LCD_PIN 2

ParallaxSerialLCD lcd(LCD_PIN);

void setup()
{
	lcd.begin(16,2);
	lcd.print("Hello World");
}

void loop(){

}
