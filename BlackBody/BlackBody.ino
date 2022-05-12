#include <LiquidCrystal.h>

float temp,oldtemp,newtemp;
float red,green,blue;

LiquidCrystal lcd(2,4,7,8,10,11);

void setup() {
    oldtemp = temp = 0;
    newtemp = 600;
    lcd.begin(16, 2);
    analogWrite(5,105);
}

void loop() {
    int um,dois;
    um = digitalRead(A0);
    dois = digitalRead(13);
    delay(150);
      
    if(um)
        newtemp += 100; 
    if(dois)
        newtemp -= 100;
      
    if(newtemp >= 12100) newtemp = 12100;
    if(newtemp <= 400) newtemp = 400;    
    
    if(newtemp != oldtemp){
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Temperature");
        lcd.setCursor(5, 1);
        int temperature = oldtemp;
        lcd.print(temperature);
        lcd.setCursor(10, 1);
        lcd.print("K");
        oldtemp = newtemp;
        temp = oldtemp/100.0;

      if(temp<=66){
        red = 255;
      }else{
        red = temp - 60;
        red = 329.698727446*(pow(red,(-0.1332047592)));
        if(red < 0){
          red = 0;
        }
        if(red > 255){
          red = 255;
        }
      }

      if(temp <=66){
        green = temp;
        green = 99.4708025861*(log(green)) - 161.1195681661;
        green = map(green,0,255,0,199);
        if(green<0){
          green = 0;
        }
        if(green>255){
          green = 255;
        }
      }else{
        green = temp - 60;
        green = 288.1221695283*(pow(green,(-0.0755148492)));
        if(green<0){
          green = 0;
        }
        if(green>255){
          green = 255;
        }
      }

      if(temp>=66){
        blue = 255;
      }else{
         if(temp <=19){
          blue = 0;
         }else{
          blue = temp - 10;
          blue = 138.5177312231*(log(blue)) - 305.0447927307;
          blue = map(blue,0,255,0,199);
          if(blue<0){
            blue = 0;
          }
          if(green>255){
            blue = 255;
          }
         }
      }

      red = red/2.9090;      // Normalizacao de valores
      green = green/3.7272;  //
      
      analogWrite(3,red);
      analogWrite(6,green);
      analogWrite(9,blue);
      delay(5);
    }
}
