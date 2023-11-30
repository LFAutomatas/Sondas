                     /*----------------------------------------------------------------------------------------------------------------------------------*/
// Macros para activar/desactivar distintas partes del codigo --> 0L desactiva, 1L activa                                         // |
#define SENSORES_ENABLE     1L                                                                                                    // |
#define LORA_ENABLE         0L                                                                                                    // | 
#define RTC_ENABLE          0L                                                                                                    // |
#define PRUEBAS_ENABLE      0L                                                                                                    // |                                                                                                       // |  
#define TEMP_ENABLE        1L                                                                                                // |
#define PH_ENABLE       1L  
#define COND_ENABLE     1L
#define TURB_ENABLE       1L                                                                                                  // |                                                                                                  // |  
/*----------------------------------------------------------------------------------------------------------------------------------*/


// rele doble: https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/
// electrovalvula: https://www.taloselectronics.com/blogs/tutoriales/valvula-solenoide

#if RTC_ENABLE
#include "RTClib.h"
#endif

#if LORA_ENABLE
#include <SPI.h>           
#include <LoRa.h>
#endif

#if TEMP_ENABLE
//Librerias para sensor de temperatura DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#endif
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char i;
int x,aux4;
float aux1, aux2, aux3;

#if PH_ENABLE
 int decimalPrecision = 2;                   // decimal a mostrar en el Display & el Serial Monitor
float PH;
 const byte pHpin = A3;// el sensor se conecta al pin A3.        
// Constants:-


#endif



#if TEMP_ENABLE
float temperatura;  
 
  const int oneWirePin = A4;  //Pin digital 7A4 para sensor de temperatura 
OneWire oneWireBus(oneWirePin);
DallasTemperature sensor(&oneWireBus);
#endif

#if COND_ENABLE
float conductividad;  
#define cond A5
   
#endif

#if TURB_ENABLE
float turbidez; 
#define turb A0
   
#endif

#if RTC_ENABLE
// RTC_DS1307 rtc;

//    + 5V -> VCC
//    GND -> GND
//    SCL -> A5
//    SDA -> A4

RTC_DS3231 rtc; // Creacion del objeto RTC
String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre" };
#endif

#if LORA_ENABLE
// Modulo LoRa sx1278
const int nodo=102;
String outgoing;              // outgoing message
String Mymessage = "";
const int csPin = 10;          // LoRa radio chip select
const int resetPin = 9;        // LoRa radio reset
const int irqPin = 2;          // change for your board; must be a hardware interrupt pin
#endif

#if PRUEBAS_ENABLE

int PH = 7;
int temperatura = 23.0;
 
#endif


/*********************** PERIFERICOS *****************************/

#define PIN_LED             13
#define PIN_SPEAKER         3
#define SPEAKER_FRECUENCY   ( 220 * 1.059 )

void ledOn()
{
  analogWrite(PIN_LED, 255);
}

void ledOff()
{
  analogWrite(PIN_LED, 0);
}

void speakerOn()
{
  tone(PIN_SPEAKER,SPEAKER_FRECUENCY);
}

void speakerOff()
{
  noTone(PIN_SPEAKER); 
}

void sendMessage(String topic, String message)
{
  String request = "/" + topic + "/" + message;
  Serial.println(request);
}

/*********************** SETUP *****************************/

void setup() 
{
  // Setup Perifericos

  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);


  // Resto del Setup

  //delay(1000); 

#if LORA_ENABLE  
   LoRa.setSPIFrequency(4.0E6);
   LoRa.setPins(csPin, resetPin, irqPin);
   if (!LoRa.begin(433E6)) {       
      Serial.println("Falló inicialización de LoRa, comprobar conexiones");
      while (true);                       // if failed, do nothing
   }else{ Serial.println("LoRa inicializado");}
   LoRa.setSyncWord(0xF3);
#endif   
   
#if RTC_ENABLE  
   if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
   delay(200);
   // Si se ha perdido la corriente, fijar fecha y hora
   if (rtc.lostPower()) {
      // Fijar la fecha y hora de compilacion
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Esto inicializará el RTC con el tiempo que compila el boceto, obviamente usando la fecha y hora de la PC.
      
      // Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
      // rtc.adjust(DateTime(2016, 1, 21, 3, 0, 0));
   }
#endif

