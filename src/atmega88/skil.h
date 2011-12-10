#ifndef _SKIL_H_
#define _SKIL_H_

/* Definiciones correspondientes a los pulsadores */

/* INT_ARRANQUE = Pulsador de Arranque */
#define PORT_PULSADOR_NAME   C
#define PULSADOR_NUMBER      1

#define PORT_SOLENOIDE_NAME   C
#define SOLENOIDE_NUMBER      2

#define PORT_PULSADOR  def_port_reg(PORT_PULSADOR_NAME)
#define PIN_PULSADOR   def_pin_reg(PORT_PULSADOR_NAME)
#define DDR_PULSADOR   def_ddr_reg(PORT_PULSADOR_NAME)

#define PORT_SOLENOIDE  def_port_reg(PORT_SOLENOIDE_NAME)
#define PIN_SOLENOIDE  def_pin_reg(PORT_SOLENOIDE_NAME)
#define DDR_SOLENOIDE   def_ddr_reg(PORT_SOLENOIDE_NAME)



/*LED1 = LED 1 (Verde)*/
#define PORT_LED1_NAME	C
#define LED1_NUMBER	    5

#define PORT_LED1     def_port_reg(PORT_LED1_NAME)
#define PIN_LED1      def_pin_reg(PORT_LED1_NAME)
#define DDR_LED1      def_ddr_reg(PORT_LED1_NAME)

#define Led1Init()  SetBit(DDR_LED1, LED1_NUMBER)

#define Led1On()    SetBit(PORT_LED1, LED1_NUMBER)
#define Led1Off()   ClearBit(PORT_LED1, LED1_NUMBER)

#define IsLed1On()    IsBitSet(PORT_LED1, LED1_NUMBER)
#define Led1Toggle()  {if ( IsLed1On() ) Led1Off(); else Led1On();}

/* Macros */
// Se setea como entrada y se pone el pin en '1'. Esto último hace que se 
// active el pull-up interno
#define PulsadorInit()  {ClearBit(DDR_PULSADOR, PULSADOR_NUMBER); SetBit(PORT_PULSADOR, PULSADOR_NUMBER);}

// lee el pin del boton de arranque
#define IsPulsadorSet()   IsBitSet(PIN_PULSADOR, PULSADOR_NUMBER)

/* ----------------------------------------------------- */
#define CANT_REPETICIONES 10

typedef enum {
	FIGHT_ADELANTE,
  FIGHT_ATRAS,
	TRACKING,
	DETENIDO
} estados;

typedef enum {
	ADELANTE_DER,
	ADELANTE_IZQ,
	ATRAS_DER,
	ATRAS_IZQ,
	ATRAS,
	ADELANTE,
	OK
} estadosInf;

typedef enum {
	GIRANDO_DERECHA,
	GIRANDO_IZQUIERDA,
	ADELANTANDO,
	ATRAZANDO
} estadosTracking;

void setearSensoresInf(void);
void configurarPulsador(void);
void movimientoPrueba(void);
void accionFightAdelante(void);
void accionFightAtras(void);
void accionTracking(void);
void accionAdelanteDer(void);
void accionAdelanteIzq(void);
void accionAtrasDer(void);
void accionAtrasIzq(void);
void accionAtrasInf(void);
void accionAdelanteInf(void);
void activarSolenoide(void);
void configurarSolenoide(void);

#endif
