#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>

#define ena 5
#define in1 6
#define in2 7
#define in3 8
#define in4 9
#define enb 10

PS2X ps2x; // create PS2 Controller Class
Servo myservo;
Servo myservo2;

int LM = 0;
int HM = 100;

void setup() {
  Serial.begin(57600);

  myservo.attach(37);
  myservo2.attach(36);

  ps2x.config_gamepad(52, 51, 53, 50, true, true); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void maju(int pwm) {
  analogWrite(ena, pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, pwm);
}

void kiri(int pwm) {
  analogWrite(ena, 20);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, pwm);
}

void kanan(int pwm) {
  analogWrite(ena, pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 20);
}

void mundur(int pwm) {
  analogWrite(ena, pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, pwm);
}

void capit() {
  //myservo.write(180);
  // set servo to mid-point
  myservo2.write(0);
  delay(100);
  myservo.write(100);
  delay(100);
  myservo2.write(100);
  delay(100);
  myservo.write(180);
  delay(100);
}

void bukaCapit() {
  myservo.write(100);
  delay(100);
  myservo2.write(20);
  delay(100);
}


void loop() {


  ps2x.read_gamepad();          //read controller and set large motor to spin at 'vibrate' speed

  int LY = ps2x.Analog(PSS_LY);
  int LX = ps2x.Analog(PSS_LX);

  if (LY < 127) {

    LY = map(LY, 127, 0, LM, HM);
    maju(LY);

  } else if (LY > 129) {

    LY = map(LY, 129, 255, LM, HM);
    mundur(LY);

  } else if (LX < 127) {

    LX = map(LX, 127, 0, LM, HM);
    kiri(LX);

  } else if (LX > 129) {

    LX = map(LX, 129, 255, LM, HM);
    kanan(LX);

  } else {

    maju(0);
    mundur(0);

  }
  if (ps2x.ButtonPressed(PSB_L1)) {
    Serial.println("ijo");
    capit();

  } else if (ps2x.ButtonPressed(PSB_R1)) {

    bukaCapit();

  }

  delay(50);
}
