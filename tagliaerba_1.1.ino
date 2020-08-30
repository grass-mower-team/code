#define REL_SX1  4
#define REL_SX2  5
#define REL_DX1 8
#define REL_DX2  9
#define PWM_DX 7
#define PWM_SX 6
#define SENSOR_DX 15
#define SENSOR_SX 14

int start_speed = 255;

int error = 0;
float power_correction = 1;

boolean newRead_dx = true;
boolean newRead_sx = true;

int counter_dx = 0;
boolean verso_dx = true;
 
int counter_sx = 0;
boolean verso_sx = true;

void setup() {
  
  Serial.begin(115200);
  
  pinMode(PWM_SX, OUTPUT);
  pinMode(PWM_DX, OUTPUT);
  pinMode(REL_SX1, OUTPUT);
  pinMode(REL_SX2, OUTPUT);
  pinMode(REL_DX1, OUTPUT);
  pinMode(REL_DX2, OUTPUT);

  pinMode(SENSOR_DX, INPUT);
  pinMode(SENSOR_SX, INPUT);
}

void loop() {
  Serial.dtostrf("ewfw");
}
