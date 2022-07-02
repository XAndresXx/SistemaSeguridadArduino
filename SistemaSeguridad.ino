/* @file SistemaSeguridad.pde
|| @version 1.0
|| @author Andres Felipe Ocampo
|| @author Michael Stevens Diaz Beltran
||
|| @description
|| | Demostracion de un sistema de seguridad.
|| #
*/
#include <LiquidCrystal.h>
#include <Keypad.h>

#define ROJO 36
#define VERDE 34
#define  AZUL 32

LiquidCrystal lcd(0, 1, 5, 4, 3, 2);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
char claveCorrecta[8] ="1234567";
char claveIngreso[8];

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int pos = 0;
int contaError = 0;

void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ingrese clave :");
  delay(2000);
  pinMode(ROJO,OUTPUT);
  pinMode(AZUL,OUTPUT);
  pinMode(VERDE,OUTPUT);
}
  
void loop(){
  char key = keypad.getKey();
  claveIngreso[pos] = key;
   
  if (key){
    lcd.setCursor(pos++, 1);
    lcd.println("*               ");
    
  }
  if(pos == 7){
      pos = 0;
      if(comprobarContra()==1){
          //Prender led verde
          LED_RGB(0,255,0);
          ImprimirMensaje("Clave Correcta");
          delay(2000);
          LED_RGB(0,255,0);
          delay(1000);
          LED_RGB(0,0,255);
          delay(1000);
          LED_RGB(255,0,0);
          delay(1000);
          LED_RGB(0,0,0);
          ImprimirMensaje("                ");
          }else{
            //Prender led amarillo
            LED_RGB(0,0,255);
            ImprimirMensaje("Clave Incorrecta");
          delay(2000);  
          ImprimirMensaje("                ");
          LED_RGB(0,0,0);
            contaError++;
          }
       
    }
    if(contaError == 3){
      //Activar led rojo y esperar 10 seg
      //Despues reiniciar
      LED_RGB(255,0,0);
      ImprimirMensaje("Block System");
      delay(10000);//se bloquea por 10 segundos
      contaError=0;
      ImprimirMensaje("                ");
      LED_RGB(0,0,0);
    }
  
}

void ImprimirMensaje(String mensaje){
  lcd.setCursor(0, 1);
  lcd.print(mensaje);
}

int comprobarContra(){
  int contaOk = 0;
  for(int i=0; i < 7; i++)
    if(claveIngreso[i]==claveCorrecta[i])    
        contaOk++;
   
  if(contaOk == 7)
    return 1;
   return 0;
    
}
void LED_RGB(int r,int g,int b){
  analogWrite(ROJO,r);
  analogWrite(VERDE,g);
  analogWrite(AZUL,b);
}
