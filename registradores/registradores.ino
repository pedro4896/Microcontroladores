#include <avr/io.h>

byte a = 0;
byte b = 0;
byte controle = 0;

void setup() {
  DDRD = 0b11111111;
  PORTD = 0b00000001;
}

void loop() {
  for(int i = 0; i < 8; i++){
    PORTD = PORTD | (1<<i);
    if(i>0){
      PORTD = PORTD & ~(1<<i-1);
    }
    delay(100);
  }

  for(int i = 7; i >= 0; i--){
    PORTD = PORTD | (1<<i);
    if(i<7){
      PORTD = PORTD & ~(1<<i+1);
    }
    delay(100);
  }

}
