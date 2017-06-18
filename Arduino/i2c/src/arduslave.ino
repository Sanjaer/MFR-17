#include <Wire.h>

#define SLAVE_ADDRESS 0x04
#define ACK 0x01

int number = 0;
int state = 0; // Ready to read
byte *inst; // Reads the instructions
bool changed = false;
bool data_requested = false;
short module = 0;
byte size = 0;

void setup() {
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  Serial.println("Ready!");
}

void loop() {
  if(data_requested){
    outDispatcher();
    data_requested = false;
  } else if (changed){
    // Serial.print("Changed!:");
    // for (int i=0; i<inst[0]; i++){
    //   Serial.println(inst[i]);
    // }
    if(inst[1] == 0x0A){
      setMotors();
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
  if (module < 0xA0){
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
  if (module == 0xA0){
    Wire.write(ACK);
  } else {
    data_requested = true;
  }
}

// TODO: info sending protocol
void outDispatcher(){
  if (module == 0xAA){
    Wire.write(ACK);
  }
}
