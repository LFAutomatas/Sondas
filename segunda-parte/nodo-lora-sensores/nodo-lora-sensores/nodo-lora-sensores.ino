#include <OneWire.h>
#include <DallasTemperature.h>

#define TURBIDITY_PIN             A0
#define PH_PIN                    A3
#define TEMPERATURE_PIN           A4
#define CONDUCTIVITY_PIN          A5
#define LED_PIN                   13
#define SPEAKER_PIN               3

#define SPEAKER_FRECUENCY         ( 220 * 1.059 )
#define DECIMAL_PRINT_PRECISION   2

#define HIGH_PH                   5
#define MEDIUM_TEMPERATURE        4
#define HIGH_TEMPERATURA          3
#define HIGH_TURBIDITY            2
#define HIGH_CONDUCTIVITY         1       
#define NORMAL_VALUES             0
#define INITIAL_STATE            -1

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensors(&oneWire);
int state = INITIAL_STATE;
float conductividad;
float temperatura;
float turbidez; 
float PH;

void ledOn()
{
  digitalWrite(LED_PIN, 1);
}

void ledOff()
{
  digitalWrite(LED_PIN, 0);
}

void speakerOn()
{
  tone(SPEAKER_PIN,SPEAKER_FRECUENCY);
}

void speakerOff()
{
  noTone(SPEAKER_PIN);
}

void sendMessage(String topic, String message)
{
  String request = "/" + topic + "/" + message;
  Serial.println(request);
}

void onHighPh()
{
  speakerOn();
  ledOn();
  sendMessage(
    "alarmaPH",
    "Verter solucion acida/alcalina para regular el PH."
  );
}

void onLowPh()
{
  speakerOff();
  ledOff();
  sendMessage(
    "alarmaPH",
    "PH reestablecido a valores aceptables."
  );
}

void onMediumTemperature()
{
  sendMessage(
    "alertaTemp",
    "Los niveles de temperatura actuales favorecen la reproducciOn de bacterias nocivas para la salud."
  );
}

void onLowTemperature()
{
  sendMessage(
    "alertaTemp",
    "Los niveles de temperatura actuales ya No favorecen la reproducciOn de bacterias nocivas para la salud."
  );
}

void onHighTemperature()
{
  ledOn();
  sendMessage(
    "alertaTemp",
    "Prohibir descarga de agua."
  );
}

void onFromHighToMediumTemperature()
{
  ledOff();
  sendMessage(
    "alertaTemp",
    "Volver a permitir la descarga de agua."
  );
}

void onHighTurbidity()
{
  sendMessage(
    "alertaExtraccionAgua",
    "Extraer residuos."
  );
}

void onLowTurbidity()
{
  sendMessage(
    "alertaExtraccionAgua",
    "Ya no es necesario extraer residuos."
  );
}

void onHighConductivity()
{
  sendMessage(
    "alertaConsumoAgua",
    "Agua no apta para el consumo."
  );
}

void onLowConductivity()
{
  sendMessage(
    "alertaConsumoAgua",
    "El agua ah vuelto a ser apta para el consumo."
  );
}

void onNormalesValues()
{
}

void leaveCurrentState()
{
  switch(state)
  {
    case HIGH_PH: onLowPh(); break;
    case MEDIUM_TEMPERATURE: onLowTemperature(); break;
    case HIGH_TEMPERATURA: onFromHighToMediumTemperature(); break;
    case HIGH_TURBIDITY: onLowTurbidity(); break;
    case HIGH_CONDUCTIVITY: onLowConductivity(); break;
    default: break;
  }
}

void changeState(int newState)
{
  if(newState < state)
    leaveCurrentState();
  state = newState;
  switch(state)
  {
    case HIGH_PH: onHighPh(); break;
    case MEDIUM_TEMPERATURE: onMediumTemperature(); break;
    case HIGH_TEMPERATURA: onHighTemperature(); break;
    case HIGH_TURBIDITY: onHighTurbidity(); break;
    case HIGH_CONDUCTIVITY: onHighConductivity(); break;
    default: break;
  }
}

void automata()
{
  int newState = NORMAL_VALUES;
  if(PH < 6 || PH > 9)
    newState = HIGH_PH;
  else if(temperatura > 25 && temperatura < 35)
    newState = MEDIUM_TEMPERATURE;
  else if(temperatura > 35)
    newState = HIGH_TEMPERATURA;
  else if(turbidez > 2000)
    newState = HIGH_TURBIDITY;
  else if(conductividad > 1500)
    newState = HIGH_CONDUCTIVITY;
  else
    newState = NORMAL_VALUES;
  if(newState != state)  
    changeState(newState);
}

float readConductivity(void)
{
  char i;
  int x,aux4;
  float aux1, aux2, aux3;
  aux1=0;
  for(i=0;i<100;i++)
  {
  aux1=aux1+((analogRead(CONDUCTIVITY_PIN)*5.00)/1023.00);
  }
  aux1=aux1/100;
  aux1=aux1*1023/5.00;
  if(aux1>=927)
  conductividad=0;
  if((aux1<927) && (aux1>=838)){
    conductividad=-30.0*(aux1-838)+3000;
  }

  if((aux1>=800)&&(aux1<=837)){
    conductividad=5800;
  }

    if((aux1>=785)&&(aux1<800)){
      conductividad=8100;
  }
  if((aux1>=769)&&(aux1<785)){
      conductividad=11200;
  }
  if((aux1>=765)&&(aux1<769)){
      conductividad=17500;
  }
  if((aux1>763)&&(aux1<765)){
      conductividad=27000;
  }
  if((aux1>774)&&(aux1<=762)){
      conductividad=30100;
  }
  if(aux1<=774){
      conductividad=40200;
  }
  return conductividad;
}

float readTurbidity(void)
{
  int x,aux4;
  int i;
  float aux1, aux2, aux3;
  aux3=0;
  for(i=0;i<100;i++)
  {
  aux3=aux3+((analogRead(TURBIDITY_PIN)*5.00)/1023.00);
  }
  aux3= aux3/100;

  if(aux3 >= 3.20) {
    turbidez=0.00;
  }
  if(aux3<3.20 && aux3>=0){
    turbidez=-1093.75*aux3 + 3500.00;  
  }

  if(aux3<0.00){
    turbidez=3500.00;
  }
  Serial.print("Turbidez: ");
  Serial.print(turbidez);
  Serial.println(" NTU");
  return turbidez;
}

float Read_Temperature(void){
  float tempC;
  tempC = DEVICE_DISCONNECTED_C;
  while(tempC == DEVICE_DISCONNECTED_C){
    sensors.requestTemperatures(); // Send the command to get temperatures
    tempC = sensors.getTempCByIndex(0);
  }
  return tempC;
}
  
float readPh(void)
{// fórmula para leer PH entre 0-14.
  return (1023 - analogRead(PH_PIN)) / 73.07;
}

void setup(void) {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  sensors.begin();
}

void loop(void) {

  temperatura = Read_Temperature();
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("^C");
  PH = readPh();
  Serial.print("PH: ");  
  Serial.println(PH, DECIMAL_PRINT_PRECISION);
  conductividad = readConductivity();
  Serial.print("Conductividad: ");
  Serial.print(conductividad);
  Serial.println("uS/cm");
  turbidez = readTurbidity();
  Serial.print("Conductividad: ");
  Serial.print(conductividad);
  Serial.println("uS/cm");
  automata();
  delay(100);
  Serial.println();
}
