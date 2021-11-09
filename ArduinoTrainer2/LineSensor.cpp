/*
    Hispalis RobIOTICS Arduino Trainer Monitor
    Version Shield: 2.0
    
    Motor Driver L9110
    Alimentacion:   5V
   
    Modulo:   LineSensor.ino

          Funciones relacionadas con el sensor de linea

    Notas 1:    TrainerBot integra una sensor de 4 emisores receptores IR
                Los sensores se conectan a las entradas A0 -A3
                El valor de lectura de blanco es   0
                El valor de lectura de negro es 1024   

    Notas 2:    El PCB del Sensor de Linea tiene impreso un "1"
                El conector al lado del "1" corresponde a la entrada A0
                y se corresponde con el sensor S1 del Sensor de linea
                La correspondencia entre pines y sensores es

                A0    -> Sensor S1    Izquierdo 
                A1    -> Sensor S2    CentroIzquierdo 
                A2    -> Sensor S3    CentroDerecho 
                A3    -> Sensor S4    Derecho 
                
    Nota 3:     Para determinar la posicion del sensor
                sobre una linea negra debe usarse
                cinta adhesiva negra de un ancho
                de 25 mm o superior

                Inicialmente asignamosun "peso" numerico 
                a cada sensor

                Los Pesos asignados son

                S1  8         Izquierdo
                S2  4         Centro Izquierdo
                S3  2         Centro Derecho
                S4  1         Sensor Derecho

                Como cada sensor devuelve un valor  { 0 , 1 } 
                La suma ponderada de los sensores 
                devolvera un entero en el rango     { 0 , 15 }

                por ejemplo,
                
                 0 corresponde a 4 lecturas de negro
                15 corresponde a 4 lecturas de blanco
                 3 corresponde a 2 + 1
                12 corresponde a 8 + 4 

                etc
                
    Funciones:

        int IRSituaTrainer( void )
        void Situacion( void )
        void IRImprimeNormales( void );
        void IRImprimeMinimos( void );
        void IRImprimeMaximos( void );
        

    ToDO:   Crear funciones de calibrado que
            actualicen los vectores smin[] y smax[]

            Grabar dichos datos en eeprom
*/
#include "ArduinoTrainer.h"

extern TrainerBot miTrainerBot;



/*
    Funcion: IRSituaTrainer( void )
    Sensores:
      A0  Derecha             Peso: 1
      A1  Centro derecha      Peso: 2
      A2  Centro Izquierda    Peso: 4
      A3 Izquierda            Peso: 8

    Nota: EL valor devuelto esta en el rango { 0 , 15 }

    Si un sensor detecta blanco devuelve el valor de su peso

    EL valor de retorno es la suma de las medidas de los 4 sensores
    
    El valor máximo de retorno es 8+4+2+1 = 15. Esto corresponde a
    los 4 sensores leyendo blanco
 */
int IRSituaTrainer( void )
{
    int retorno = 0;
    int limiteuno; 
    int ind;
    
    limiteuno=  128;

    IRLeeSensor();    

    //adj_1 = map(sensor1, s1_min, s1_max, 0, 255);
    //adj_1 = constrain(adj_1, 0, 255);
    
    for( ind=0 ; ind<4 ; ind ++ )
    {
      miTrainerBot.IRsnorm[ind] = map(miTrainerBot.IRsensor[ind], miTrainerBot.IRsmin[ind], miTrainerBot.IRsmax[ind], 0, 255);
      miTrainerBot.IRsnorm[ind] = constrain(miTrainerBot.IRsnorm[ind], 0, 255);
    }

    //    El codigo siguiente se puede simplificar
    //    Introduciendolo en el for anterior
    if( miTrainerBot.IRsnorm[0]<=  limiteuno )
      retorno = retorno + 8;
        
    if( miTrainerBot.IRsnorm[1]<=  limiteuno )
      retorno = retorno + 4;
        
    if( miTrainerBot.IRsnorm[2]<=  limiteuno )
      retorno = retorno + 2;
    
    if( miTrainerBot.IRsnorm[3]<=  limiteuno )
      retorno = retorno + 1;

    //  Esto es redundante   y es por retrocompatibilidad 
    //  en la definicion de la estructura TrainerBot
    
    miTrainerBot.IRsensorIzquierdo  = miTrainerBot.IRsnorm[0];
    miTrainerBot.IRsensorCI         = miTrainerBot.IRsnorm[1];
    miTrainerBot.IRsensorCD         = miTrainerBot.IRsnorm[2];
    miTrainerBot.IRsensorDerecho    = miTrainerBot.IRsnorm[3];
    miTrainerBot.IRcode             = retorno;

    return retorno;
}



/*
    Funcion: void Situacion( void )

    Proposito:  Imprime datos del sensor
        
        Ledturas
        Lecturas normalizadas
        Valores Minimos
        Valores Maximos
 */
void Situacion( void )
{
  int situacion;
  
  situacion = IRSituaTrainer();
  
  Serial.print("Situacion");
  Serial.println(situacion);
  IRImprimeSensor();
  IRImprimeNormales();
  IRImprimeMinimos();
  IRImprimeMaximos();
}





/*
    Funcion: void IRImprimeNormales(void)

    Proposito:  Imprime Valores Normalizados
 */
void IRImprimeNormales(void)
{
  int ind;
  Serial.print("IRNormales ...");
  for( ind =0; ind <4 ; ind++)
      Serial.print("\t"+String( miTrainerBot.IRsnorm[ind] ));
  Serial.println("");
  delay(500);
}



/*
    Funcion: void IRImprimeMinimos(void)

    Proposito:  Imprime Valores Maximos de cada sensor
 */
void IRImprimeMinimos(void)
{
  int ind;
  Serial.print("IRMinimos ...");
  for( ind =0; ind <4 ; ind++)
      Serial.print("\t"+String( miTrainerBot.IRsmin[ind] ));
  Serial.println("");
  delay(500);
}



/*
    Funcion: void IRImprimeMaximos(void)

    Proposito:  Imprime Valores Maximos de cada sensor
 */
void IRImprimeMaximos(void)
{
  int ind;
  Serial.print("IRMaximos ...");
  for( ind =0; ind <4 ; ind++)
      Serial.print("\t"+String( miTrainerBot.IRsmax[ind] ));
  Serial.println("");
  delay(500);
}




