#include <Wire.h>
#include "RTClib.h"
 
//const int outputPin = LED_BUILTIN;
bool state = false;
 
// RTC_DS1307 rtc;
RTC_DS3231 rtc;
 String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
void setup() {
  // Serial.begin(9600);
   delay(1000);
 
   if (!rtc.begin()) {
   //   Serial.println(F("Couldn't find RTC"));
      while (1);
   }
 
   if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
  // digitalWrite(outputPin, LOW);
}
 
// Comprobar si esta programado el encendido
bool isScheduledON(DateTime date)
{
   int weekDay = date.dayOfTheWeek();
   float hours = date.hour() + date.minute() / 60.0;
 
   // De 09:30 a 11:30 y de 23:50 a 23:55
   bool hourCondition = (hours > 9.50 && hours < 11.50) || (hours > 23.83 && hours < 23.92);
 
   // Miercoles, Sabado o Domingo
   bool dayCondition = (weekDay == 3 || weekDay == 6 || weekDay == 0); 
   if (hourCondition && dayCondition)
   {
      return true;
   }
   return false;
}
 
void loop() {
   DateTime now = rtc.now();
  Serial.print(" (");
   Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
   Serial.print(") ");
   Serial.print(now.hour(), DEC);
   Serial.print(':');
   Serial.print(now.minute(), DEC);
   Serial.print(':');
   Serial.print(now.second(), DEC);
   Serial.println();
   if (state == false && isScheduledON(now))      // Apagado y debería estar encendido
   {
   //   digitalWrite(outputPin, HIGH);
      state = true;
      Serial.print("Activado");
   }
   else if (state == true && !isScheduledON(now))  // Encendido y deberia estar apagado
   {
   //   digitalWrite(outputPin, LOW);
      state = false;
      Serial.print("Desactivar");
   }
 
   delay(3000);
}
