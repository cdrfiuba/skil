#ifndef _SKIL_H_
#define _SKIL_H_

/* INT_ARRANQUE = Pulsador de Arranque */
#define PORT_PULSADOR_NAME   C
#define PULSADOR_NUMBER      1

#define PORT_PULSADOR  def_port_reg(PORT_PULSADOR_NAME)
#define PIN_PULSADOR   def_pin_reg(PORT_PULSADOR_NAME)
#define DDR_PULSADOR   def_ddr_reg(PORT_PULSADOR_NAME)

/* Macros */
// Se setea como entrada y se pone el pin en '1'. Esto último hace que se 
// active el pull-up interno
#define PulsadorInit()  {ClearBit(DDR_PULSADOR, PULSADOR_NUMBER); SetBit(PORT_PULSADOR, PULSADOR_NUMBER);}

// lee el pin del boton de arranque
#define IsPulsadorSet()   IsBitSet(PIN_PULSADOR, PULSADOR_NUMBER)


/* Solenoide */
#define PORT_SOLENOIDE_NAME   C
#define SOLENOIDE_NUMBER      2

#define PORT_SOLENOIDE  def_port_reg(PORT_SOLENOIDE_NAME)
#define PIN_SOLENOIDE  def_pin_reg(PORT_SOLENOIDE_NAME)
#define DDR_SOLENOIDE   def_ddr_reg(PORT_SOLENOIDE_NAME)

/* Macros */
#define configurarSolenoide()    SetBit(DDR_SOLENOIDE, SOLENOIDE_NUMBER)
#define energizarSolenoide()     SetBit(PORT_SOLENOIDE, SOLENOIDE_NUMBER)
#define desenergizarSolenoide()  ClearBit(PORT_SOLENOIDE, SOLENOIDE_NUMBER)


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
//#define Led1Toggle()  {if ( IsLed1On() ) Led1Off(); else Led1On();}
#define Led1Toggle()  SetBit(PIN_LED1, LED1_NUMBER)

/* ----------------------------------------------------- */

typedef enum {
	FIGHT_ADELANTE,
	TRACKING,
	DETENIDO
} estados_t;

typedef enum {
	GIRANDO_DERECHA,
	GIRANDO_IZQUIERDA,
	ADELANTANDO,
	ATRAZANDO
} estadosTracking_t;


//extern volatile estados_t estado;

/* prototipos de funciones usadas en skil.c */

void configurarPulsador(void);
void setup(void);
void accionTracking(void);

/* prototipos de funciones de prueba */
void movimientoPrueba(void);
void titilarLed(uint8_t numero);
#endif
