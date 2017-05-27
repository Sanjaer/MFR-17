#include <Wire.h>

#define SLAVE_ADDRESS 0x04

int number = 0;
int state = 0; // Ready to read
byte *inst; // Reads the instructions
bool changed = false;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  Serial.println("Ready!");
}

void loop() {
  if (changed){
    changed=false;
    for (int i=0; i<inst[0]; i++){
      Serial.println(inst[i]);
    }
  }
  delay(100);
}

// callback for received data
void receiveData(int byteCount){
  free(inst);
  short module = Wire.read();
  byte size = Wire.read();
  size=size+2;
  //inst = new int*[size]; // C++ way
  inst = (byte*) malloc(size * sizeof(byte)); // C way
  inst[0]=size;
  inst[1]=module;

  short cnt = 2;
  while(Wire.available()) {
    inst[cnt] = Wire.read();
    cnt++;
  }
  changed=true;
}

// callback for sending data
void sendData(){
  byte number[] = {3,2};
  Wire.write(number, 2);
}
