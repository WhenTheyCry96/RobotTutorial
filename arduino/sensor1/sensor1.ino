#define SENSOR1 2 // SENSOR1의 핀 2번을 저장
#define motor1A 5 // motor1A (전진이 아닐경우, 5,6번 서로 교체)
#define motor1B 6 // motor1B (전진이 아닐경우, 5,6번 서로 교체)
#define motor2A 9 // motor2A (전진이 아닐경우, 9,10번 서로 교체)
#define motor2B 10 // motor2B (전진이 아닐경우, 9,10번 서로 교체)

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR1, INPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value1 = digitalRead(SENSOR1);
  
  Serial.print("조도센서: ");
  Serial.println(value1);
  
  if (value1 == HIGH){
    // LED 센서에 HIGH가 입력된다면?
    analogWrite(motor1A, 200); // 전진
    analogWrite(motor1B, 0);
    analogWrite(motor2A, 200); // 전진
    analogWrite(motor2B, 0);
  }

  else {
    analogWrite(motor1A, 0);
    analogWrite(motor1B, 200); // 후진
    analogWrite(motor2A, 0);
    analogWrite(motor2B, 200); // 후진
  }
  delay(50);
}