#if SENSORES_ENABLE   
 

  #if PH_ENABLE
   
  #endif

  
#endif  
}

#if RTC_ENABLE
void printDate(DateTime date)
{
   Serial.print(date.year(), DEC);
   Serial.print('/');
   Serial.print(date.month(), DEC);
   Serial.print('/');
   Serial.print(date.day(), DEC);
   Serial.print(" (");
   Serial.print(daysOfTheWeek[date.dayOfTheWeek()]);
   Serial.print(") ");
   Serial.print(date.hour(), DEC);
   Serial.print(':');
   Serial.print(date.minute(), DEC);
   Serial.print(':');
   Serial.print(date.second(), DEC);
   Serial.println();
}
#endif 

/*********************** LOOP *****************************/

void loop() 
{
#if RTC_ENABLE  
  // RTC: Obtener fecha actual y mostrar por Serial
   DateTime now = rtc.now();
   printDate(now);
#endif

#if SENSORES_ENABLE   
 
  #if TEMP_ENABLE
  //lectura de Temperatura
       sensor.requestTemperatures();
   sensor.getTempCByIndex(0);
   temperatura=sensor.getTempCByIndex(0);
   Serial.print(temperatura);
    Serial.println("°C");
     delay(100);   
  #endif
  
 
   
   #if PH_ENABLE
  // Lectura de PH
  PH = (1023 - analogRead(pHpin)) / 73.07; // fórmula para leer PH entre 0-14.
Serial.println(PH, decimalPrecision);// muestra el resultado en el serial monitor.
delay(1000);// espera un segundo por lectura.
   #endif

  #if COND_ENABLE
       
aux1=0;
for(i=0;i<100;i++)
{
aux1=aux1+((analogRead(cond)*5.00)/1023.00);
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

Serial.print(conductividad);
    Serial.println("uS/cm");
   #endif

     #if TURB_ENABLE
  // Lectura de turbidez
  delay(100);
aux3=0;
for(i=0;i<100;i++)
{
aux3=aux3+((analogRead(3)*5.00)/1023.00);
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
Serial.print(turbidez);
Serial.println(" NTU");
delay(1500);
   #endif
   
#endif

   #if LORA_ENABLE
   // Envio de los valores mediante LoRa
   delay(10);
   Mymessage = String(nodo)+ "/" + String(Temp,3) + "&" + String(PH)+"#"+String(Turbidez);  
   sendLoraMessage(Mymessage);
   delay(10);
   //Mymessage = " ";
   #endif

/* Con la porción de código que sigue se prueba el envio de datos entre modulos LoRa del NODO y GATEWAY enviando valores fijos.
   En condiciones normales de funcionamiento se desactiva esta parte del codigo con 0L en el macro*/
#if PRUEBAS_ENABLE
  delay(10);
  Mymessage = Mymessage + String(Temp) + "/" + String(PH)+ "&"+String(Turbidez)"\n";  
  sendLoraMessage(Mymessage);
  delay(100);
  Mymessage = "";
#endif

 //Esperar algunos segundos entre mediciones
   delay(500);
  
  comprobarPh();
  comprobarConductividad();
  comprobarTurbidez();
  comprobarTemperatura();
}


/*********************** AUTOMATAS *****************************/


void comprobarPh()
{
  if(PH < 6 || PH > 9)
  {
    speakerOn();
    ledOn();
    sendMessage(
      "alarmaPH",
      "Verter solución acida/alcalina para regular el ph"
    );
  }
  else
  {
    speakerOff();
    ledOff();
  }
}

void comprobarConductividad()
{

}

void comprobarTurbidez()
{
  
}

#define INITIAL_STATE         0       
#define NORMAL_TEMPERATURE    1
#define ALERT_TEMPERATURE     2
#define CRITICAL_TEMPERATURA  3

int TemperatureState = NORMAL_TEMPERATURE
void comprobarTemperatura() 
{
  switch(TemperatureState)
  {
    case NORMAL_TEMPERATURE :
      break;
    case ALERT_TEMPERATURE :
      break;
    case CRITICAL_TEMPERATURA :
      break;
  }
}

#if LORA_ENABLE
void sendLoraMessage(String outgoing) {
  LoRa.beginPacket();                    // start packet
  LoRa.print(outgoing);                  // add payload
  LoRa.endPacket(true);                      // finish packet and send it
}
#endif
