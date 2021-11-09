/*
    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0

    Motor Driver L9110
    Alimentacion:   5V


  Modulo: Tests.cpp

  Notas 1:  Test diversos del hardware
            Estos test sirven como ejemplos de uso de las
            funciones Primitivas

            Incluyen algunas técnicas básicas de programacion
            Cada uno de estos tests puede incluirse en loop()
            y constituyen un curso rápido de C
  Funciones:

    void Led_Test(void)
    void Switch_Test(void)
    void Distance_Test(void)
    void Motor_Test(void)
    void LineSensor_Test( void )
    void Motor_PWM_Test(void)

*/

#include "ArduinoTrainer.h"




extern TrainerBot miTrainerBot;


//    Macros de preprocesador solo empleadas en este modulo
#define LED_DELAY   500
#define ENCENDIDO   255
#define APAGADO       0


/*

    Led_Test()

    Proposito:
        a)  Enciende alternativamente los LEDs
        b)  Hace sonar el buzzer como un despertador
        c)  Hace un pitido
*/
void Led_Test(void)
{
   int i,repite;

   // Enciende y apaga los LED
   LedRojo( ENCENDIDO );
   delay( LED_DELAY );
   LedRojo( APAGADO );
   delay( LED_DELAY );

   LedAmarillo( ENCENDIDO );
   delay( LED_DELAY );
   LedAmarillo( APAGADO );
   delay( LED_DELAY );

   LedVerde( ENCENDIDO );
   delay( LED_DELAY );
   LedVerde( APAGADO );
   delay( LED_DELAY );

   //   Hacer parpadear los LED
   for( i=0;i<5;i++)
    LedParpadea( LED_ROJO , 100 , 50 );

  delay( 500 );

  for( i=0;i<5;i++)
    LedParpadea( LED_AMARILLO , 100 , 50 );
  delay( 500 );

  for( i=0;i<5;i++)
    LedParpadea( LED_VERDE , 100 , 50 );
  delay( 500 );

  //  Hace zumbar el buzzer aumentando el volumen
  for( repite =0 ; repite < 4 ; repite++)
  {
    for ( i=0;i<4 ; i++ )
    {
      analogWrite( BUZZER ,  2*(5*repite+1));
      delay( 100 );
      analogWrite( BUZZER , LOW );
      delay( 50 );
    }
    delay(500 );
  }
  delay(1000);

  Pita();
}





/*

    Switch_Test(void)

    Proposito:
        a)  Al pulsar el pulsador D12 , cambia el parpadeo del LED_ROJO y LED_AMARILLO
        a)  Al pulsar el pulsador D13 , cambia el parpadeo del LED_ROJO y LED_AMARILLO

*/
void Switch_Test(void)
{
  int ledrojo = 0;
  for(;;)
  {
    if( Switchd12_esta_pulsado() && Switchd13_esta_pulsado()    )
    {
      Pita();
      LedRojo( APAGADO  );
      LedAmarillo( APAGADO );
      LedVerde( APAGADO );
      return;
    }



    if( !ledrojo )
    {
      LedVerde( APAGADO );
      if( Switchd12_esta_pulsado() )
        LedParpadea( LED_AMARILLO , 100 , 100 );
      else
        LedParpadea( LED_ROJO , 25 , 100 );
    }

    if( Switchd13_esta_pulsado() )
    {
      ledrojo = 1;
      LedRojo( APAGADO );
      LedVerde( ENCENDIDO );
    }
    else
      ledrojo=0;
  }

}





