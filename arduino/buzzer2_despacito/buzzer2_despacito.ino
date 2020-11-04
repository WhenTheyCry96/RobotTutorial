#include "pitches.h"
#define led    8
#define buzzer 7

int noteDuration;
int pauseBetweenNotes = 0;
int keytime;

void setup() {
  pinMode(led, OUTPUT);    
  keytime=640;
}

void loop() {
 chorus();
}

void chorus(){
  note(keytime, NOTE_D5);
  note(keytime, NOTE_CS5);
  digitalWrite(led, HIGH);   // (1)
  note(keytime/2, NOTE_B4);
  note(keytime/4, NOTE_FS4);
  digitalWrite(led, LOW);    // (2)
  delay(keytime/4);
  digitalWrite(led, HIGH);   // (3)
  note(keytime/4, NOTE_FS4);
  note(keytime/4, NOTE_FS4);
  digitalWrite(led, LOW);    // (4)
  note(keytime/4, NOTE_FS4);
  note(keytime/4, NOTE_FS4);
  digitalWrite(led, HIGH);   //  (1) 

  note(keytime/4, NOTE_FS4);

  note(keytime/4, NOTE_B4);
  note(keytime/4, NOTE_B4);
  digitalWrite(led, LOW);    //  (2) 
  note(keytime/4, NOTE_B4);
  digitalWrite(led, HIGH);   //  (3)  
  note(keytime/2, NOTE_B4);
  digitalWrite(led, LOW);    //  (4)   

  note(keytime/4, NOTE_A4);  
      
  note(keytime/4, NOTE_B4);
  digitalWrite(led, HIGH);   //  (1) 
  delay(keytime/4); 
  delay(keytime/4); 
  note(keytime/4, NOTE_G4); 
  digitalWrite(led, LOW);    //  (2) 
  delay(keytime/4);
  digitalWrite(led, HIGH);   //  (3) 

  note(keytime/4, NOTE_G4);  
  note(keytime/4, NOTE_G4);
  digitalWrite(led, LOW);    //  (4)   
  note(keytime/4, NOTE_G4);  
  note(keytime/4, NOTE_G4);
  digitalWrite(led, HIGH);   //  (1)   
  note(keytime/4, NOTE_G4);  

  note(keytime/4, NOTE_B4);  
  note(keytime/4, NOTE_B4); 
  digitalWrite(led, LOW);    //  (2) 
  note(keytime/4, NOTE_B4);
  digitalWrite(led, HIGH);   //  (3) 
  note(keytime/2, NOTE_B4);
  digitalWrite(led, LOW);    //  (4) 

  note(keytime/4, NOTE_CS5);
  note(keytime/4, NOTE_D5);
  digitalWrite(led, HIGH);   //  (1) 
  delay(keytime/4);
  delay(keytime/4);
  note(keytime/4, NOTE_A4);
  digitalWrite(led, LOW);    //  (2)      
  delay(keytime/4);
  digitalWrite(led, HIGH);   //  (3) 

  note(keytime/4, NOTE_A4);     
  note(keytime/4, NOTE_A4);
  digitalWrite(led, LOW);    //  (4)           
  note(keytime/4, NOTE_A4);               
  note(keytime/4, NOTE_A4);
  digitalWrite(led, HIGH);   //  (1)                

  note(keytime/4, NOTE_D5);          
  note(keytime/4, NOTE_CS5);               
  note(keytime/4, NOTE_D5);
  digitalWrite(led, LOW);              
  note(keytime/4, NOTE_CS5);
  digitalWrite(led, HIGH);            
  note(keytime/2, NOTE_D5);
  digitalWrite(led, LOW);    
  note(keytime/4, NOTE_E5);
  note_jai(keytime/2, NOTE_E5,keytime/4);  // (1)
  note(keytime/2, NOTE_E5);  

  tone(8,NOTE_CS5 ,keytime*3/4);
  delay(keytime/4);
  delay(keytime/4);
  digitalWrite(led, LOW);    //  (2)                     
  delay(keytime/4);
  digitalWrite(led, HIGH);   //  (3)                     
  noTone(8);
  delay(keytime/4);

  delay(keytime/4);
  digitalWrite(led, LOW);    //  (4) 

  delay(keytime/4);
  delay(keytime/4);       
}

void note(int noteDuration, int LaNota){
  tone(buzzer,LaNota, noteDuration*0.9);
  pauseBetweenNotes = noteDuration * 1.1;
  delay(pauseBetweenNotes);
  noTone(8);  
}

void note_jai(int noteDuration, int LaNota, int Desfase){
  tone(buzzer,LaNota ,noteDuration*0.9);
  pauseBetweenNotes = noteDuration * 1.1;
  delay(Desfase);
  digitalWrite(led, HIGH); 
  delay(pauseBetweenNotes-Desfase);
  noTone(8);  
}
