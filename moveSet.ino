void foward(int total_step){
  int start_step = (abs(abs(counter_dx)+abs(counter_sx)))/2;
  int real_step = 0;
  
  digitalWrite(REL_SX1, LOW);
  digitalWrite(REL_SX2, LOW);
  digitalWrite(REL_DX1, HIGH);
  digitalWrite(REL_DX2, HIGH);
  
  analogWrite(PWM_SX, start_speed);
  analogWrite(PWM_DX, start_speed);
  while(real_step < total_step){
    real_step = (abs(abs(counter_dx)+abs(counter_sx)))/2 - start_step;
    speed_correction();
    step_counter();
 }
}

void back(int total_step){
  int start_step = (abs(abs(counter_dx)+abs(counter_sx)))/2;
  int real_step = 0;
  
  digitalWrite(REL_SX1, HIGH);
  digitalWrite(REL_SX2, HIGH);
  digitalWrite(REL_DX1, LOW);
  digitalWrite(REL_DX2, LOW);
  
  analogWrite(PWM_SX, start_speed);
  analogWrite(PWM_DX, start_speed);
  while(real_step < total_step){
    real_step = (abs(abs(counter_dx)+abs(counter_sx)))/2 - start_step;
    speed_correction();
    step_counter();
  }
}

void turn_right(int total_step){
  analogWrite(PWM_SX, start_speed);
  analogWrite(PWM_DX, 0);
  
  int start_step = abs(counter_sx);
  int real_step = 0;
  
  while(real_step < total_step){
    real_step = abs(counter_sx) - start_step;
    step_counter();
  }
}

void turn_left(int total_step){
  analogWrite(PWM_DX, start_speed);
  analogWrite(PWM_SX, 0);
  int start_step = abs(counter_dx);
  int real_step = 0;
  while(real_step < total_step){
    real_step = abs(counter_dx) - start_step;
    step_counter();
  }
  x++;
}

void stop(int time){
  analogWrite(PWM_SX, 0);
  analogWrite(PWM_SX, 0);
  delay(time);
}
