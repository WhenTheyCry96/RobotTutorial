#include <Servo.h>
#include <SoftwareSerial.h>

#define BT_rx 7 // 블루투스 rx 핀 7번
#define BT_tx 8 // 블루투스 tx 핀 8번
#define motor_servo 9 // 서보모터 PWM핀 9번
/*
초음파 센서를 부착하세요
 */
#define echoPin 12 // 에코 (echo) 핀 12번에
#define trigPin 13 // 트리거 (trig) 핀 13번에
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


int angle = 0;  // 서보모터 각도 0도로 설정
Servo servo;    // 서보모터 클래스 인스턴스 생성
SoftwareSerial bt(BT_tx, BT_rx);

void setup()
{
  servo.attach(motor_servo);
  
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
  // 초음파 센서 핀 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //블루투스 통신
  bt.begin(9600);
  //시리얼 모니터 통신
  Serial.begin(9600);
}

void loop()
{
  while(bt.available()) {
    // 블루투스 데이터를 읽고, btData 변수에 저장
    char btData = bt.read(); 
    if (btData == 'a'){
      // 만약 데이터가 a 일 경우, 서보를 다음과 같이
      for (angle = 0; angle < 180; angle++) {
        // 서보 모터의 각도를 0 -> 180도 까지 증가
        servo.write(angle);
        delay(15);
      }
    }
    else if (btData == 'b') {
      // 만약 데이터가 b 일 경우, 서보를 다음과 같이
      for (angle = 180; angle > 0; angle--) {
        // 서보 모터의 각도를 180 -> 0도 까지 감소
        servo.write(angle);
        delay(15);
      }      
    }
    else {
      Serial.println("블루투스 데이터가 a 혹은 b가 아닙니다!");
    }
  }
}

int detect() // 장애물이 있는지 판단하는 함수
{
  // 자동차를 멈추게 할 거리 ex. stop_dist = 10; 장애물이 10cm 이내면 멈춰라
  float stop_dist = 10;
  
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  unsigned long duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  float distance = ((float)(340 * duration) / 10000) / 2;  

  Serial.print(distance);
  Serial.println("cm");
  
  int checkD = 0; // 장애물 있으면 1 없으면 0으로 return해라 (기본값: 장애물 없음 0)
  
  if (distance < stop_dist) {
    // 장애물이 stop_dist 거리보다 짧을 경우, 부저를 울려라
    tone(buzzer, 1000, 200);
    checkD = 1; // 장애물이 있다
  }
  return checkD;
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
  int duration = 1000;
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
  int duration = 2000;
  analogWrite(Motor_L_GO, velocity);
  analogWrite(Motor_L_BACK, 0);
  analogWrite(Motor_R_BACK, velocity);
  analogWrite(Motor_R_GO, 0);
  delay(duration);     
}
