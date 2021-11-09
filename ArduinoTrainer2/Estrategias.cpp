/*
    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0
    
    Motor Driver L9110
    Alimentacion:   5V
   
    Modulo:   Estrategias.cpp

        Funciones:
            void Redil( void );
            void Walk_Test(void);
            void Hasta_que_lleguesa( int );

    ToDo:
          
*/

#include "ArduinoTrainer.h"

extern TrainerBot miTrainerBot;
//#define HORIZONTE           300

/*
    Funcion:  Redil()
        
      Programa simple que ilustra una estrategia simple

      Es preciso hacer un camino cerrado con cinta aislante de color negro
      Situamos a TrainerBot en el interior del perimetro
      TrainerBot retrocede al detectar la cinta negra
      TrainerBot queda recluido dentro del redil

      Funcionamiento:
      
        1)    Lanzamos un pulso de señal cuadrado. Para ello el pin TRIGGER 
                a) Lo ponemos a LOW, y esperamos un tiempo a que se estabilice ( por si estaba en nivel HIGH )
                b) Lo ponemos a HIGH, y esperamos un tiempo no inferior a 30 msg
                c) Lo ponemos a LOW again
        2)  El sensor devuelve un pulso de entrada en el pin ECHO, que es el tiempo de ida y vuelta del sonido
  
        3)  Con una formula lo convertimos a cm.


 */
void Redil( void )
{
  int situacion;

  for(;;)
  {
      situacion = IRSituaTrainer();
      delay(100);
    //  Serial.print("Situacion");
    //  Serial.println(situacion);
  
      switch (situacion)
      {
        case 15:
          //  Cuatro sensores leen negro
          for(int i=0;i<5;i++)
            LedParpadea( LED_ROJO , 150 , 150 );
          Patras_pasos( miTrainerBot.numPasos );
          delay(100);
          MediavueltaLeft_pasos( 2*miTrainerBot.numPasos );
        break;
    
        case 0:
            //  Cuatro sensores leen blanco
            LedParpadea( LED_VERDE , 50 , 50 );
            Palante_pasos( miTrainerBot.numPasos );
            delay(100);
         break;
    
        case 1:
        case 2:
        case 3:
             //  Dos sensores izqudos leen blanco
             LedParpadea( LED_AMARILLO , 150 , 150 );
             Patras_pasos( 3*miTrainerBot.numPasos );
             delay(100);            
             MediavueltaRight_pasos( 4*miTrainerBot.numPasos );
        break;

        case 4:
        case 5:
        case 6:
        case 7:
                //  Tres sensores izqudos leen blanco
          LedParpadea( LED_AMARILLO , 150 , 150 );
          Patras_pasos( 3*miTrainerBot.numPasos );
          delay(100);
          MediavueltaRight_pasos( 3*miTrainerBot.numPasos );
       break;


        case 8:
           //  Dos sensores derechos leen blanco
          LedParpadea( LED_AMARILLO , 150 , 150 );
          Patras_pasos( 3*miTrainerBot.numPasos );
          delay(100);
          MediavueltaLeft_pasos( 4*miTrainerBot.numPasos );
       break;
        
        case 12:
           //  Dos sensores derechos leen blanco
          LedParpadea( LED_AMARILLO , 150 , 150 );
          Patras_pasos( 3*miTrainerBot.numPasos );
          delay(100);
          MediavueltaLeft_pasos( 3*miTrainerBot.numPasos );
       break;
      }   
      delay(500);
  }
  
}




void Walk_Test( void )
{
  int i;

  for( i=0 ;i<5 ; i++ )
    LedParpadea( LED_AMARILLO , 250 , 250 );
  
  delay(1000);  
  
  Palante();
  Hasta_que_lleguesa(25);
  
  Stop();
  
  for( i=0 ;i<10 ; i++ )
    LedParpadea( LED_ROJO , 50 , 50 );
  delay(500);
}





void Hasta_que_lleguesa( int horizonte)
{
  int distancia=-1000;
  do
  {
    distancia = USLeeDistancia();
  } 
  while( distancia >= horizonte );
}
