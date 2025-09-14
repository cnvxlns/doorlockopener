#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

void unlock(void);

const String PIN = "4821";
String str = "";
char buff;

const int btRXPin = 11;
const int btTXPin = 10;
const int servoPin = 9;
const int greenledPin = 3;
const int redledPin = 2;


Servo servo;
SoftwareSerial mySerial(btTXPin, btRXPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  servo.attach(servoPin);
  servo.write(0);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(redledPin, HIGH);
  digitalWrite(greenledPin, LOW);
  while(mySerial.available()){
    char buff = (char)mySerial.read();
    str += buff;
    delay(5);
  }
  if(str.equals(PIN) || str.equals("proper_fingerprint_")){
    unlock();  
  }else{
      lcd.print("**DOORLOCK**");
      lcd.setCursor(0, 1);
      lcd.print(str);
      delay(1000);
      lcd.clear();
  }
  str="";
  delay(100);
}

void unlock(){
    lcd.print("DOOR OPEN!");
    digitalWrite(greenledPin, HIGH);
    digitalWrite(redledPin, LOW);
    for(int i = 0; i <= 90; i++){
      servo.write(i);
      delay(10);
    }
    delay(3000);
    digitalWrite(redledPin, HIGH);
    digitalWrite(greenledPin, LOW);
    for(int i = 90; i >= 0; i--){
      servo.write(i);
      delay(10);
    }
    lcd.clear();
}
