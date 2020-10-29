void setup() {

  pinMode(5, OUTPUT); // 5번핀을 출력모드로 설정합니다.

  pinMode(6, OUTPUT); // 6번핀을 출력모드로 설정합니다.

  pinMode(9, OUTPUT); // 10번핀을 출력모드로 설정합니다.

  pinMode(10, OUTPUT);// 11번핀을 출력모드로 설정합니다.

}

void loop() {
  
  for(int i=0;i<255;i++){
    // for 문 반복문
    analogWrite(5,i); // 5번 핀에 (i/255*5 [V])만큼 아날로그 신호 출력 
    delay(10);        // 10 ms 만큼 쉬었다가
                      // 속도가 점점? -> 빨라진다
  }
  for(int i=255;i>0;i--){
    analogWrite(5,i); // 5번 핀에 (i/255*5 [V])만큼 아날로그 신호 출력 
    delay(10);        // 10 ms 만큼 쉬었다가
                      // 속도가 점점? -> 느려진다
   for(int i=0;i<255;i++){
    analogWrite(9,i); // 9번 핀에 (i/255*5 [V])만큼 아날로그 신호 출력 
    delay(10);        // 10 ms 만큼 쉬었다가
                      // 속도가 점점? -> 빨라진다
  }
  for(int i=255;i>0;i--){
    analogWrite(9,i); // 9번 핀에 (i/255*5 [V])만큼 아날로그 신호 출력 
    delay(10);        // 10 ms 만큼 쉬었다가
                      // 속도가 점점? -> 느려진다
  }
}
