#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>

// 电机引脚
#define in1 32   // 左轮前进
#define in2 33   // 左轮后退
#define in3 25   // 右轮前进
#define in4 26   // 右轮后退

// 固定速度
int leftSpeed = 255;   // 左轮固定最大
int rightSpeed = 180;  // 右轮速度

// ================= 电机函数 =================
void motorForward() {
  analogWrite(in1, leftSpeed);
  digitalWrite(in2, LOW);
  analogWrite(in3, rightSpeed);
  digitalWrite(in4, LOW);
}

void motorBackward() {
  analogWrite(in2, leftSpeed);
  digitalWrite(in1, LOW);
  analogWrite(in4, rightSpeed);
  digitalWrite(in3, LOW);
}

void motorLeft() {
  analogWrite(in1, 0);       // 左轮慢
  digitalWrite(in2, LOW);
  analogWrite(in3, rightSpeed);// 右轮快
  digitalWrite(in4, LOW);
}

void motorRight() {
  analogWrite(in1, leftSpeed); // 左轮快
  digitalWrite(in2, LOW);
  analogWrite(in3, 0);       // 右轮慢
  digitalWrite(in4, LOW);
}

void motorStop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

// ================= 初始化 =================
void setup() {
  Serial.begin(115200);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Dabble.begin("Pai_Car");   // 蓝牙名字
}

// ================= 主循环 =================
void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    motorForward();
  }
  else if (GamePad.isDownPressed()) {
    motorBackward();
  }
  else if (GamePad.isSquarePressed()) {   // 左转
    motorLeft();
  }
  else if (GamePad.isCirclePressed()) {   // 右转
    motorRight();
  }
  else {
    motorStop();
  }

  delay(20);
}