/***********************/
/* recorrido de octava */
/***********************/

int pinaltavoz = 3;
int frecuencia=220;    // frecuencia correspondiente a la nota La
int contador;          // variable para el contador
float m=1.059;         // constante para multiplicar frecuencias

void setup()
{
}

void loop()
{
    for(contador=0,frecuencia=220;contador<12;contador++)
    {
        frecuencia=frecuencia*m;     // actualiza la frecuencia
        tone(pinaltavoz,frecuencia); // emite el tono
        delay(1500);                 // lo mantiene 1.5 segundos
        noTone(pinaltavoz);          // para el tono
        delay(500);                  // espera medio segundo
    }
}
