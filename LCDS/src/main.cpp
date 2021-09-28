//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015 - Electrónica Digital 2
// Pablo Mazariegos
// Ejemplo de uso de LCD en 4 bits
//*****************************************************************************

//*****************************************************************************
// Librerías
//*****************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h>
//#include "LCD4bits.h"
//*****************************************************************************
// Definición de pines
//*****************************************************************************
#define d4 3
#define d5 1
#define d6 22
#define d7 23
#define en 16
#define rs 0

#define pot1 36
#define pot2 26

#define Boton1 14
#define Boton2 12

#define led1 25 //verde
#define led2 13 //rojo
//*****************************************************************************
// Prototipos de función
//*****************************************************************************
void separarvariables1(void);
void separarvariables2(void);
void contBitsSuma(void);
//void contBitsResta(void);
//*****************************************************************************
// Variables Globales
//*****************************************************************************
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
uint8_t decenas, unidades, decimal;
int adcRaw;
float voltaje1;
int volt1;
float voltaje2;
int volt2;

//Instanciar timer
hw_timer_t *timer = NULL;
//variable para el contador del timer
int ISRB1 = 0;
int ISRB2 = 0;
int contadorDisplay = 7;

//*****************************************************************************
//ISR
//*****************************************************************************


//interrupcion para el boton1
void IRAM_ATTR boton1()
{
  ISRB1 = 1;
}

//interrupcion para el boton2
void IRAM_ATTR boton2()
{
  ISRB2 = 1;
}
//*****************************************************************************
// Configuración
//*****************************************************************************

void setup() {
  //leds
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
  //boton1
  //pinMode(Boton1, INPUT_PULLUP);
  attachInterrupt(Boton1, boton1, RISING);

  //boton2
  //pinMode(Boton2, INPUT_PULLUP);
  attachInterrupt(Boton2, boton2, RISING);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Pot1:");
  lcd.setCursor(6, 0);
  lcd.print("Pot2:");
  lcd.setCursor(12, 0);
  lcd.print("CPU");
}

void loop() {
  contBitsSuma();
  //contBitsResta();
  separarvariables1();
  separarvariables2();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(voltaje1);

  lcd.setCursor(6, 1);
  // print the number of seconds since reset:
  lcd.print(voltaje2);

   lcd.setCursor(12, 1);
  // print the number of seconds since reset:
  lcd.print(contadorDisplay);
}

void separarvariables1(){
  voltaje1 = analogReadMilliVolts(pot1)/1000.0 ;
  int temp = voltaje1;
  decenas = temp / 100.0;
  temp = temp - decenas *100.0;
  unidades = temp / 10.0;
  temp = temp - unidades *10.0;
  decimal = temp;
  volt1 = decenas + unidades + decimal;
}

void separarvariables2(){
  voltaje2 = analogReadMilliVolts(pot2)/1000.0;
  int temp = voltaje2;
  decenas = temp / 100.0;
  temp = temp - decenas *100.0;
  unidades = temp / 10.0;
  temp = temp - unidades *10.0;
  decimal = temp;
  volt2 = decenas + unidades + decimal;
}

void contBitsSuma(){
  if (ISRB1 == 1 && contadorDisplay < 255){
    contadorDisplay = contadorDisplay + 1 ;
    digitalWrite(led1, 1);
   ISRB1 = 0;
  }

  if (ISRB1 == 1 && contadorDisplay == 255){
    contadorDisplay = 255 ;
    digitalWrite(led1, 1);
    ISRB1 = 0;
  }

  if (ISRB2 > 0 && contadorDisplay > 0){
    contadorDisplay = contadorDisplay - 1 ;
     digitalWrite(led2, 1);
     ISRB2 = 0;
  }
  if (ISRB2 == 1 && contadorDisplay == 0){
    contadorDisplay = 0 ;
     digitalWrite(led2, 1);
     ISRB2 = 0;
    
  }
  
}
/*
void contBitsResta(){
  if (ISRB2 == 1 && contadorDisplay > 0){
    contadorDisplay = contadorDisplay - 1 ;
     digitalWrite(led2, 1);
     ISRB2 = 0;
  }
  if (ISRB2 == 1 && contadorDisplay == 0){
    contadorDisplay = 0 ;
     digitalWrite(led2, 1);
     ISRB2 = 0;
    
  }
  
}*/