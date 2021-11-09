/*
    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0
    
    Motor Driver L9110
    Alimentacion:   5V
   
    Modulo:   Seguidor.cpp

    Funciones de seguidor de Linea
    
    Funciones:

       void Seguidor(void )
    
  ToDo:   Revisar y reconstruir
*/                
#include "ArduinoTrainer.h"

extern TrainerBot miTrainerBot;



// Lecturas normalizadas
int adj_1 =0;
int adj_2 =0;
int adj_3 =0;
int adj_4 =0;


// You can change the min/max values below to fine tune each sensor on your bot

int s1_min = 100;
int s1_max = 985;
int s2_min = 100;
int s2_max = 985;
int s3_min = 100;
int s3_max = 985;
int s4_min = 100;
int s4_max = 985;

//Mias
int limitecero = 60;
int limiteuno= 128;

// Limite para que un sensor lea Negro
int lower_threshold = 30;

// Limite para que un sensor lea un valor medio entre Blanco y Negro. Esto debería ser cuando esta medio salido de la linea negra
// Esto es para investigar los colores , o si la variacion es lineal o logaritmica
int threshold = 128;

// Limite para que un sensor lea Blanco
int upper_threshold = 230;

// end of changeable variables 

 

 


void Seguidor(void)
{
    int situacion;
    
    situacion = IRSituaTrainer();
    
    //  Empezamos verificando que TrainerBot esté en la linea negra
    //  Para ello comprobamos que los sensores internos esten al menos medio centrados
    
    //if (adj_2 > threshold && adj_3 > threshold)
    if (adj_2 > lower_threshold && adj_3 > lower_threshold)
    {
            // Comprobados los sensores, tiramos palante
      Palante_pasos(3);        
    }

    //    El robot se para cdo todos los sensores leen negro
    else if ( (adj_1 < 1) && (adj_2 < 1) && (adj_3 < 1) && (adj_4 < 1) )
    {
      Stop();          
    }
      /*
          Si el sensor central no esta leyendo NEGRO, es que está descentrado
            Entonces algun sensor interno estara descentrado, pero no sabemos cual
            En otras palabras, el robot se ha salido por la derecha o por la izquierda
          Si un sewnsor externo se ha salido ( y leerá BLANCO ), y el otro se ha introducido en la linea Y LEE CLARAMENTE negro
      
          Veamos qué sensor está sobre la linea NEGRA
      */
    else 
    {
        //  Primero->   Chequeamos el sensor izquierdo externo 
        //  Si se ha movido hacia la derecha, paramos motor izquierdo, y hacemos un giro a derecha
        if (adj_1 < upper_threshold && adj_4 > upper_threshold)
        {
            DerechaPalante_pasos(3);
        }
        //  Segundo->   Chequeamos el sensor derecho externo 
        //  Si se ha movido hacia la izquierda, paramos motor derecho, y hacemos un giro a izquierda
        
        else if (adj_1 > upper_threshold && adj_4 < upper_threshold)
        {
            IzquierdaPalante_pasos(3);
        }
        //    A continuacion vienen las situaciones mas frecuentes
        //    Tercero->   Chequeamos sensor Centro Izquierdo
        //      Si se ha movido hacia la derecha ( y sensor 2 LEE NEGRO y sensor 3 LEE BLANCO )
        else if (adj_2 < upper_threshold && adj_3 > upper_threshold)
        {
            DerechaPalante_pasos(1);
            // motor_left.run(RELEASE);
            // motor_left.setSpeed(0);
            // motor_right.run(FORWARD);
            // motor_right.setSpeed(speed_value);
        }
        
        //    Cuarto->   Chequeamos sensor Centro Derecho
        //      Si se ha movido hacia la derecha ( y sensor 2 LEE BLANCO y sensor 3 LEE NEGRO )
        
        else if (adj_2 > upper_threshold && adj_3 < upper_threshold)
        {
            IzquierdaPalante_pasos(1);
            // motor_left.run(FORWARD);
            // motor_left.setSpeed(speed_value);
            // motor_right.run(RELEASE);
            // motor_right.setSpeed(0);
        }
    }
}














