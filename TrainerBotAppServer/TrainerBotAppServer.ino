/*
    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0

    Motor Driver L9110
    Alimentacion:   5V

    Modulo:   ArduinoTrainerv2.0-Abril2019.ino

        Funciones:
            loop()
            setup()
            SetupTrainerBot( void )
            ImprimeTrainerBot()

      ToDO:
          1)  Valores IRsmin[] , smax[]  -->Inicializarlos
          2)  ImprimeTrainerBot         --> Revisar campos
*/

#include "ArduinoTrainer.h"

#define BUFFER_LEN 100              //    Buffer Serie
#define BUFFER_MAXLEN 5             //    Longitud del mensaje enviado por App Inventor



/*

      Variables globales

*/
TrainerBot miTrainerBot ;               //    Clase definida en ArduinoTrainer.h


/**************************************************************************************

      Programa Principal

*/

/*
      Funcion: setup()
          Normalmente esto no hay que tocarlo
 */
void setup()
{
  pinMode( LED_ROJO , OUTPUT );
  pinMode( LED_AMARILLO , OUTPUT );
  pinMode( LED_VERDE , OUTPUT );

  pinMode(HCSR04_TRIGGER , OUTPUT);
  pinMode(HCSR04_ECHO , INPUT);

  pinMode( MOTOR_IZDO_DIR , OUTPUT );
  pinMode( MOTOR_IZDO_SPD , OUTPUT );
  pinMode( MOTOR_DCHO_DIR , OUTPUT );
  pinMode( MOTOR_DCHO_SPD , OUTPUT );

  pinMode( BUZZER , OUTPUT );

  //    Para motores
  Stop();

  //  Activa los pulsadores ( D12 D13 ) como entrada.
  //    Activa la resistencia pull up integrada en chip ATMEGA328
  pinMode( SWITCH_D12 , INPUT_PULLUP );
  pinMode( SWITCH_D13 , INPUT_PULLUP );

  // pinMode( SWITCH_D12 , INPUT );         //  Las lineas anteriores son similares a estas dos lineas
  //digitalWrite(SWITCH_D12 , HIGH);

  //  Espera a que se pulse el boton D12
  while( !Switchd12_esta_pulsado() )
      LedParpadea( LED_VERDE , 250 , 250 );
  delay(500);
  //  Inicia Puerto Serie
  Serial.begin( 9600 );                   //    9600 es obligado para el modulo AppServer()
  //while( Serial.available()>0 )
    //Serial.read();

   SetupTrainerBot();                     //    Simula el constructor de C++ ( Situada al final de este modulo )
}



/*
    Funcion: loop()

    Notas 1:  Las lineas comentadas en loop() son funcionales

 */
void loop()
{

  AppServer( );

  //  Motor_Test();
  //Led_Test();
  //Switch_Test();
  //Distance_Test() ;
  //LineSensor_Test( );
  //Motor_Test();

  //IRSituaTrainer( );
  //Situacion();


  //Redil(  );
  //Walk_Test();
  //PARA

}



/*

      Fin del Programa Principal

**************************************************************************************/





/*
      Constructor de la clase

      Nota 1:   Esto es una simulacion de un metodo de clase
                (
                  La clase TrainerBot no necesita esto, ya que en C++
                  una struct es una clase con todos sus miembros publicos
                  y TrainerBot es un tipo de datos agregado struct
                  definido en TrainerBot.h
                )
                Este codigo simula iniciar una estructura usando ANSI C


      Nota 2:   Por otra parte muestra parte de la biblioteca de funciones del programa
                El conjunto total de prototipos de funcion se encentra en ArduinoTrainer.h
                y constituye el API de la  clase TrainerBot


      Nota 3:   La funcion se llama desde la funcion setup()
*/
void SetupTrainerBot( void )
{
  miTrainerBot.medicion     =1;

  miTrainerBot.ledRojo      =00;
  miTrainerBot.ledAmarillo  =00;
  miTrainerBot.ledVerde     =00;

  miTrainerBot.distancia = USLeeDistancia();

#define K1    30
  miTrainerBot.velocidadMotorDerecho    = VELOCIDAD;     //230
  miTrainerBot.velocidadMotorIzquierdo  = VELOCIDAD ;    //255

  miTrainerBot.sentido =1;
  miTrainerBot.numPasos=5;

  miTrainerBot.IRcode=IRSituaTrainer();

  //    Es preciso hacer una funcion Calibra() que ajuste esto
  miTrainerBot.IRsmax[0] = 900;
  miTrainerBot.IRsmax[1] = 906;
  miTrainerBot.IRsmax[2] = 977;
  miTrainerBot.IRsmax[3] = 700;
  miTrainerBot.IRsmin[0] = 200;
  miTrainerBot.IRsmin[1] = 200;
  miTrainerBot.IRsmin[2] = 200;
  miTrainerBot.IRsmin[3] = 100;

  /*
  miTrainerBot.IRsensorIzquierdo=0;
  miTrainerBot.IRsensorCI=0;
  miTrainerBot.IRsensorCD=0;
  miTrainerBot.IRsensorDerecho=0;
  */
}
