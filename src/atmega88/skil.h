#ifndef _SKIL_H_
#define _SKIL_H_

/* Definiciones correspondientes a los pulsadores */

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

/* ----------------------------------------------------- */
#define CANT_REPETICIONES 10

typedef enum {
	FIGHT,
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
void accionFight(void);
void accionTracking(void);
void accionAdelanteDer(void);
void accionAdelanteIzq(void);
void accionAtrasDer(void);
void accionAtrasIzq(void);
void accionAtrasInf(void);
void accionAdelanteInf(void);

#endif
