#include <Keypad.h>
#include <LiquidCrystal.h> // Libreria para que funcione el LCD
LiquidCrystal lcd(2, 0, A1, A2, 10, 9); // RS=2 , E=0, A1=D4, A2=D5, 10=D6, 9= D7 esta linea muestra en que pines debe ir conectado la pantalla LCD a nuestro Arduino

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'#','0','*'}
};
  byte rowPins[ROWS] = {12,11,8,7}; //Filas(pines del 7,8 y 12, 13)
byte colPins[COLS] = {6,5,4}; //Columnas (pines del 4 al 6)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//int led = 13;
////////////////////////////////////////////////////////////////////VOID SETUP
void setup(){

lcd.begin(16, 2); // Con esta instrucción indicamos cual es la proporción de nuestro LCD
lcd.print("LFyA-Ingenieria-"); // Una instrucción muy importante ya que con esta imprimiremos el texto en nuestra pantalla


}
////////////////////////////////////////////////////////////////////VOID LOOP
void loop(){
char key = keypad.getKey();
/////////////////////////////////////////Boton A
if(key) {
switch (key)
{
case '*'://Cuando key "B" es oprimida... 
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:*"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD         


break;
case '#'://Cuando key "B" es oprimida...   
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:#"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD       

break;
}
}

/////////////////////////////////////////Números del 0 al 9
if(key) {
switch (key)
{
case '1':  
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:1"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD      
//Serial.println("1");
break;
case '2':   
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:2"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD     
break;
case '3':    
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:3"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD    

break;
case '4':     
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:4"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD   

break;
case '5':   
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:5"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD     

break;
case '6':    
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:6"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD    

break;
case '7':   
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:7"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD     

break;
case '8':
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:8"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD

break;
case '9':     
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:9"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD   

break;
case '0': 
lcd.setCursor(0, 1); // con esta linea damos a entender que la primera fila de nuestro LCd ya esta siendo usada por lo cual queremos usar la segunda
lcd.print("tecla:0"); // Al ser colocadar debajo de la instrucción anterior, este mensaje se mostrara en la segunda fila del LCD       

break;
}
}

///...
}
//Mas información en CDM
