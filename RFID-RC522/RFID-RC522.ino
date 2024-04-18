#include <Wire.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <MFRC522.h> //INCLUSÃO DE BIBLIOTECA

#define SS_PIN 10 //PINO SDA
#define RST_PIN 9 //PINO DE RESET
#define BUZZER_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN); //PASSAGEM DE PARÂMETROS REFERENTE AOS PINOS


const int pinoLedVerde = 3; //PINO DIGITAL REFERENTE AO LED VERDE
const int pinoLedVermelho = 2; //PINO DIGITAL REFERENTE AO LED VERMELHO

void setup(){

  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  rfid.PCD_Init(); //INICIALIZA MFRC522
  
  pinMode(pinoLedVerde, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoLedVermelho, OUTPUT); //DEFINE O PINO COMO SAÍDA
  
  digitalWrite(pinoLedVerde, LOW); //LED INICIA DESLIGADO
  digitalWrite(pinoLedVermelho, LOW); //LED INICIA DESLIGADO
}

void loop() {
  leituraRfid(); //CHAMA A FUNÇÃO RESPONSÁVEL PELA VALIDAÇÃO DA TAG RFID
}

//FUNÇÃO DE VALIDAÇÃO DA TAG RFID
void leituraRfid(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) //VERIFICA SE O CARTÃO PRESENTE NO LEITOR É DIFERENTE DO ÚLTIMO CARTÃO LIDO. CASO NÃO SEJA, FAZ
    return; //RETORNA PARA LER NOVAMENTE

  /***INICIO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
  String strID = ""; 
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
/***FIM DO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/

  //O ENDEREÇO "27:41:AA:AB" DEVERÁ SER ALTERADO PARA O ENDEREÇO DA SUA TAG RFID QUE CAPTUROU ANTERIORMENTE
  if (strID.indexOf("B3:4D:0D:13") >= 0) { //SE O ENDEREÇO DA TAG LIDA FOR IGUAL AO ENDEREÇO INFORMADO, FAZ
    digitalWrite(pinoLedVerde, HIGH); //LIGA O LED VERDE
    tone(BUZZER_PIN, 400); // Toca a frequência 400 Hz
    delay(100); // Mantém o som por 100 milissegundos
    noTone(BUZZER_PIN); // Desliga o som
    //delay(3000); //INTERVALO DE 4 SEGUNDOS
    digitalWrite(pinoLedVerde, LOW); //DESLIGA O LED VERDE
  }else{ //SENÃO, FAZ (CASO A TAG LIDA NÃO SEJÁ VÁLIDA)
    digitalWrite(pinoLedVermelho, HIGH); //LIGA O LED VERMELHO
    for (int i = 200; i <= 1000; i += 100) {
      tone(BUZZER_PIN, i); // Tocar tom crescente
      delay(50); // Breve pausa
      noTone(BUZZER_PIN); // Parar o tom
      delay(50); // Breve pausa

      tone(BUZZER_PIN, i); // Tocar tom decrescente
      delay(50); // Breve pausa
      noTone(BUZZER_PIN); // Parar o tom
      delay(50); // Breve pausa
    }
    digitalWrite(pinoLedVermelho, LOW); //DESLIGA O LED VERDE
  }

  rfid.PICC_HaltA(); //PARADA DA LEITURA DO CARTÃO
  rfid.PCD_StopCrypto1(); //PARADA DA CRIPTOGRAFIA NO PCD
  }