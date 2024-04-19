
//#define D0 A0
#define D0 8
unsigned long ultimo_evento = 0;

void setup(){
  pinMode(D0, INPUT);
  Serial.begin(115200);
}

void loop(){
  //int saida = analogRead(D0);
  int saida = digitalRead(D0);
  //Serial.println(saida);
  if(saida == LOW){
    if(millis() - ultimo_evento > 25){
      Serial.println("som de palmas detectadas!");
    }
    ultimo_evento = millis();
  }
}