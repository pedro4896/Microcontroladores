/* SevSeg Counter Example
 
 Copyright 2020 Dean Reading
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object
char displayStr[6]; // 5 caracteres para minutos.segundos + 1 para o terminador nulo
void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 12, 11, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
  static unsigned long lastRefreshTime = 0;
  static unsigned int minutes = 0;
  static unsigned int seconds = 0;
  const unsigned long refreshInterval = 1000; // Intervalo de atualização em milissegundos (1 segundo)
  
  if (millis() - lastRefreshTime >= refreshInterval) {
    lastRefreshTime = millis();
    // Incrementa os segundos e ajusta os minutos, se necessário
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 100) { // Limita a exibição de minutos a 99
        minutes = 0;
      }
    }
    // Constrói a string para exibir no formato "minutos.segundos"
    sprintf(displayStr, "%02d.%02d", minutes, seconds); // Formata os minutos e segundos
    sevseg.setChars(displayStr);
  }
  sevseg.refreshDisplay(); // Deve ser chamado repetidamente
}
/// END ///
