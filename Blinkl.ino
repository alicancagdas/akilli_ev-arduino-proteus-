#include "LiquidCrystal.h"
#include <Keypad.h>


#define F_Pin A0
#define T_pin A15
#define P_Pin A2

#define buzzer 18
#define redled 19
#define greenled 20
#define lamp 21

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sayac = 0;

const byte satir = 4;
const byte sutun = 3;

String sifre = "1903";
String sifreinput = "";


char tustakimi[satir][sutun] = {
  {'3', '2', '1'},
  {'6', '5', '4'},
  {'9', '8', '7'},
  {'#', '0', '*'}
};

byte satirPin[satir] = { 10, 9, 8, 7 };
byte sutunPin[sutun] = { 13, 12, 11 };

Keypad keypadim = Keypad( makeKeymap(tustakimi), satirPin, sutunPin, satir, sutun);


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);


  analogReference(INTERNAL1V1);
  
  pinMode(F_Pin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(P_Pin, INPUT);
    pinMode(lamp, OUTPUT);

  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);

}

void loop() {
sifrekontrolcu();
  flamesensor();
  pirsensor();
  termometre();

}

void termometre() {
  float sicaklik = analogRead(T_pin);
  sicaklik = sicaklik * 1100 / (1024 * 10);
  lcd.setCursor(0, 0);
  lcd.print( "SICAKLIK: ");
  lcd.print(sicaklik);
  lcd.println("C");

  if (sicaklik >= 30) {
 
   
   lcd.setCursor(0, 1);
    
      lcd.println("SICAKLIKYUKSELDI! ");
    delay(20);
    lcd.clear();

  }
  if (sicaklik <= 20) {

   
    lcd.setCursor(0, 1);
    lcd.println("SICAKLIKDUSTU!");
    ;
    delay(20);
    lcd.clear();
  
  }
}

void pirsensor() {
  int Hareket = digitalRead(P_Pin);
  if (Hareket == HIGH)
  {
    digitalWrite(lamp, HIGH);



  }
  else
  {
    digitalWrite(lamp, LOW);
  }
}

void flamesensor() {
  int Yangin = digitalRead(F_Pin);
  if (Yangin == HIGH)
  {
    digitalWrite(buzzer, HIGH);

  }
  else
  {
    digitalWrite(buzzer, LOW);
  }
}



void sifrekontrolcu() {


  char girdi = keypadim.getKey();
  
  if (girdi != NO_KEY) {

    sifreinput = sifreinput + girdi;
    sayac++;
  }


  if (girdi == '#') {
    
    if (sifreinput.substring(0, sayac - 1) == sifre) {

      digitalWrite(20, HIGH);
       delay(300);
              digitalWrite(20, LOW);
      
sifreinput="";
    sayac=0;
    }
    
    else if (sifreinput.substring(0, sayac - 1) != sifre) {
       digitalWrite(19, HIGH);
       delay(300);
              digitalWrite(19, LOW);

    sayac=0;
  sifreinput="";
  }

}}
