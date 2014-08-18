#include <FileIO.h>
#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>
#include <LiquidCrystal.h>
#include <Bridge.h>

String msg1 = "SydPHP Meetup Group";
String msg2 = "";
String msg3 = "";
String msg4 = "Follow us @PayPalDev";

int printer_RX_Pin = 5;
int printer_TX_Pin = 6;

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  Bridge.begin();
  printer.begin(); 
  FileSystem.begin();
  lcd.begin(20, 4);
}

char path[ ] = "/www/cache/temp";

void loop() {
  
  startmsg();
  
  if(FileSystem.exists(path)){
    String text;
    File file = FileSystem.open(path, FILE_READ);
    while (file.available() > 0){
      char c = file.read();
      text += c;
    }
    file.close();
    FileSystem.remove(path);      
      
    int textLen = text.length();    
    
    if(textLen>0)
    {
      printing(text);
      text = "";
    }    
    
  }
  
  delay(5000);
  
}

void startmsg()
{
  lcd.setCursor(0, 0);
  lcd.print(msg1);  
  lcd.setCursor(0, 1);
  lcd.print(msg2);  
  lcd.setCursor(0, 2);
  lcd.print(msg3);  
  lcd.setCursor(0, 3);
  lcd.print(msg4);  
}

void blinker(int blinkloop)
{ 
  while(blinkloop>0)
  {
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
    blinkloop--;
  }
}

void printing(String text){
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("********************");  
  lcd.setCursor(0, 1);
  lcd.print("      INCOMING      ");  
  lcd.setCursor(0, 2);
  lcd.print("      PRINTING      ");  
  lcd.setCursor(0, 3);
  lcd.print("********************");  
  blinker(3);

  printer.justify('C');
  printer.println(msg1);
  printer.feed(2);
  printer.justify('L');
  printer.println(text);
  printer.feed(1);
  
  delay(1000);
  
  lcd.clear();
  startmsg();

}

