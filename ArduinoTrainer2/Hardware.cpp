/*
    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0

    Motor Driver L9110
    Alimentacion:   5V

    Modulo:   Hardware.cpp

    Notas 1:  Interface con hardware
              Incluye las funciones que controlan la electronica de Arduino
              Se incluyen funciones primitivas ( que controlan los dispositivos
              de Trainer v2.0 ) para el siguiente hardware

                  LEDs
                  HCSR-04
                  Sensor IR
                  Buzzer
                  Driver de motor L9110

              Estas son las funciones a modificar en el caso de tener
              otro tipo de hardware, por ejemplo servos de rotacion continua


    Notas 1:  Si consideramos un paradigma OOP, estas funciones, al ser las de bajo nivel
              deberian estar restringidas a la interfaz

              De este modo podemos simpliicar el API
              ( aun a costa de perder funcionalidad )

    Funciones:

             void Stop_Motor_Left( void )
             void Stop_Motor_Right( void )
             void Forward_Motor_Left( void )
             void Forward_Motor_Right( void )
             void Reverse_Motor_Left( void )
             void Reverse_Motor_Right( void )
             void MotorDerecho( int velocidad )
             void MotorIzquierdo( int velocidad )


             int Distance_StandardTest(void)


             void IRLeeSensor( void )
             void IRImprimeSensor( void )


             void Pita(void)
             void Beep( int frec , int duracion )
             void BipBip( void )
             void Bipveces( in n )

             void LedParpadea( int led , int tiempo_ON , int tiempo_OFF )
             void LedRojo( int color )
             void LedAmarillo( int color )
             void LedVerde( int color )


             int Switchd12_esta_pulsado(void)
             int Switchd13_esta_pulsado(void)

*/

#include "ArduinoTrainer.h"
extern TrainerBot miTrainerBot;





/****************

      Hardware: Driver de motor L9110
      Pines:    ( D7 , D8 , D9 , D10 )

      Ctes:     ( MOTOR_DCHO_DIR , MOTOR_DCHO_SPD )
                ( MOTOR_IZDO_DIR ,  MOTOR_IZDO_SPD );

 ****************/

void Stop_Motor_Left( void )
{
  digitalWrite( MOTOR_IZDO_DIR , LOW );
  digitalWrite( MOTOR_IZDO_SPD , LOW );
}



void Stop_Motor_Right( void )
{
  digitalWrite( MOTOR_DCHO_DIR , LOW );
  digitalWrite( MOTOR_DCHO_SPD , LOW );
}



void Forward_Motor_Left( void )
{
  digitalWrite( MOTOR_IZDO_DIR, HIGH );
  analogWrite( MOTOR_IZDO_SPD, 255-miTrainerBot.velocidadMotorIzquierdo );
}



void Forward_Motor_Right( void )
{
  digitalWrite( MOTOR_DCHO_DIR, HIGH );
  analogWrite( MOTOR_DCHO_SPD, 255-miTrainerBot.velocidadMotorDerecho );
}



void Reverse_Motor_Left( void )
{
  digitalWrite( MOTOR_IZDO_DIR, LOW );
  analogWrite( MOTOR_IZDO_SPD, miTrainerBot.velocidadMotorIzquierdo );
}




void Reverse_Motor_Right( void )
{
  digitalWrite( MOTOR_DCHO_DIR, LOW );
  analogWrite( MOTOR_DCHO_SPD, miTrainerBot.velocidadMotorDerecho );
}



void MotorDerecho( int velocidad )
{
  miTrainerBot.velocidadMotorDerecho = velocidad;
}



void MotorIzquierdo( int velocidad )
{
  miTrainerBot.velocidadMotorIzquierdo = velocidad;
}



/****************

      Hardware: Sensor US HC-SR04
      Pines:  ( D2 , D4 )

      Ctes:   ( HCSR04_TRIGGER , HCSR04_ECHO )

 ****************/

