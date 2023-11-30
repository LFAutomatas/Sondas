

int pinLedR = 13; // pin Rojo del LED 

int pausa = 1000;

void setup()
{
pinMode(pinLedR, OUTPUT); // pone el pinLedR como output

 Serial.begin(9600);
   delay(1000); 
 
 
}

void loop()
{
analogWrite(pinLedR, 255); //encendido
delay(1000);
analogWrite(pinLedR, 0); //apagado

}
