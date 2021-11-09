/*
        HispalisRoBIOTICS

        Arduino Trainer v 2.0


      Funciones de Control de Motores
        
        void Palante_pasos( int pasos )
        void Patras_pasos( int pasos )
        void DerechaPalante_pasos( int pasos )
        void DerechaPatras_pasos( int pasos )
        void IzquierdaPalante_pasos( int pasos )
        void IzquierdaPatras_pasos( int pasos )
        void MediavueltaLeft_pasos( int pasos )
        void Mediavuelta_Right_pasos( int velocidad )
        
        void Palante( int velocidad )
        void Patras( int velocidad )
        void Stop()
        void Mediavuelta_Left( void )
        void Mediavuelta_Right( void )
        void DerechaPalante( void  )
        void DerechaPatras( void  )
        void IzquierdaPalante( void )
        void IzquierdaPatras( void )

        
        
*/

#include "ArduinoTrainer.h"


void Palante_pasos( int pasos )
{  
  int cont;

  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Palante();  
    delay( 50);
    Stop();
    delay( 20 );
  }
}



void Patras_pasos( int pasos )
{  
  int cont;

  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Patras();  
    delay( 60);
    Stop();
    delay( 40 );
  }
}



void DerechaPalante_pasos( int pasos )
{  
  int cont;
  Stop_Motor_Left();
  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Forward_Motor_Right();
    delay( 60);
    Stop();
    delay( 40 );
  }
}



void DerechaPatras_pasos( int pasos )
{  
  int cont;
  Stop_Motor_Left();
  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Reverse_Motor_Right();
    delay( 60);
    Stop();
    delay( 40 );
  }
}



void IzquierdaPalante_pasos( int pasos )
{  
  int cont;
  Stop_Motor_Right();
  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Forward_Motor_Left();
    delay( 60);
    Stop();
    delay( 40 );
  }
}



void IzquierdaPatras_pasos( int pasos )
{  
  int cont;
  Stop_Motor_Right();
  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Reverse_Motor_Left();
    delay( 60);
    Stop();
    delay( 40 );
  }
}



void MediavueltaLeft_pasos( int pasos )
{
  int cont;

  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Forward_Motor_Right();
    Reverse_Motor_Left( );
    delay( 60);
    Stop();
    delay( 40 );
  }
}



void MediavueltaRight_pasos( int pasos )
{
  int cont;

  for( cont = 1 ; cont <= pasos ; cont ++ )
  { 
    Reverse_Motor_Right();  
    Forward_Motor_Left();
    delay( 60);
    Stop();
    delay( 40 );
  }
}




/*
 
    Funciones de movimiento continuo

        En la funcion Palante() hay un cierto retardo entre motores
        Aunque ese retardo es minimo incluso en un uP a 16Mhz
  
 */

void Palante( void )
{
  
  Forward_Motor_Right();
  Forward_Motor_Left();
}



void Patras( void )
{
  Reverse_Motor_Left();
  Reverse_Motor_Right();
}



void Stop( void )
{
  Stop_Motor_Left();
  Stop_Motor_Right();
}



void Mediavuelta_Left( void )
{
  Forward_Motor_Right();
  Reverse_Motor_Left();
}



void Mediavuelta_Right( void )
{
  Reverse_Motor_Right();  
  Forward_Motor_Left();
}



void DerechaPalante( void )
{
  Forward_Motor_Right();
}



void DerechaPatras( void  )
{
  Reverse_Motor_Right();  
}



void IzquierdaPalante( void )
{
  Forward_Motor_Left();
}




void IzquierdaPatras( void )
{
  Reverse_Motor_Left();
}

