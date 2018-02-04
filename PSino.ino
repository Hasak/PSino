#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte up[] = {
  B00100,
  B01110,
  B11111,
  B01110,
  B01110,
  B01110,
  B01110,
  B00000
};

byte down[] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B11111,
  B01110,
  B00100
};

byte flash[] = {
  B00111,
  B01110,
  B11100,
  B11111,
  B00111,
  B00110,
  B01100,
  B10000
};

void setup() {
  lcd.createChar(1, up);
  lcd.createChar(2, down);
  lcd.createChar(3, flash);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
  lcd.begin(16, 2);
  lcd.print("  POWER SUPPLY");
  lcd.setCursor(0,1);
  lcd.write(3);lcd.print(" HASAK  2018 ");lcd.write(3);
  for(int i=0;i<255;i++){
    analogWrite(9,i);
    analogWrite(10,i);
    delay(5);
  }for(int i=255;i>=0;i--){
    analogWrite(9,i);
    analogWrite(10,i);
    delay(5);
  }
  
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(2000);
  lcd.clear();
  lcd.print(" ");lcd.write(1);lcd.print("  CONNECT  ");lcd.write(1);lcd.setCursor(0,1);
  lcd.print("GND         V+");
  delay(3000);
  lcd.clear();
  //Serial.begin(9600);
}

int nodig(int n){
  int c=0;
  while(n!=0){
    n/=10;
    c++;
  }
  return c;
}

int kol(int x){
  int a=3-nodig(x);
  if(a<0)
  return 0;
  else if(!x) return a-1;
  else return a;
}
double E=0,I,V,P2,t=10,t1=-1000,t2,mmm=0,nnn=0,n=0;
void loop(){
  mmm+=analogRead(A0);
  n++;
  nnn+=analogRead(A1);
  t2=millis();
  if(t2-t1>=1000){
    mmm/=n;
    nnn/=n;
    //I=(5000.0*mmm/1024-2500)/66;
    Serial.println(mmm);
    I=-0.036711*mmm+3.7563;
    I=abs(I);
    V=15.0*nnn/1024;
    P2=V*I;
    E+=1.0*P2*t/1000/3600;
    mmm=0;
    nnn=0;
    n=0;
    t1=t2;
    if(V>14.1){
      lcd.setCursor(0,0);
      digitalWrite(9,0);
      digitalWrite(10,1);
      lcd.print("  ");lcd.write(3);lcd.print("  ERROR  ");lcd.write(3);lcd.print("   ");lcd.setCursor(0,1);
      lcd.print("  HIGH VOLTAGE  ");
    }
    else if(I>21.1){
      lcd.setCursor(0,0);
      digitalWrite(9,0);
      digitalWrite(10,1);
      lcd.print("  ");lcd.write(3);lcd.print("  ERROR  ");lcd.write(3);lcd.print("   ");lcd.setCursor(0,1);
      lcd.print("  HIGH CURRENT  ");
    }
    else if(V<0.1){
      lcd.setCursor(0,0);
      digitalWrite(9,0);
      digitalWrite(10,1);
      lcd.print("  ");lcd.write(3);lcd.print("  ERROR  ");lcd.write(3);lcd.print("   ");lcd.setCursor(0,1);
      lcd.print(" CHECK SELECTOR ");
    }
    else{
      digitalWrite(9,1);
      digitalWrite(10,0);
      lcd.setCursor(0,0);
      lcd.print("V=");lcd.print(V,kol(V));lcd.print("V I=");lcd.print(I,kol(I));lcd.print("A ");lcd.setCursor(0,1);
      lcd.print("P=");lcd.print(P2,kol(P2));lcd.print("W ");if(nodig(P2)==3)lcd.print(" ");lcd.print("E=");lcd.print(E,kol(E));lcd.print("Wh");
    }
  }
  delay(t);
}
