/*
jeje

    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0

    Motor Driver L9110
    Alimentacion:   5V

    Modulo:   AppServer.cpp

        Funciones:
            void AppServer( void )


    Notas 1   Este programa puede comprobarse desde el IDE de Arduino
              Para ello solo hay que  teclear los comandos desde el
              Monitor Serie

              Por ejemplo, la secuencia LR128 enciende el LED rojo
              con intensidad 128

              Igualmente MA101 ejecuta la funcion Palante() situada
              en Motor.cpp

              Es preciso ajustar la velocidad a 9600 ( se puede
              aumentar, pero la del modulo HC-06 es 9600
              ( dicha velocidad puede aumentarse por medio de comandos AT
              pero esto rebasa este programa )

              Adicionalmente, el ajuste de linea debe establecerse en
              Nueva Linea ( '\n' )
*/
#include "ArduinoTrainer.h"

extern TrainerBot miTrainerBot;

#define BUFFER_LEN 100              //    Buffer Serie
#define BUFFER_MAXLEN 6             //    Longitud del mensaje enviado por App Inventor





/*
    void AppServer(void)

    Proposito:
        a)  Servidor Bluetooth que se conecta con
            la aplicacion TrainerBotMonitor
            realizada con AppInventor


    Funcionamiento:

        1) Lee el puerto serie a la espera de paquetes

        2) Un paquete posee la siguiente estructura

            Longitud: 6 bytes
            Caracter terminador '\n' ( ASCII 10 )
            Forma: "CONNN\n"  siendo
            C   Clase   { 'L' , 'M' , 'I', 'P' , 'S' }
            OO  Orden
            NNN Numero
            \n  Terminador

    Nota 3:   //  Una orden acaba en nueva linea
              //  Aqui se procesa la linea leida del puerto serie que esta en buffer[]

    Nota 4:   El comando "S" hace que el estado de TrainerBot ( campos de la estructura )
            se envie a la app.

    Nota 5: Descripcion del paquete recibido por la app

    a)      //    Clase de paquete  El primer byte puede ser  { 'L' , 'M' , 'H' , 'I' , 'P' , 'S' }
            //    Indica que clase de orden se realiza y sobre que hardware se actua
            //    { Led  Motor  Hcsro4  Infrared State }

    b)      //    Orden de mando. El segundo byte indica la orden a ejecutar

            Indica que clase de orden se realiza
            ( La clase ´L' -LED- tiene tiene tres ordenes { 'R' , 'V' , 'A' }
            para activar cada LED
            Igualmente la clase de orden 'M' posee diferentes ordenes para cada motor

 */
