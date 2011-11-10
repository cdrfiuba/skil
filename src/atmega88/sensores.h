#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <avr/io.h>
#include "definiciones.h"

/*-----------------------------------------------*/
/* Definiciones de los pines correspondientes a los sensores */
// Defino las mascaras para la interrupcion
//#define MASK_INT_SENSA	(~(1<<PB7))
#define MASK_INT_SENSA	0x7F
//#define MASK_INT_SENSB	(~(1<<PB6))
#define MASK_INT_SENSB	0xBF
//#define MASK_INT_SENSC	(~((1<<PD7)>>2))
#define MASK_INT_SENSC	0x7F
//#define MASK_INT_SENSD	(~(1<<PB0))
#define MASK_INT_SENSD	0xFE	
//#define MASK_INT_PORT (~((1<<PB7)|(1<<PB6)|(1<<PB0)))
#define MASK_INT_PORT 0x3E

/* Sensores Inferiores */
/*EP = Emisor Piso*/
#define PORT_EP_NAME B
#define EP_NUMBER    3

/*RPA = Receptor Piso A*/
#define PORT_RPA_NAME B
#define RPA_NUMBER    7

/*RPB = Receptor Piso B*/
#define PORT_RPB_NAME B
#define RPB_NUMBER    6

/*RPC = Receptor Piso C*/
#define PORT_RPC_NAME D
#define RPC_NUMBER    7

/*RPD = Receptor Piso D*/
#define PORT_RPD_NAME B
#define RPD_NUMBER    0

#define PORT_EP  def_port_reg(PORT_EP_NAME)
#define PIN_EP   def_pin_reg(PORT_EP_NAME)
#define DDR_EP   def_ddr_reg(PORT_EP_NAME)

#define PORT_RPA  def_port_reg(PORT_RPA_NAME)
#define PIN_RPA   def_pin_reg(PORT_RPA_NAME)
#define DDR_RPA   def_ddr_reg(PORT_RPA_NAME)

#define PORT_RPB  def_port_reg(PORT_RPB_NAME)
#define PIN_RPB   def_pin_reg(PORT_RPB_NAME)
#define DDR_RPB   def_ddr_reg(PORT_RPB_NAME)

#define PORT_RPC  def_port_reg(PORT_RPC_NAME)
#define PIN_RPC   def_pin_reg(PORT_RPC_NAME)
#define DDR_RPC   def_ddr_reg(PORT_RPC_NAME)

#define PORT_RPD  def_port_reg(PORT_RPD_NAME)
#define PIN_RPD   def_pin_reg(PORT_RPD_NAME)
#define DDR_RPD   def_ddr_reg(PORT_RPD_NAME)


/* Sensores Superiores */
/*EAD = Emisor Adelante*/
#define PORT_EAD_NAME D
#define EAD_NUMBER    4

/*EAT = Emisor Atras*/
#define PORT_EAT_NAME B
#define EAT_NUMBER    4

/*RAD = Receptor Adelante*/
#define PORT_RAD_NAME D
#define RAD_NUMBER    2

/*RAT = Receptor Atras*/
#define PORT_RAT_NAME D
#define RAT_NUMBER    3

#define PORT_EAD  def_port_reg(PORT_EAD_NAME)
#define PIN_EAD   def_pin_reg(PORT_EAD_NAME)
#define DDR_EAD   def_ddr_reg(PORT_EAD_NAME)

#define PORT_EAT  def_port_reg(PORT_EAT_NAME)
#define PIN_EAT   def_pin_reg(PORT_EAT_NAME)
#define DDR_EAT   def_ddr_reg(PORT_EAT_NAME)

#define PORT_RAD  def_port_reg(PORT_RAD_NAME)
#define PIN_RAD  def_pin_reg(PORT_RAD_NAME)
#define DDR_RAD   def_ddr_reg(PORT_RAD_NAME)

#define PORT_RAT  def_port_reg(PORT_RAT_NAME)
#define PIN_RAT   def_pin_reg(PORT_RAT_NAME)
#define DDR_RAT   def_ddr_reg(PORT_RAT_NAME)

/* ----------------------------------------------------------------- */

#define PRESCALER_EMISORES_SUP		1
#define OCR_EMISORES_SUP			97
#define CANT_PULSOS_ALTO_EM_SUP		50
#define CANT_PULSOS_BAJO_EM_SUP		255
#define  A1ON   0
#define  A2ON   1
#define  B1ON   2
#define  B2ON   3
#define  C1ON   4
#define  C2ON   5


#define OPONENTE_ADELANTE 1
#define OPONENTE_ATRAS    2
#define OPONENTE_AI       3  //ADELANTE IZQUIERDA
#define OPONENTE_AD       4  //ADELANTE DERECHA
#define OPONENTE_TI       5  //ATRAS IZQUIERDA
#define OPONENTE_TD       6  //ATRAS DERECHA
#define ME_CAIGO          7

extern int estado_anterior;
extern int estado_actual;
extern int estado_sensores;
extern int pulso1;
extern int pulso2;

void sensores_update(void);
void estado_actual_update(void);
void portadora1_tick();
void modulacion1_tick();
void portadora2_tick();
void modulacion2_tick();

void configurar_ojitos();

void emisor1_sup_on(void);
void emisor1_sup_off(void);
void emisor2_sup_on(void);
void emisor2_sup_off(void);

void emisores_superior_on();

void emisor_inf_on(void);
void emisor_inf_off(void);
int sensor_prendido(int num);


#define SALIENDO_LINEA    170

extern volatile unsigned char analogSD;
extern volatile unsigned char analogSI;

void configurar_adc();
void leer_sensores_adc();

void configurarPinSensoresSup (void);
void configurarTimerSensoresSup (void);
void configurarPinSensoresInf(void);
#endif
