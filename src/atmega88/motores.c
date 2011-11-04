#include <avr/interrupt.h>
#include <util/delay.h>

#include "definiciones.h"
#include "motores.h"


volatile unsigned char velMI;
volatile unsigned char velMD;

static inline void actualizar_velocidad (void) {
  vel_motor_derecho(velMD);
  vel_motor_izquierdo(velMI);
}

/*
static inline void inc_vel_md(void){
  if (velMD < VEL_MAX_ADELANTE) velMD++;
}

static inline void inc_vel_mi(void){
  if (velMI < VEL_MAX_ADELANTE) velMI++;
}

static inline void dec_vel_md(void){
  if (velMD > VEL_MAX_ATRAS) velMD--;
}

static inline void dec_vel_mi(void){
  if (velMI < VEL_MAX_ADELANTE) velMI++;
}
*/
void configurar_motores(void) {
  SetBit(DDR_NSLEEP,NSLEEP_NUMBER);
  ClearBit(DDR_NFAULT,NFAULT_NUMBER);
  ClearBit(PORT_NSLEEP,NSLEEP_NUMBER);

  /*Configurar PWM */
  SetBit(DDR_MI_IN1,MI_IN1_NUMBER);
  SetBit(DDR_MI_IN2,MI_IN2_NUMBER);
  TCCR0A = (1<<COM0A1) | (0<<COM0A0) | (1<<COM0B1) | (1<<COM0B0) | (1<<WGM01) | (1<<WGM00);
  TCCR0B = (0<<WGM02);

  SetBit(DDR_MD_IN1,MD_IN1_NUMBER);
  SetBit(DDR_MD_IN2,MD_IN2_NUMBER);
  TCCR1A = (1<<COM0A1) | (1<<COM0A0) | (1<<COM0B1) | (0<<COM0B0) | (0<<WGM11) | (1<<WGM10);
  TCCR1B = (0<<WGM13) | (1<<WGM12);

  ApagarMotores();
  _delay_ms(2);
}

void ApagarMotores(void) {
  ClearBit(PORT_NSLEEP,NSLEEP_NUMBER);
  Detener();
  TCCR0B &= TMR0MASKOFF;
  TCCR1B &= TMR1MASKOFF;
}

void EncenderMotores(void) {
  TCCR0B |= TMR0MASKON;
  TCCR1B |= TMR0MASKON;
  SetBit(PORT_NSLEEP,NSLEEP_NUMBER);
}

void Detener(){
  velMD = VEL_DETENIDO;
  velMI = VEL_DETENIDO;
  actualizar_velocidad();
}

void GirarIzquierda(){
  velMD = VEL_ADELANTE;
  velMI = VEL_ATRAS;
  actualizar_velocidad();
}

void GirarDerecha(){
  velMI = VEL_ADELANTE;
  velMD = VEL_ATRAS;
  actualizar_velocidad();
}

void MoverAdelante(){
  velMI = VEL_ADELANTE;
  velMD = VEL_ADELANTE;
  actualizar_velocidad();
}

void MoverAtras(){
  velMI = VEL_ATRAS;
  velMD = VEL_ATRAS;
  actualizar_velocidad();
}


