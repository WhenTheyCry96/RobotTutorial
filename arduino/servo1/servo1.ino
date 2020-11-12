#include <Servo.h>
#define servoPin 9

int angle = 0;  // 서보모터 각도 0도로 설정
Servo servo;    // 서보모터 클래스 인스턴스 생성

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
}

void loop() {
  for (angle = 0; angle < 180; angle++) {
    // 서보 모터의 각도를 0 -> 180도 까지 증가
    servo.write(angle);
    delay(15);
  }
  for (angle = 180; angle > 0; angle--) {
    // 서보 모터의 각도를 180 -> 0도 까지 감소
    servo.write(angle);
    delay(15);
  }
}
