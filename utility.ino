void step_counter(){
  if(analogRead(SENSOR_DX) < 900)
    newRead_dx = true;
  if(analogRead(SENSOR_SX) < 900)
    newRead_sx = true;

  if(newRead_dx == true){
    if(analogRead(SENSOR_DX) > 900 && verso_dx == true)
      counter_dx++; newRead_dx = false;
    if(analogRead(SENSOR_DX) > 900 && verso_dx == false)
      counter_dx--; newRead_dx = false;
  }

  if(newRead_sx == true){
    if(analogRead(SENSOR_SX) > 900 && verso_sx == true)
      counter_dx++; newRead_sx = false;
    if(analogRead(SENSOR_SX) > 900 && verso_sx == false)
      counter_sx--; newRead_sx = false;
  }  
  calculate_error();
}

void calculate_error(){
  error = abs(abs(counter_dx)-abs(counter_sx));
  power_correction = map(error, 0, 3, 100, 30); 
  power_correction /= 100;
  if (power_correction <= 0.20)
    power_correction = 0.20;
}

void speed_correction(){
  float diff_velocita = 0;
  float speed_dx = start_speed;
  float speed_sx = start_speed;
  /*
  diff_velocita = abs(velocita_sx*correzione_potenza) - (velocita_dx*correzione_potenza);

  if(diff_velocita <= 10){diff_velocita = velocita_iniziale-diff_velocita;}
  */
  
  if(abs(counter_sx) > abs(counter_dx))
    analogWrite(PWM_SX, speed_sx*power_correction);
  else
    analogWrite(PWM_DX, speed_dx*power_correction);

  /*Serial.print("vel inizio = ");Serial.print(velocita_iniziale);Serial.print(" :: ");Serial.print("velocità dx = ");Serial.print(velocita_dx*correzione_potenza);Serial.print(" :: ");Serial.print("velocità sx = ");Serial.print(velocita_sx*correzione_potenza);Serial.print(" :: ");
  Serial.print("correzione_potenza % = ");Serial.print(correzione_potenza);Serial.println(" :: ");*/
}

void calibration(){
  int speed_calibration = 30;
  boolean dx_calibrated = false;
  boolean sx_calibrated = false;
  
  analogWrite(PWM_DX, speed_calibration); 
  analogWrite(PWM_SX, speed_calibration); 

  while(dx_calibrated == false && sx_calibrated == false){
    if(analogRead(SENSOR_DX) < 900){
      analogWrite(PWM_DX, speed_calibration*0);
      dx_calibrated = true;
    }
    if(analogRead(SENSOR_SX) < 900){
      analogWrite(PWM_SX, speed_calibration*0);
      sx_calibrated = true;
  }
  Serial.println("sto calibrando");
  }

}
