#include <avr/interrupt.h>
#include <util/delay.h>

#include "definiciones.h"
#include "motores.h"

#define MDAdelante() {ClearBit(PORT_MD_IN1,MD_IN1_NUMBER);SetBit(PORT_MD_IN2,MD_IN2_NUMBER);}
#define MDAtras() {SetBit(PORT_MD_IN1,MD_IN1_NUMBER);ClearBit(PORT_MD_IN2,MD_IN2_NUMBER);}
#define MDStop() {ClearBit(PORT_MD_IN1,MD_IN1_NUMBER);ClearBit(PORT_MD_IN2,MD_IN2_NUMBER);}

#define MIAtras() {ClearBit(PORT_MI_IN1,MI_IN1_NUMBER);SetBit(PORT_MI_IN2,MI_IN2_NUMBER);}
#define MIAdelante() {SetBit(PORT_MI_IN1,MI_IN1_NUMBER);ClearBit(PORT_MI_IN2,MI_IN2_NUMBER);}
#define MIStop() {ClearBit(PORT_MI_IN1,MI_IN1_NUMBER);ClearBit(PORT_MI_IN2,MI_IN2_NUMBER);}

void ConfigurarMotores(void) {
  SetBit(DDR_NSLEEP,NSLEEP_NUMBER);
  ClearBit(PORT_NSLEEP,NSLEEP_NUMBER);

  ClearBit(DDR_NFAULT,NFAULT_NUMBER);
  SetBit(PORT_NFAULT,NFAULT_NUMBER);  //Agrego Pull up

  /*Configurar PWM */
  SetBit(DDR_MI_IN1,MI_IN1_NUMBER);
  SetBit(DDR_MI_IN2,MI_IN2_NUMBER);

  SetBit(DDR_MD_IN1,MD_IN1_NUMBER);
  SetBit(DDR_MD_IN2,MD_IN2_NUMBER);

  ApagarMotores();
  _delay_ms(2);
}

void ApagarMotores(void) {
  ClearBit(PORT_NSLEEP,NSLEEP_NUMBER);
  Detener();
}

void EncenderMotores(void) {
  SetBit(PORT_NSLEEP,NSLEEP_NUMBER);
  Detener();
}

void Detener(){
  ClearBit(PORT_MI_IN1,MI_IN1_NUMBER);
  ClearBit(PORT_MI_IN2,MI_IN2_NUMBER);

  ClearBit(PORT_MD_IN1,MD_IN1_NUMBER);
  ClearBit(PORT_MD_IN2,MD_IN2_NUMBER);
}

void GirarIzquierdaAdelante(){
  MIStop();
  MDAdelante();
}

void GirarDerechaAdelante(){
  MDStop();
  MIAdelante();
}

void GirarIzquierdaAtras(){
  MDStop();
  MIAtras();
}

void GirarDerechaAtras(){
  MIStop();
  MDAtras();
}

void RotarIzquierda(){
  MDAdelante();
  MIAtras();
}

void RotarDerecha(){
  MIAdelante();
  MDAtras();
}

void MoverAdelante(){
  MDAdelante();
  MIAdelante();
}

void MoverAtras(){
  MDAtras();
  MIAtras();
}