void AppServer( void )
{
  static int bytein;
  static char bufferin[BUFFER_LEN] , clase ;
  static int comando , contador = 0 , orden ;
  int situacion;

  while(1)
  if(Serial.available() > 0)
  {
    bytein = Serial.read();
    //  Serial.write(bytein);
    //Led_Parpadea( LED_VERDE , 50 , 50 );

    //  Aqui se procesa la linea leida del puerto serie que esta en buffer[]
    //if( (bytein == 10)   (bytein ==13)  )
    if( bytein == '\n'  )
    {
      Pita();
      //Led_Parpadea( LED_AMARILLO , 10 , 10 );

      //  Proceso del paquete

      //    Clase de paquete  El primer byte puede ser  { 'L' , 'M' , 'H' , 'I' , 'P' , 'S' }
      //    Indica que clase de orden se realiza y sobre que hardware se actua
      //    { Led  Motor  Hcsro4  Infrared State }
      clase = *bufferin;

      //    Orden de mando ( La clase ´L' -LED- tiene tiene tres ordenes { 'R' , 'V' , 'A' }
      //    para activar cada LED
      //    Igualmente la clase de orden 'M' posee diferentes ordenes para cada motor
      //    Indica que clase de orden se realiza

      if( contador >= 2 )
        orden = *(bufferin+1);
     else
        orden=0;

      //    Lo siguiente es un numero, como por ejemplo  LR127
      if( contador >=3 )
        comando= atoi( (bufferin+2) );
      else
        comando =0;
/*
      Serial.print("\n_______________________________");
      Serial.print("\nRecibido ... "); Serial.print( bufferin );
      Serial.print( "\nContador .."); Serial.print( contador );
      Serial.print("\n Clase ...");Serial.print(clase);
      Serial.print("\n Orden ...");Serial.print(orden);
      Serial.print("\n Comando ...");Serial.print(comando);
      Serial.print("\n_______________________________\n");
*/
      switch (clase)
      {
        //    Gestion del Menu de App Inventor Screen_LEDs

        //  Funciones que actuan sobre el sensor US
        case 'H':
        {
            miTrainerBot.distancia = USLeeDistancia();
            USImprimeDistancia( MM );
            delay(1000);
            break;
        }
        break;


        //  Funciones que actuan sobre el sensor de linea
        case 'I':
        {
          situacion = IRSituaTrainer();
          IRImprimeSensor();
          delay(1000);
          //Serial.print("Situacion");
          //Serial.println(situacion);
        }
        break;


        //  Funciones que actuan sobre LEDs
        case 'L':
        {
            switch (orden)
            {
              case 'R':
              {
                miTrainerBot.ledRojo=comando;
                analogWrite( LED_ROJO , comando );
              }
              break;

              case 'A':
              {
                miTrainerBot.ledAmarillo=comando;
                analogWrite( LED_AMARILLO , comando );
              }
              break;

              case 'V':
              {
                miTrainerBot.ledVerde=comando;
                analogWrite( LED_VERDE , comando );
              }
              break;

              default:  BipBip(); break;
            }
        }
        delay(1000);
        break;            //    Sale de la clase 'L'



        //    Gestion del Menu de App Inventor Screen_Motor


        //  Funciones que actuan sobre los motores en modo continuo
        case 'M':
        {
          switch( orden )
            {
              case 'I':
              {
                switch ( comando )
                {
                  case 101:        IzquierdaPalante_pasos( miTrainerBot.numPasos );break;
                  case 102:        IzquierdaPatras_pasos( miTrainerBot.numPasos );break;
                  case 103:        Stop_Motor_Left();break;

                  /*
                  case 101:        Forward_Motor_Left();break;
                  case 102:        Reverse_Motor_Left();break;
                  case 103:        Stop_Motor_Left();break;
                  */
                }
              }
              break;

              case 'D':
              {
                switch ( comando )
                {         
                  case 101:DerechaPalante_pasos( miTrainerBot.numPasos );break;
                  case 102:DerechaPatras_pasos( miTrainerBot.numPasos );break;
                  case 103:Stop_Motor_Right();break;
               /*
                  case 101:Forward_Motor_Right();break;
                  case 102:Reverse_Motor_Right();break;
                  case 103:Stop_Motor_Right();break;
               */
                }
              }
              break;

              case 'A':
              {
                switch ( comando )
                {
                  case 101:Palante_pasos( miTrainerBot.numPasos );break;
                  case 102:Patras_pasos( miTrainerBot.numPasos );break;
                  case 103:Pita();break;

                  /*
                  case 101:Palante();delay(1500);Stop();break;
                  case 102:Patras();break;
                  case 103:Stop();break;
                  */
                }
              }
              break;

           }
        }
        break;

        //    Gestion del Menu de App Inventor Screen_Programas
        //
        case 'P':
        {
          switch ( orden )
            {

              case '1': Led_Test();break;
              case '2': Switch_Test();break;
              case '3': Distance_Test();break;
              case '4':Motor_Test();break;
              case '5':break;
              case '6':break;
              case '7':break;
              case '8':break;
              case '9':break;



              //    Original
/*
              case '1':miTrainerBot.velocidadMotorIzquierdo++; //IzquierdaPalante_pasos( miTrainerBot.numPasos );break;
              case '2':Palante_pasos( miTrainerBot.numPasos );break;break;
              case '3':DerechaPalante_pasos( miTrainerBot.numPasos  );break;
              case '4':MediavueltaLeft_pasos( miTrainerBot.numPasos );break;
              case '5':Stop();break;
              case '6':MediavueltaRight_pasos( miTrainerBot.numPasos );break;
              case '7':IzquierdaPatras_pasos( miTrainerBot.numPasos );break;
              case '8':Patras_pasos( miTrainerBot.numPasos );break;
              case '9':DerechaPatras_pasos( miTrainerBot.numPasos );break;
*/
              //    RobyCAD

              case 'A':
              {
                  if( miTrainerBot.numPasos >1 )
                  {
                    miTrainerBot.numPasos--;
                    BipBip();
                  }
                  else
                    Bipveces(5);
              }
              break;

              //    Incrementa el numero de pasos
              case 'B':
              {
                  if( miTrainerBot.numPasos <25 )
                  {
                    miTrainerBot.numPasos++;
                    BipBip();
                  }
                  else
                    Bipveces(5);
              }
              break;

              case 'C':  Redil();break;

              case 'D':  Pita();break;

              case 'E':  Pita();break;
              break;

              case 'F':
              break;

              default:  BipBip(); break;
            }
        }
        break;

        //    Modulo que envia el estado de TrainerBot a App Inventor /  Processing
        //

        case 'S':
        {
          ImprimeTrainerBot();
          miTrainerBot.medicion++;
          break;
        }
        break;

        //  Si recibimos un paquete con primer byte diferente se descarta
        //  Resto de ordenes ( Primera letra ) se rechazan
        default:  BipBip(); break;
      }

      //  Orden gestionada, blanqueamos el buffer de entrada
      contador=0;
      memset( bufferin , 0 , BUFFER_LEN );

      while( Serial.available() > 0)
      {
        bytein = Serial.read();
        delay(5);
      }

    }
    else
    {
      bufferin[contador++]=bytein;
      //  Control de longitud de paquete
      if( contador > BUFFER_MAXLEN )
      {
        //  Enviamos mensaje de error
        //Serial.write("\nERROR\n");
        //Vaciamos el buffer de entrada
        delay(5);                          // OJO --> No eliminarlo

        //    Leemos el resto del buffer y lo vaciamos
        while( Serial.available() > 0)
        {
          bytein = Serial.read();
          delay(5);
        }

         //  Iniciamos el buffer de entrada
        contador=0;
        memset( bufferin , 0 , BUFFER_LEN );
        LedParpadea( LED_ROJO , 500 , 250 );
      }
    }
  }
}






