#define buzzer  7
#define echoPin 12
#define trigPin 13

// 한 번 부저가 총 울리는 시간
int buzzertime = 200;

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
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
  
  // 부저로 거리에 따른 알람 울리기
  alarm(distance);
  delay(200);
}

void alarm(float distance) {
  if (distance >= 50) {
    tone(buzzer, 500, buzzertime);
  }
  else {
    // 거리가 가까워질수록, 더 높은 소리가 난다.
    tone(buzzer, 500*50/distance, buzzertime);
  }
}