/*
    Funcion:  void USLeeDistancia( void )

      Devuelve en MILIMETROS la distancia del sensor HCSR04 al objeto más cercano

      Funcionamiento:

        1)    Lanzamos un pulso de señal cuadrado. Para ello el pin TRIGGER
                a) Lo ponemos a LOW, y esperamos un tiempo a que se estabilice ( por si estaba en nivel HIGH )
                b) Lo ponemos a HIGH, y esperamos un tiempo T = 10 msg
                c) Lo ponemos a LOW again
        2)  El sensor devuelve un pulso de entrada en el pin ECHO, que es el tiempo de ida y vuelta del sonido

        3)  Con una formula lo convertimos a MILIMETROS

        4)  El horizonte de pulseIn corresponde a 38 milisegundos  -38000 microsg - segun geeekfactory.mx

        5)  Con el horizonte se devuelve cero cuando mido delante de una cortina , que absorbe el sonido
            Nadie ha hablado de esto en la Web que yo sepa
*/
int USLeeDistancia( void )
{
  long duracion;
  float distancia;

  //  Pulso en TRIGGER
  digitalWrite(HCSR04_TRIGGER , LOW);
  delayMicroseconds(5);
  digitalWrite(HCSR04_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(HCSR04_TRIGGER, LOW);


  //  Pulso de ECHO
  duracion = pulseIn(HCSR04_ECHO , HIGH ) ;

  //  Conversion a float ...
  distancia = (duracion /  5.84 ) ;
  //distancia = int(0.017 * duracion);
  delay(100);
  return (int )distancia;
}


void USImprimeDistancia( int factor )
{
  switch ( factor )
  {
    case( MM ):
      Serial.println( "Distancia .. "+ String(miTrainerBot.distancia) + "mm.") ;
      break;
    case CM :
      Serial.println( "Distancia .. "+ String( int( (miTrainerBot.distancia+5)/10) ) + " cm") ;
      break;
  }
}



/****************

      Hardware: Sensor Linea
      Pines: ( A0 , A1 , A2 , A3 )

 ****************/

void IRLeeSensor( void )
{
  miTrainerBot.IRsensor[0]= analogRead( A0 );delay(5);
  miTrainerBot.IRsensor[1]= analogRead( A1 );delay(5);
  miTrainerBot.IRsensor[2]= analogRead( A2 );delay(5);
  miTrainerBot.IRsensor[3]= analogRead( A3 );delay(5);
}




void IRImprimeSensor( void )
{
  int ind;
  //Serial.print("Lecturas ...");

  for( ind =0; ind <4 ; ind++)
  {
      Serial.print(" "+ String( miTrainerBot.IRsensor[ind] ) );
      delay(10);
  }
  Serial.print("\n");
  delay(10);
}







/****************

      Hardware: BUZZER
      Pines: ( D11 )

      Ctes:     ( BUZZER )

  Funciones:
      void Pita(void)
      void Beep( int frec , int duracion )
      void BipBip( void )
      void Bipveces( in n )

 ****************/

void Pita(void)
{
    tone( BUZZER , 1440);
    delay(1000);
    noTone( BUZZER );
}



void Beep( int frec , int duracion )
{
    tone( BUZZER , frec , duracion );
    delay( duracion );
    noTone( BUZZER );
}


void BipBip( void )
{
    tone( BUZZER , 440 );
    delay(50);
    noTone( BUZZER );
    delay( 100 );

    tone( BUZZER , 440 );
    delay(50);
    noTone( BUZZER );
}


void Bipveces( int n )
{
  int i;
  for ( i = 0 ; i< n ; i++ )
  {
    tone( BUZZER , 440 );
    delay(50);
    noTone( BUZZER );
    delay( 100 );
  }
}




/****************

      Hardware: LEDS
      Pines:    ( D3 , D5 , D6 )

 ****************/

/*
    Led_Parpadea()

      Hace parpadear el LED mediante 2 parametros

*/
void LedParpadea( int led , int tiempo_ON , int tiempo_OFF )
{
   digitalWrite( led , HIGH );
   delay( tiempo_ON );
   if( tiempo_OFF )
   {
      digitalWrite( led , LOW );
      delay(tiempo_OFF );
   }
}



void LedRojo( int color )
{
  analogWrite( LED_ROJO , color );
}



void LedAmarillo( int color )
{
  analogWrite( LED_AMARILLO, color );
}



void LedVerde( int color )
{
  analogWrite( LED_VERDE , color );
}





/****************

      Hardware: SWITCHES
      Pines:    ( D12 , D13 )

 ****************/

/*
    Funcion:  Switch_esta_pulsado(void)

      Devuelve 1 si el pulsador esta siendo presionado, 0 si no
*/

int Switchd12_esta_pulsado(void)
{
  return !digitalRead( SWITCH_D12 );
}





/*
    Funcion:  Switch_esta_pulsado(void)

      Devuelve 1 si el pulsador esta siendo presionado, 0 si no
*/

int Switchd13_esta_pulsado(void)
{
  return !digitalRead( SWITCH_D13 );
}
