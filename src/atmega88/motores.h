#ifndef _MOTORES_H_
#define _MOTORES_H_

#include <avr/io.h>
#include "definiciones.h"

/* Definiciones de los pines correspondientes a los motores 
 * deberia estar en otro lugar*/

/* Motores (nFault)*/
#define PORT_NFAULT_NAME  C
#define NFAULT_NUMBER     0
/* Motores (nSleep)*/
#define PORT_NSLEEP_NAME  B
#define NSLEEP_NUMBER     5

#define PORT_NFAULT  def_port_reg(PORT_NFAULT_NAME)
#define PIN_NFAULT   def_pin_reg(PORT_NFAULT_NAME)
#define DDR_NFAULT   def_ddr_reg(PORT_NFAULT_NAME)

#define PORT_NSLEEP  def_port_reg(PORT_NSLEEP_NAME)
#define PIN_NSLEEP   def_pin_reg(PORT_NSLEEP_NAME)
#define DDR_NSLEEP   def_ddr_reg(PORT_NSLEEP_NAME)

#define PORT_NRESET  def_port_reg(PORT_NRESET_NAME)
#define PIN_NRESET   def_pin_reg(PORT_NRESET_NAME)
#define DDR_NRESET   def_ddr_reg(PORT_NRESET_NAME)

/* Motor Izquierdo  -- Timer 0 */
/*MI_1 = Motor Left IN1*/
#define PORT_MI_IN1_NAME  D
#define MI_IN1_NUMBER     6
/*MI_2 = Motor Left IN2*/
#define PORT_MI_IN2_NAME	 D
#define MI_IN2_NUMBER		   5

#define PORT_MI_IN1  def_port_reg(PORT_MI_IN1_NAME)
#define PIN_MI_IN1   def_pin_reg(PORT_MI_IN1_NAME)
#define DDR_MI_IN1   def_ddr_reg(PORT_MI_IN1_NAME)

#define PORT_MI_IN2  def_port_reg(PORT_MI_IN2_NAME)
#define PIN_MI_IN2   def_pin_reg(PORT_MI_IN2_NAME)
#define DDR_MI_IN2   def_ddr_reg(PORT_MI_IN2_NAME)

/* Motor Derecho  -- Timer 1 */
/*MD_1 = Motor Right IN1*/
#define PORT_MD_IN1_NAME  B
#define MD_IN1_NUMBER     2
/*MD_2 = Motor Right IN2*/
#define PORT_MD_IN2_NAME  B
#define MD_IN2_NUMBER     1

#define PORT_MD_IN1  def_port_reg(PORT_MD_IN1_NAME)
#define PIN_MD_IN1   def_pin_reg(PORT_MD_IN1_NAME)
#define DDR_MD_IN1   def_ddr_reg(PORT_MD_IN1_NAME)

#define PORT_MD_IN2  def_port_reg(PORT_MD_IN2_NAME)
#define PIN_MD_IN2   def_pin_reg(PORT_MD_IN2_NAME)
#define DDR_MD_IN2   def_ddr_reg(PORT_MD_IN2_NAME)


#define TMR0MASKON   ( (0<<CS02) | (0<<CS01) | (1<<CS00) )
#define TMR1MASKON   ( (0<<CS12) | (0<<CS11) | (1<<CS10) )
#define TMR0MASKOFF ~( (1<<CS02) | (1<<CS01) | (1<<CS00) )
#define TMR1MASKOFF ~( (1<<CS12) | (1<<CS11) | (1<<CS10) )

/* ------------------------------------------------------ */

#define VEL_DETENIDO   0x80
#define VEL_ADELANTE   0xC0
#define VEL_ATRAS      0x40

void ConfigurarMotores(void);
void ApagarMotores(void);
void EncenderMotores(void);
void Detener(void);
void MoverAdelante(void);
void MoverAtras(void);
void GirarIzquierda(void);
void GirarDerecha(void);  

static inline void vel_motor_derecho(const unsigned char temp) {
  OCR1AL = temp;
  OCR1BL = temp;
}

static inline void vel_motor_izquierdo(const unsigned char temp) {
  OCR0A = temp;
  OCR0B = temp;
}


#endif