/*
      void ImprimeTrainerBot( void )

      Manda el estado de TrainerBot por el puerto serie
      Como estado se entiende las variables internas de TrainerBot

      Ademas se envia un numero de medida correlativo
      correspondiente al campo medida de la clase TrainerBot

      Nota 1: El delimitador de campo es un caracter '.'

*/
void ImprimeTrainerBot( void )
{
  static long contador=1;

  //  Ver una alternativa con sprintf
  //  En un buffer
  Serial.print( String( contador++) + '*' );
  Serial.print( String( miTrainerBot.medicion ) + '*' );
  Serial.print( String(miTrainerBot.ledRojo) + '*' );
  Serial.print( String(miTrainerBot.ledAmarillo) + '*' );
  Serial.print( String(miTrainerBot.ledVerde) + '*' );
  Serial.print( String(miTrainerBot.distancia) + '*' );
  Serial.print( String(miTrainerBot.velocidadMotorDerecho) + '*' );
  Serial.print( String(miTrainerBot.velocidadMotorIzquierdo) + '*' );
  Serial.print( String(miTrainerBot.numPasos) + '*' );
  Serial.print( String(miTrainerBot.sentido) + '*' );
  Serial.print( String(miTrainerBot.IRsensorIzquierdo) + '*' );
  Serial.print( String(miTrainerBot.IRsensorCI) + '*' );
  Serial.print( String(miTrainerBot.IRsensorCD) + '*' );
  Serial.print( String(miTrainerBot.IRsensorDerecho) + '*' );
  Serial.print( String(miTrainerBot.IRcode) + '*' );
  Serial.println();

  delay(10);
}


/*
01 long medicion;
02  int ledRojo;
03  int ledAmarillo;
04  int ledVerde;

05  int distancia;

06  int velocidadMotorDerecho;
07  int velocidadMotorIzquierdo;
08  int numPasos;
09  int sentido;

10  int IRsensorIzquierdo;
11  int IRsensorCI;
12  int IRsensorCD;
13  int IRsensorDerecho;
14  int IRcode;
*/
