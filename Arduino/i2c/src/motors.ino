void rightMotor(int direction){
  if(direction%2){ //FORWARD
    digitalWrite(right_motor_a, LOW);
    digitalWrite(right_motor_b, HIGH);
  } else {
    digitalWrite(right_motor_a, HIGH);
    digitalWrite(right_motor_b, LOW);
  }
}


void leftMotor(int direction){
  if(direction%2){//FORWARD
    digitalWrite(left_motor_a, LOW);
    digitalWrite(left_motor_b, HIGH);
  } else{
    digitalWrite(left_motor_a, HIGH);
    digitalWrite(left_motor_b, LOW);
  }
}


void setMotors(){
  if (inst[3] == 0x00 || inst[3] == 0x01){
    fullstop();
  }
  if(inst[0] == 4){ //Check this value
      rightMotor(inst[3]);
      leftMotor(inst[3]);
      analogWrite(right_pwm, inst[4];
      analogWrite(left_pwm, inst[5];
  } else{
    if(inst[3] == 0x02){
      rightMotor(inst[3]);
      analogWrite(right_pwm, inst[4];
    }else if(inst[3] == 0x03){
      rightMotor(BACKWARD);
      analogWrite(right_pwm, inst[4];
    }else if(inst[3] == 0x04){
      leftMotor(FORWARD);
      analogWrite(left_pwm, inst[4];
    }else if(inst[3] == 0x05){
      leftMotor(BACKWARD);
      analogWrite(left_pwm, inst[4];
    }
  }
}
