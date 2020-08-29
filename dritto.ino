#define REL_SX1  4
#define REL_SX2  5
#define REL_DX1 8
#define REL_DX2  9
#define pwm_dx 7
#define pwm_sx 6
#define SENSORE_DX A15
#define SENSORE_SX A14

int velocita_iniziale = 255;

long errore = 0;
float correzione_potenza = 1;

boolean newRead_dx = true;
boolean newRead_sx = true;

 long contatore_dx = 0;
 boolean verso_dx = true;
 

 long contatore_sx = 0;
 boolean verso_sx = true;


void setup() {
Serial.begin(115200);

  
  pinMode(pwm_sx, OUTPUT);
  pinMode(pwm_dx, OUTPUT);
  pinMode(REL_SX1, OUTPUT);
  pinMode(REL_SX2, OUTPUT);
  pinMode(REL_DX1, OUTPUT);
  pinMode(REL_DX2, OUTPUT);

 pinMode(SENSORE_DX, INPUT);
 pinMode(SENSORE_SX, INPUT);

  


  digitalWrite(REL_SX1, LOW);
  digitalWrite(REL_SX2, LOW);
  verso_sx = false;
  newRead_sx = true;
  digitalWrite(REL_DX1, HIGH);
  digitalWrite(REL_DX2, HIGH);
  verso_dx = false;
  newRead_dx = true;

 //calibrazione();

   delay(2000);
   
  analogWrite(pwm_sx, velocita_iniziale);
  analogWrite(pwm_dx, velocita_iniziale);



}

void loop() {

foward(50);

//if(abs(contatore_dx) == 13){ analogWrite(pwm_dx, velocita_iniziale*0); delay(3000);}
//if(abs(contatore_sx) == 13){ analogWrite(pwm_sx, velocita_iniziale*0); delay(3000);}
//Serial.println(analogRead(SENSORE_DX));
}





void conta_passi(){


if(analogRead(SENSORE_DX) < 900){newRead_dx = true;}
if(analogRead(SENSORE_SX) < 900){newRead_sx = true;}

if(newRead_dx == true){
if(analogRead(SENSORE_DX) > 900 && verso_dx == true){contatore_dx++; newRead_dx = false;}
if(analogRead(SENSORE_DX) > 900 && verso_dx == false){contatore_dx--; newRead_dx = false;}
}



if(newRead_sx == true){
if(analogRead(SENSORE_SX) > 900 && verso_sx == true){contatore_sx++; newRead_sx = false;}
if(analogRead(SENSORE_SX) > 900 && verso_sx == false){contatore_sx--; newRead_sx = false;}
} 


//else{contatore_dx = contatore_dx; contatore_sx = contatore_sx;}
calcolo_errore();
Serial.print("passi dx = ");Serial.print(contatore_dx);Serial.print(" :: ");Serial.print("passi sx = ");Serial.print(contatore_sx);Serial.println(" :: ");
//Serial.print("errore = ");Serial.print(errore);Serial.print(" :: ");Serial.print("correzione_potenza % = ");Serial.print(correzione_potenza);Serial.println(" :: ");
  
  
  
  
  
  }


void calcolo_errore(){
  
  errore = abs(abs(contatore_dx)-abs(contatore_sx));
  correzione_potenza = map(errore, 0, 3, 100, 30); correzione_potenza = correzione_potenza/100;
  if (correzione_potenza <= 0.20){correzione_potenza = 0.20; }
  }

void correzzione_velocita(){
  float diff_velocita = 0;
  float velocita_dx = velocita_iniziale;
  float velocita_sx = velocita_iniziale;


  
/*  diff_velocita = abs(velocita_sx*correzione_potenza) - (velocita_dx*correzione_potenza);

  if(diff_velocita <= 10){diff_velocita = velocita_iniziale-diff_velocita;}
  */
 
  
  if(abs(contatore_sx) > abs(contatore_dx)){ analogWrite(pwm_sx, velocita_sx*correzione_potenza); }
  else{analogWrite(pwm_dx, velocita_dx*correzione_potenza);}

  
  Serial.print("vel inizio = ");Serial.print(velocita_iniziale);Serial.print(" :: ");Serial.print("velocità dx = ");Serial.print(velocita_dx*correzione_potenza);Serial.print(" :: ");Serial.print("velocità sx = ");Serial.print(velocita_sx*correzione_potenza);Serial.print(" :: ");
  Serial.print("correzione_potenza % = ");Serial.print(correzione_potenza);Serial.println(" :: ");
  }



void calibrazione(){
  int velocita_calibrazione = 30;
  boolean DX_CALIBRATO = false;
  boolean SX_CALIBRATO = false;
  analogWrite(pwm_dx, velocita_calibrazione); 
  analogWrite(pwm_sx, velocita_calibrazione); 

while(DX_CALIBRATO == false && SX_CALIBRATO == false){
  
   
  if(analogRead(SENSORE_DX) < 900){analogWrite(pwm_dx, velocita_calibrazione*0);DX_CALIBRATO = true;}
  if(analogRead(SENSORE_SX) < 900){analogWrite(pwm_sx, velocita_calibrazione*0);SX_CALIBRATO = true;}
Serial.println("sto calibrando");
  }

}

void foward(int total_step){
  int start_step = (abs(abs(contatore_dx)+abs(contatore_sx)))/2;
  int real_step = 0;
  analogWrite(pwm_sx, velocita_iniziale);
  analogWrite(pwm_dx, velocita_iniziale);
  while(real_step < total_step){
    real_step = (abs(abs(contatore_dx)+abs(contatore_sx)))/2 - start_step;
    correzzione_velocita();
    conta_passi();
  }
  analogWrite(pwm_sx, 0);
  analogWrite(pwm_dx, 0);
  delay(7000);
}

void turn_right(int total_step){
  analogWrite(pwm_sx, velocita_iniziale);
  analogWrite(pwm_dx, 0);
  int start_step = abs(contatore_sx);
  int real_step = 0;
  while(real_step < total_step){
    real_step = abs(contatore_sx) - start_step;
    conta_passi();
    Serial.println(real_step);
  }
  analogWrite(pwm_sx, 0);
  analogWrite(pwm_dx, 0);
  delay(2000);
}
