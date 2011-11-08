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

typedef enum {
	FIGHT,
	SALIENDO_DER,
	SALIENDO_IZQ,
	AFUERA_DER,
	AFUERA_IZQ,
	TRACKING,
	DETENIDO 
} estados;

void configurarPulsador(void);
void movimientoPrueba(void);
#endif
