#include <Wire.h>
void setup() {
  Wire.begin();
}

byte x1 = 0; // marcelo
byte x2 = 0; // patriota
byte x3 = 0; // ismaylla
byte x4 = 0; // Vitória
byte x5 = 0;
byte x6 = 0; // Jack
byte x7 = 0; // pedro
byte x8 = 0; // fabio
byte x9 = 0; // ingrid
byte x10 = 0; // jota

void loop() {
  Wire.beginTransmission(1);
  Wire.write("x1 = ");
  Wire.write(x1);
  Wire.endTransmission();

  Wire.beginTransmission(2);
  Wire.write("x2 = ");
  Wire.write(x2);
  Wire.endTransmission();

  Wire.beginTransmission(3);
  Wire.write("x3 = ");
  Wire.write(x3);
  Wire.endTransmission();

  Wire.beginTransmission(4);
  Wire.write("x4 = ");
  Wire.write(x4);
  Wire.endTransmission();

  Wire.beginTransmission(5);
  Wire.write("x5 = ");
  Wire.write(x5);
  Wire.endTransmission();

  Wire.beginTransmission(6);
  Wire.write("x6 = ");
  Wire.write(x6);
  Wire.endTransmission();

  Wire.beginTransmission(7);
  Wire.write("x7 = ");
  Wire.write(x7);
  Wire.endTransmission();

  Wire.beginTransmission(8);
  Wire.write("x8 = ");
  Wire.write(x8);
  Wire.endTransmission();

  Wire.beginTransmission(9);
  Wire.write("x9 = ");
  Wire.write(x9);
  Wire.endTransmission();

  Wire.beginTransmission(10);
  Wire.write("x10 = ");
  Wire.write(x10);
  Wire.endTransmission();

  x1++; 
  x2++; 
  x3++; 
  x4++; 
  x5++;
  x6++; 
  x7++; 
  x8++; 
  x9++; 
  x10++; 

  delay(1000);
}