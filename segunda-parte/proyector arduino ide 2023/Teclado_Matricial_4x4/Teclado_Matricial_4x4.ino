/*ElectroCrea.com

Instrucciones:
--------------------------------------
Conecte los pines 1-8 del KeyPad a los pines 9-2 de Arduino
Conecte un led al pin 13 de Arduino
Recuerda descargar la libreria Keypad
*/

#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'0','E','F','D'}
};
byte rowPins[ROWS] = {12,11,8,7}; //Filas(pines del 7,8 y 12, 13)
byte colPins[COLS] = {6,5,4,2}; //Columnas (pines del 2, 4 al 6)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//int led = 13;
////////////////////////////////////////////////////////////////////VOID SETUP
void setup(){
Serial.begin (9600);
//pinMode(led, OUTPUT);
}
////////////////////////////////////////////////////////////////////VOID LOOP
void loop(){
char key = keypad.getKey();
/////////////////////////////////////////Boton A
if(key) {
switch (key)
{
case 'A'://Cuando key "A" es oprimida...          
Serial.println("A");//El monitor serial escribe "ElectroCrea.com"
//digitalWrite(led, HIGH);//El led se enciende
break;
case 'B'://Cuando key "B" es oprimida...          
Serial.println("B");//El monitor serial escribe "Visítanos"
//digitalWrite(led, LOW);//El led se apaga
break;
case 'C'://Cuando key "B" es oprimida...          
Serial.println("c");//El monitor serial escribe "Visítanos"
//digitalWrite(led, LOW);//El led se apaga
break;
case 'D'://Cuando key "B" es oprimida...          
Serial.println("D");//El monitor serial escribe "Visítanos"
//digitalWrite(led, LOW);//El led se apaga
break;
case 'E'://Cuando key "B" es oprimida...          
Serial.println("E");//El monitor serial escribe "Visítanos"
//digitalWrite(led, LOW);//El led se apaga
break;
case 'F'://Cuando key "B" es oprimida...          
Serial.println("F");//El monitor serial escribe "Visítanos"
//digitalWrite(led, LOW);//El led se apaga
break;
}
}

/////////////////////////////////////////Números del 0 al 9
if(key) {
switch (key)
{
case '1':        
Serial.println("1");
break;
case '2':        
Serial.println("2");
break;
case '3':        
Serial.println("3");
break;
case '4':        
Serial.println("4");
break;
case '5':        
Serial.println("5");
break;
case '6':        
Serial.println("6");
break;
case '7':        
Serial.println("7");
break;
case '8':        
Serial.println("8");
break;
case '9':        
Serial.println("9");
break;
case '0':        
Serial.println("0");
break;
}
}

///...
}
//Mas información en CDM
