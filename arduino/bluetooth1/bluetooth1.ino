#include <SoftwareSerial.h>
#define BT_rx 7 // 블루투스 rx 핀 7번
#define BT_tx 8 // 블루투스 tx 핀 8번

SoftwareSerial bt(BT_tx, BT_rx);

void setup() {
 bt.begin(9600);     // 블루투스 통신 시작
 Serial.begin(9600); // 시리얼 통신 시작
}

void loop() {
 if (bt.available()) {
  // 블루투스쪽에서 데이터가 수신됐을때,
  // 시리얼 모니터에 데이터 출력
  Serial.write(bt.read()); 
 }
 if (Serial.available()) {
  // 시리얼 모니터에서 데이터 전송했을때,
  // 블루투스쪽에 데이터 출력
  bt.write(Serial.read());
 }
}
