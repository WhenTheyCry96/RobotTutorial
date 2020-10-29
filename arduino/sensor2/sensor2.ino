#define SENSOR1 2 // SENSOR1의 핀 2번을 저장(제일 왼쪽)
#define SENSOR2 3 // SENSOR2의 핀 3번을 저장 (가운데 센서)
#define SENSOR3 4 // SENSOR3의 핀 4번을 저장 (제일 오른쪽)
#define motor1A 5 // motor1A (전진이 아닐경우, 5,6번 서로 교체)
#define motor1B 6 // motor1B (전진이 아닐경우, 5,6번 서로 교체)
#define motor2A 9 // motor2A (전진이 아닐경우, 9,10번 서로 교체)
#define motor2B 10 // motor2B (전진이 아닐경우, 9,10번 서로 교체)

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR1, INPUT);
  pinMode(motor1A, OUTPUT); // motor1 : 왼쪽 모터
  pinMode(motor1B, OUTPUT); // motor2 : 오른쪽 모터
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int S1 = digitalRead(SENSOR1); // SENSOR1의 상태값 저장
  int S2 = digitalRead(SENSOR2); // SENSOR2의 상태값 저장
  int S3 = digitalRead(SENSOR3); // SENSOR3의 상태값 저장
  
  if (s1 == HIGH && s3 == LOW){
    // 조도센서 왼쪽은 HIGH 그리고 오른쪽은 LOW일 때 (왼쪽에 선)
    analogWrite(motor1A, 150); // 전진
    analogWrite(motor2B, 150); // 후진
    // 우회전
    delay(100);
  }

  else if ((s1 == LOW && s3 == HIGH)) {
    // 조도센서 왼쪽은 LOW 그리고 오른쪽은 HIGH일 때 (오른쪽에 선)
    analogWrite(motor1B, 150); // 후진
    analogWrite(motor2A, 150); // 전진
    // 좌회전
    delay(100);
  }

  else if ((s1 == HIGH && s2 == HIGH && s3 == HIGH)) {
    // 바로 앞에 선이 있을 때
    analogWrite(motor1B, 150); // 후진
    analogWrite(motor2B, 150); // 후진
    // 뒤로 후진
    delay(100);
  }

  else {
    // 위의 두 경우가 아닐 때
    analogWrite(motor1A, 150); // 전진
    analogWrite(motor2A, 150); // 전진
    // 앞으로 전진
    delay(100);
  }
  
}
