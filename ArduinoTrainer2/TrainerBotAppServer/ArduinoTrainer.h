/*
Juju
        HispalisRoBIOTICS

        Arduino Trainer v 2.0

    Version Shield: 2.0

    Motor Driver L9110
    Alimentacion:   5V


    Revision: ABRIL 2019


    Modulo:   ArduinoTrainer.h


        Notas: Arduino TRainer v2.0 mantiene el pin-out de v1.
               Salvo los pines del sensor HCSR04 que se invierten

               Trainerv1.0    { ECHO = pin 4   TRIGGER = pin 2 }
               Trainerv2.0    { ECHO = pin 2   TRIGGER = pin 4 }
*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

#include <avr/io.h>
#include <avr/interrupt.h>





//    Arduino Trainer pin out
#define LED_ROJO              3
#define LED_AMARILLO          5
#define LED_VERDE             6

#define MOTOR_IZDO_DIR        7
#define MOTOR_IZDO_SPD        9

#define MOTOR_DCHO_DIR        8
#define MOTOR_DCHO_SPD       10

#define BUZZER               11

#define SWITCH_D12           13
#define SWITCH_D13           12

#define HCSR04_TRIGGER        4//2
#define HCSR04_ECHO           2//4

#define VELOCIDAD           200

#define PARA           for(;;);


#define MM 1
#define CM 2


/*

      Clase TrainerBot

*/

typedef struct
{
  long medicion;
  int ledRojo;
  int ledAmarillo;
  int ledVerde;

  int distancia;

  int velocidadMotorDerecho;
  int velocidadMotorIzquierdo;
  int numPasos;
  int sentido;

  int IRsensorIzquierdo;
  int IRsensorCI;
  int IRsensorCD;
  int IRsensorDerecho;
  int IRcode;
  int IRsensor[4];
  int IRsnorm[4];
  int IRsmin[4];
  int IRsmax[4];
}TrainerBot;


/*

      Prototipos

*/
//    Modulo main                         ********************************************

void SetupTrainerBot( void );         //  Constructor de TrainerBot
                                      //  Ajustar valores minimos/maximos del IRSensor
void ImprimeTrainerBot( void );       //  Revisar.


//    Modulo  AppServer.cpp               ********************************************

//ToDO: Revisar/Ampliar ( state of art )
void AppServer( void );





//    Modulo  Bluetooth.cpp               ********************************************

//ToDO: Revisar

void Test_Follower(void );       //Interfaz con Proccessing
void BluetoothLedONOFF();        //Obsoleta




//    Modulo Tests.cpp                    ********************************************

void Led_Test(void);
void Switch_Test(void);
void Distance_Test(void) ;
void Motor_Test(void);
void LineSensor_Test( void );
void Motor_PWM_Test(void);





//    Modulo Hardware.cpp                 ********************************************

//ToDo: Funciones de Frenado/Cambio de direccion
//      con MotorDerecho() y MotorIzquierdo() ...

void Stop_Motor_Left( void );
void Stop_Motor_Right( void );
void Forward_Motor_Left( void );
void Forward_Motor_Right( void );
void Reverse_Motor_Left( void );
void Reverse_Motor_Right( void );
void MotorDerecho( int  );
void MotorIzquierdo( int );

int USLeeDistancia( void );
void USImprimeDistancia( int );


void IRLeeSensor( void );
void IRImprimeSensor( void );

void Pita(void);
void Beep( int frec , int duracion );
void BipBip( void );
void Bipveces( int );

void LedParpadea( int led , int tiempo_ON , int tiempo_OFF );
void LedRojo( int color );
void LedAmarillo( int color );
void LedVerde( int color );
int Switchd12_esta_pulsado(void);
int Switchd13_esta_pulsado(void);





//    Modulo Estrategia.cpp       ********************************************
//      ToDo:   Revisar funciones/Documentar

void Redil( void );
void Walk_Test(void);
void Hasta_que_lleguesa( int );





//    Modulo Seguidor.cpp -->     ********************************************
//      Actualmente es inservible

void Seguidor(void );       // Inservible





//    Modulo Motor.cpp            ********************************************
//      ToDo:   Funcion GiraGrados( int grados )

void Palante_pasos( int );
void Patras_pasos( int );
void DerechaPalante_pasos( int );
void DerechaPatras_pasos( int );
void IzquierdaPalante_pasos( int );
void IzquierdaPatras_pasos( int );
void MediavueltaLeft_pasos( int );
void MediavueltaRight_pasos( int );

void Palante();
void Patras();
void Stop();
void Mediavuelta_Left( void );
void Mediavuelta_Right( void );
void DerechaPalante( void  );
void DerechaPatras( void  );
void IzquierdaPalante( void );
void IzquierdaPatras( void );





//    Modulo LineSensor.cpp      ********************************************

//      ToDO: Codificar funciones de calibrado

int IRSituaTrainer( void );
void Situacion( void );
void IRImprimeNormales( void );
void IRImprimeMinimos( void );
void IRImprimeMaximos( void );





//    Modulo Bluetooth.cpp      ********************************************
void BluetoothLedONOFF() ;




//        Fin de ArduinoTrainer.h
//
//      *****************************************************************************
