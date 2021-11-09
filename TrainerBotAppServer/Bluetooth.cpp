/*
      Modulo:     Bluetooth.cpp 
     
      Funciones: 
     
          void Test_Follower(void )       Interfaz con Proccessing
          void BluetoothLedONOFF()        Obsoleta

 */
#include "ArduinoTrainer.h"

extern TrainerBot miTrainerBot;






void Test_Follower(void )
{
  char buffer[100];
  int index=0;
  int opcion;
  static int flagConexion =0;
  
  if( Serial.available() > 0 )
  {
    //    Leemos una linea de texto enviada por Processing
    memset( buffer, 0, 100 );
    while( Serial.available() > 0 )
      buffer[index++] = Serial.read();
    
    //    El comando está en el primer caracter
    
    opcion = buffer[0];
    
    switch( opcion )
    {
      //    Inicia la conexion.
      //    Apaga LED_ROJO y Parpadea LED_AMARILLO
      //    Envia "OK"
      case 'I':
        flagConexion = true;
        digitalWrite( 3 , LOW );
        LedParpadea( LED_ROJO , 25 , 25 );
        
        //    Este es el punto de inicio de Cliente
        //    Envio la Palabra OK
        Serial.print("OK\n");
        return;
    
      //    Tecla Arriba
      case 'U':
        LedParpadea( LED_ROJO , 50 , 50 );
        Palante_pasos( miTrainerBot.numPasos );
        break;
        
      case 'D':
        LedParpadea( LED_ROJO , 50 , 50 );
        Patras_pasos( miTrainerBot.numPasos );
        break;
            
      //   Tecla IZDA_PALANTE
      //    Enciende LED_AMARILLO
      case 'L':
        LedParpadea( LED_AMARILLO , 50 , 50 );
        IzquierdaPalante_pasos( miTrainerBot.numPasos );
        break;
    
      //   Tecla DERECHA_PALANTE
      //    Enciende LED_VERDE
      case 'R':
        LedParpadea( LED_VERDE , 50 , 50 );
        DerechaPalante_pasos( miTrainerBot.numPasos );
        break;

      //   Tecla IZDA_PATRAS
      //    Enciende LED_AMARILLO
      case 'M':
        LedParpadea( LED_AMARILLO , 50 , 50 );
        IzquierdaPatras_pasos( miTrainerBot.numPasos );
        break;
    
      //   Tecla DERECHA_PATRAS
      //    Enciende LED_VERDE
      case 'N':
        LedParpadea( LED_VERDE , 50 , 50 );
        DerechaPatras_pasos( miTrainerBot.numPasos );
        break;

      //   Tecla S
      //    Hace un Scan
      case 'S':
        break;

      //   Tecla W
      //   Avanza el numero de pasos
      case 'W':
        LedParpadea( LED_VERDE , 50 , 50 );
        if( miTrainerBot.numPasos <5 )
          miTrainerBot.numPasos++;
        break;

      //   Tecla E
      //   Retrocede el numero de pasos
      case 'E':
        LedParpadea( LED_VERDE , 50 , 50 );
        if( miTrainerBot.numPasos >0 )
          miTrainerBot.numPasos--;
        break;

      //   Tecla Y
      //   Avanza velocidad motorIzquierdo
      case 'Y':
        LedParpadea( LED_VERDE , 50 , 50 );
        if( miTrainerBot.velocidadMotorIzquierdo <= 250 )
          miTrainerBot.velocidadMotorIzquierdo+=5;
        break;

      //   Tecla O
      //   Retrocede velocidad motorIzquierdo
      case 'O':
        LedParpadea( LED_VERDE , 50 , 50 );
        if( miTrainerBot.velocidadMotorIzquierdo >= 155 )
          miTrainerBot.velocidadMotorIzquierdo-=5;
        break;

      //   Tecla P
      //   Avanza velocidad motorDerecho
      case 'P':
        LedParpadea( LED_VERDE , 50 , 50 );
        if( miTrainerBot.velocidadMotorDerecho <= 250 )
          miTrainerBot.velocidadMotorDerecho+=5;
        break;

      //   Tecla K
      //   Retrocede velocidad motorDerecho
      case 'K':
        LedParpadea( LED_VERDE , 50 , 50 );
        if( miTrainerBot.velocidadMotorDerecho >= 155 )
          miTrainerBot.velocidadMotorDerecho-=5;
        break;

      //  Tecla DESCONEXION
      //  Enciende LED_ROJO
      case 'Q':
        flagConexion = false;
        digitalWrite( 3, HIGH );
        return;
        break;    
      
      default:
        return;
        break;
    }
    int situacion = IRSituaTrainer();
    
    ImprimeTrainerBot();
    //Imprime_Sensor();
  }   
}     







void BluetoothLedONOFF() 
{
  static int bytein;
  
  while( 1 )
  {
    if(Serial.available() > 0)
    {
      bytein = Serial.read();
    
      switch (bytein)
      {
        case '0':
            digitalWrite(LED_ROJO, LOW);break;
        case '1':
            digitalWrite(LED_ROJO, HIGH);break; 
      }
    }
  }
}
