#include <Wire.h>

#define SLAVE_ADDRESS 0x04
#define ACK 0x01

int number = 0;
int state = 0; // Ready to read
byte *inst; // Reads the instructions
bool changed = false;
short module = 0;
byte size = 0;

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
    Serial.print("Changed!:");
    for (int i=0; i<inst[0]; i++){
      Serial.println(inst[i]);
    }
    changed=false;
  }else{

  }
  delay(100);
}

// callback for received data
void receiveData(int byteCount){
  free(inst);
  module = Wire.read();
  if (module == 0x01 || module == 0xAA  || module == 0xAB || module == 0xAC || module == 0xAD){

  }else{
    size = Wire.read();
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

}

// callback for sending data
void sendData(){
  if (module == 0x01){
    Wire.write(ACK);
  } else if (module == 0xAA){
    Wire.write(2);
  }
}