/*

    Distance_Test(void)

    Proposito:
        a)  Llama a la funcion Primitiva Distance_StandardTest()
        b)  Imprime por Monitor Serie la distancia
        c)  Enciende el LED Rojo Amarillo o Verde segun la distancis

*/
void Distance_Test(void)
{

  for(;;)
  {
    miTrainerBot.distancia = USLeeDistancia();
    //USImprimeDistancia( MM );
    delay(100);                                          //Limite 25 msg Va ok
    if( miTrainerBot.distancia < 50 )
    {
      Pita();
      LedRojo( APAGADO  );
      LedAmarillo( APAGADO );
      LedVerde( APAGADO );
      return;
    }
        else if( miTrainerBot.distancia < 100 )
    {
      LedRojo( ENCENDIDO );
      LedAmarillo( APAGADO );
      LedVerde( APAGADO );
    }
    else if( miTrainerBot.distancia < 150 )
    {
      LedRojo( ENCENDIDO  );
      LedAmarillo( ENCENDIDO );
      LedVerde( APAGADO );
    }
        else if( miTrainerBot.distancia < 200 )
    {
      LedRojo( APAGADO  );
      LedAmarillo( ENCENDIDO );
      LedVerde( APAGADO );
    }
    else if( miTrainerBot.distancia < 250 )
    {
      LedRojo( APAGADO  );
      LedAmarillo( ENCENDIDO );
      LedVerde( ENCENDIDO );
    }
    else
    {
      LedRojo( APAGADO  );
      LedAmarillo( APAGADO );
      LedVerde( ENCENDIDO );
    }

  }
}





/*

    Motor_Test(void)

    Proposito:
        a)  Llama a la funciones Primitiva de motor
        b)  La secuencia de giro es
              Notor   IZDO    Adelante
                      IZDO    Atras
                      DCHO    Adelante
                      DCHO    Atras
                      IZDO y DCHO Adelante
                      IZDO y DCHO Atras
                      IZDO Adelante y DCHO Atras
                      IZDO Atras    y DCHO Adelante

    Notas 1:    Esta funcion es fundamental para ajustar los motores
                El cableado de los motores debe ser de modo que
                la secuencia de giro sea la de arriba

                El cableado del modulo L9110 de cada motor es

                Motor A   {  D7 , D9 }
                Motor B   {  D8 , 10 }

                Asi pues en el PCB de Arduino Trainer los cables
                del driver L9110 se van alternando en el conector
                y no van los dos de un motor juntos en el conector

                Para ello basta con intercambiar los cables
                del conector del PCB si fuera erronea

     Notas 2:   La orientacion de los motores es visto en planta ( desde arriba )
                Hay que mirar TrainerBot desde arriba, con el sensor HCSr04
                en la posicion 12:00 horas de un reloj
*/
void Motor_Test(void)
{
  Pita();
  delay(1000);
  //    Motor Izquierdo
  Forward_Motor_Left();
  delay(1000);
  Stop_Motor_Left();
  delay(500);

  Reverse_Motor_Left();
  delay(1000);
  Stop_Motor_Left();
  delay(500);

  //    Motor Derecho
  Forward_Motor_Right();
  delay(1000);
  Stop_Motor_Right();
  delay(500);

  Reverse_Motor_Right();
  delay(1000);
  Stop_Motor_Right();
  delay(500);

  //    Motor Izquierdo y Derecho Adelante
  Palante();
  delay(1000);
  Stop();
  delay(500);

  //    Motor Izquierdo y Derecho Atras
  Patras();
  delay(1000);
  Stop();
  delay(500);

  //    Motor Izquierdo Adelante y Motor Derecho Atras
  Mediavuelta_Left();
  delay(1000);
  Stop();
  delay(500);

  //    Motor Izquierdo Atras y Motor Derecho Adelante
  Mediavuelta_Right();
  delay(1000);
  Stop();
  delay(500);

  BipBip();
}




/*
    LineSensor_Test(void)

    Proposito:
        a)  Lee el Sensor de Linea
        b)  Imprime por Monitor Serie los valores

*/
void LineSensor_Test( void )
{
  for(;;)
  {
    IRLeeSensor();
    IRImprimeSensor();
  }
}




/*

    Motor_PWMTest(void)

    Proposito:
        a)  Avanza adelante a velocidad variable
        b)  Retrocede igualmente
*/
void Motor_PWM_Test(void)
{
  int speed;
  for( speed=150 ; speed < 255 ; speed+=10)
  {
    MotorDerecho( speed );
    MotorIzquierdo( speed );

    Palante();
    delay(1000);
    LedParpadea( LED_VERDE , 50 , 50 );
  }

  for( speed=150 ; speed < 255 ; speed+=10)
  {
    MotorDerecho( speed );
    MotorIzquierdo( speed );

    Patras();
    delay(1000);
    LedParpadea( LED_ROJO , 50 , 50 );
  }
  Stop();
}
