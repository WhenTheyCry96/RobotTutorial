#include <Servo.h>
#include <NewPing.h>
/*
초음파 센서를 부착하세요
 */
#define echoPin 12 // 에코 (echo) 핀 12번에
#define trigPin 13 // 트리거 (trig) 핀 13번에
#define MAX_DISTANCE 100 // 최대 거리 인지 100 cm로

NewPing sonar1(trigPin, echoPin, MAX_DISTANCE);

/*
부저를 부착하세요
 */
#define buzzer 7 // 부저를 7번 핀에 부착

/* 
모터의 왼쪽/오른쪽 그리고 전진/후진을 본인의 자동차에 맞춰서
#define 쪽에서 수정하세요
 */
#define Motor_L_GO 5    // 왼쪽 모터 전진
#define Motor_L_BACK 6  // 왼쪽 모터 후진
#define Motor_R_GO 9    // 오른쪽 모터 전진
#define Motor_R_BACK 10 // 오른쪽 모터 후진

/*
센서의 왼쪽/가운데/오른쪽을 본인의 자동차에 맞춰서 
#define 쪽에서 수정하세요
 */
#define SENSOR_L 2 // 왼쪽 조도 센서
#define SENSOR_C 3 // 중간 조도 센서
#define SENSOR_R 4 // 오른쪽 센서

/*
센서의 HIGH/LOW가 잘 들어오는지, serial모니터로 확인하면서
드라이버로 가변저항을 돌려보세요
 */
int SL;    //좌측센서 상태
int SC;    //중간센서 상태
int SR;    //우측센서 상태

void setup() {
  //모터 핀 설정
  pinMode(Motor_L_GO,OUTPUT);   // (PWM)
  pinMode(Motor_L_BACK,OUTPUT); // (PWM)
  pinMode(Motor_R_GO,OUTPUT);   // (PWM) 
  pinMode(Motor_R_BACK,OUTPUT); // (PWM)
  // 센서 핀 설정
  pinMode(SENSOR_L, INPUT);     //좌측센서포트를 입력으로 정의
  pinMode(SENSOR_C, INPUT);     //중간센서포트를 입력으로 정의
  pinMode(SENSOR_R, INPUT);     //우측센서포트를 입력으로 정의
  // 부저 핀 설정
  pinMode(buzzer, OUTPUT);

  //시리얼 모니터 통신
  Serial.begin(9600);
}

void loop() {
  //초음파센서 거리 재기 (by NewPing 라이브러리!)
  int distance = sonar1.ping_cm();
  
  //신호가 있으면 LOW, 신호가 없으면 HIGH
  SL = digitalRead(SENSOR_L);
  SC = digitalRead(SENSOR_C);
  SR = digitalRead(SENSOR_R);  
  
  //시리얼 모니터 출력
  Serial.print("왼쪽 조도센서: ");
  Serial.print(SL);
  Serial.print(", 가운데 조도센서: ");
  Serial.print(SC);
  Serial.print(", 오른쪽 조도센서: ");
  Serial.print(SR);
  Serial.print(", 초음파 센서 거리: ");
  Serial.print(distance);
  Serial.println(" [cm]");
  
  if (SL == HIGH && distance >= 5 && distance <= 30 && SR == LOW) {
    left();
  }
  else if (SR == HIGH && distance >= 5 && distance <= 30 && SL == LOW) {
    right();
  }
  else if (SL == HIGH && distance >= 5 && distance <= 30 && SR == HIGH) {
    go();
  }
  else if (distance < 5) {
    brake();    
  }
  else {
    spin();
  }
}

void go()//자동차가 전진하는 함수
{
  /*
  velocity하고, duration을 조절해보세요
  velocity: 0~255까지 가능 (너무 숫자가 작으면 모터가 안 돌 수도)
  duration: ms 단위 (ex. 100 = 0.1 초, 500 = 0.5초)
   */
  int velocity = 180;
  int duration = 50;
  analogWrite(Motor_L_GO, velocity);
  analogWrite(Motor_L_BACK, 0);
  analogWrite(Motor_R_GO, velocity);
  analogWrite(Motor_R_BACK, 0);
  delay(duration);     
}

void back()//자동차가 후진하는 함수
{
  /*
  velocity하고, duration을 조절해보세요
  velocity: 0~255까지 가능 (너무 숫자가 작으면 모터가 안 돌 수도)
  duration: ms 단위 (ex. 100 = 0.1 초, 500 = 0.5초)
   */
  int velocity = 180;
  int duration = 50;
  analogWrite(Motor_L_GO, 0);
  analogWrite(Motor_L_BACK, velocity);
  analogWrite(Motor_R_GO, 0);
  analogWrite(Motor_R_BACK, velocity);
  delay(duration);     
}

void left()//자동차가 좌회진하는 함수
{
  /*
  velocity하고, duration을 조절해보세요
  velocity: 0~255까지 가능 (너무 숫자가 작으면 모터가 안 돌 수도)
  duration: ms 단위 (ex. 100 = 0.1 초, 500 = 0.5초)
   */
  int velocityL = 180; // 왼쪽모터 앞으로 가는 속도
  int velocityR = 50;  // 오른쪽모터 뒤로 가는 속도
  int duration = 50;
  analogWrite(Motor_L_GO, velocityL);
  analogWrite(Motor_L_BACK, 0);
  analogWrite(Motor_R_BACK, velocityR);
  analogWrite(Motor_R_GO, 0);
  delay(duration);     
}

void right()//자동차가 우회진하는 함수
{
  /*
  velocity하고, duration을 조절해보세요
  velocity: 0~255까지 가능 (너무 숫자가 작으면 모터가 안 돌 수도)
  duration: ms 단위 (ex. 100 = 0.1 초, 500 = 0.5초)
   */
  int velocityL = 50;  // 왼쪽모터 뒤로 가는 속도
  int velocityR = 180; // 오른쪽모터 앞으로 가는 속도
  int duration = 50;
  analogWrite(Motor_L_GO, 0);
  analogWrite(Motor_L_BACK, velocityL);
  analogWrite(Motor_R_GO, velocityR);
  analogWrite(Motor_R_BACK, 0);
  delay(duration);     
}

void brake()//자동차가 멈추는 함수
{
  /*
  velocity하고, duration을 조절해보세요
  velocity: 0~255까지 가능 (너무 숫자가 작으면 모터가 안 돌 수도)
  duration: ms 단위 (ex. 100 = 0.1 초, 500 = 0.5초)
   */
  int duration = 100;
  analogWrite(Motor_L_BACK, 0);
  analogWrite(Motor_L_GO, 0);
  analogWrite(Motor_R_BACK, 0);
  analogWrite(Motor_R_GO, 0);
  delay(duration);     
}

void spin()//자동차가 제자리에서 도는 함수
{
  /*
  velocity하고, duration을 조절해보세요
  velocity: 0~255까지 가능 (너무 숫자가 작으면 모터가 안 돌 수도)
  duration: ms 단위 (ex. 100 = 0.1 초, 500 = 0.5초)
   */
  int velocity = 200;
  int duration = 100;
  analogWrite(Motor_L_GO, velocity);
  analogWrite(Motor_L_BACK, 0);
  analogWrite(Motor_R_BACK, velocity);
  analogWrite(Motor_R_GO, 0);
  delay(duration);     
}
