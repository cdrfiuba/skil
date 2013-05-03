#ifndef _SENSORES_H_
#define _SENSORES_H_

#include <avr/io.h>
#include "definiciones.h"
#include "skil.h"

/*-----------------------------------------------*/
/* Definiciones de los pines correspondientes a los sensores */

/* Sensores Inferiores */
/*EP = Emisor Piso*/
#define PORT_EP_NAME B
#define EP_NUMBER    3

/*RPA = Receptor Piso A  Adelante izquierda*/
#define PORT_RPA_NAME B
#define RPA_NUMBER    7

/*RPB = Receptor Piso B  Adelante derecha*/
#define PORT_RPB_NAME B
#define RPB_NUMBER    6

/*RPC = Receptor Piso C  Atras izquierda*/
#define PORT_RPC_NAME B
#define RPC_NUMBER    4

/*RPD = Receptor Piso D  Atras derecha*/
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

/*RAD = Receptor Adelante*/
#define PORT_RAD_NAME D
#define RAD_NUMBER    2


#define PORT_EAD  def_port_reg(PORT_EAD_NAME)
#define PIN_EAD   def_pin_reg(PORT_EAD_NAME)
#define DDR_EAD   def_ddr_reg(PORT_EAD_NAME)

#define PORT_RAD  def_port_reg(PORT_RAD_NAME)
#define PIN_RAD  def_pin_reg(PORT_RAD_NAME)
#define DDR_RAD   def_ddr_reg(PORT_RAD_NAME)

#define MASK_INT_PIN_ALL (uint8_t)((1<<RPA_NUMBER)|(1<<RPB_NUMBER)|(1<<RPC_NUMBER)|(1<<RPD_NUMBER))

// Defino las mascaras para la interrupcion
// El color del tatami se define en el Makefile
#if defined TATAMI_NEGRO
  #define MASK_INT_OK     MASK_INT_PIN_ALL
  #define MASK_INT_SENSA	(uint8_t)(~(1<<RPA_NUMBER)) // 0x7F
  #define MASK_INT_SENSB	(uint8_t)(~(1<<RPB_NUMBER)) // 0xBF
  #define MASK_INT_SENSAD (uint8_t)(~((1<<RPA_NUMBER)|(1<<RPB_NUMBER))) // 0x3F
  #define MASK_INT_SENSC	(uint8_t)(~(1<<RPC_NUMBER)) // 0xEF
  #define MASK_INT_SENSD	(uint8_t)(~(1<<RPD_NUMBER)) // 0xFE
  #define MASK_INT_SENSAT (uint8_t)(~((1<<RPC_NUMBER)|(1<<RPD_NUMBER))) // 0xEE
  #define MASK_INT_SENSDER (uint8_t)(~((1<<RPB_NUMBER)|(1<<RPD_NUMBER))) // 0xEE
  #define MASK_INT_SENSIZQ (uint8_t)(~((1<<RPC_NUMBER)|(1<<RPA_NUMBER))) // 0xEE
#elif defined TATAMI_BLANCO
  #define MASK_INT_OK     ~MASK_INT_PIN_ALL
  #define MASK_INT_SENSA	(uint8_t)(1<<RPA_NUMBER) // 0x80
  #define MASK_INT_SENSB	(uint8_t)(1<<RPB_NUMBER) // 0x40
  #define MASK_INT_SENSAD (uint8_t)((1<<RPA_NUMBER)|(1<<RPB_NUMBER)) // 0xC0
  #define MASK_INT_SENSC	(uint8_t)(1<<RPC_NUMBER) // 0x10
  #define MASK_INT_SENSD	(uint8_t)(1<<RPD_NUMBER) // 0x01
  #define MASK_INT_SENSAT (uint8_t)((1<<RPC_NUMBER)|(1<<RPD_NUMBER)) // 0x11
  #define MASK_INT_SENSDER (uint8_t)((1<<RPB_NUMBER)|(1<<RPD_NUMBER)) // 0x11
  #define MASK_INT_SENSIZQ (uint8_t)((1<<RPC_NUMBER)|(1<<RPA_NUMBER)) // 0x11
#else
  #error TATAMI NO DEFINIDO
#endif

/* ----------------------------------------------------------------- */

#define CNT1_INI 0x3000
#define PRESCALER_EMISORES_SUP   1
// Top del timer para generar cuadrada de 40khz
// Con 100 anda bien
// Con 140 tiene 5 cm de alcance y sirve para hacer pruebas
#define OCR_EMISORES_SUP         100
#define CANT_PULSOS_ALTO_EM_SUP  25 // despues se multiplica por dos, para generar los dos flancos del pulso

typedef enum {
	OK = MASK_INT_OK & MASK_INT_PIN_ALL,
	ADELANTE = MASK_INT_SENSAD & MASK_INT_PIN_ALL,
	ATRAS = MASK_INT_SENSAT & MASK_INT_PIN_ALL,
	ADELANTE_DER = MASK_INT_SENSB & MASK_INT_PIN_ALL,
	ADELANTE_IZQ = MASK_INT_SENSA & MASK_INT_PIN_ALL,
	ATRAS_DER = MASK_INT_SENSD & MASK_INT_PIN_ALL,
	ATRAS_IZQ = MASK_INT_SENSC & MASK_INT_PIN_ALL,
  DERECHA = MASK_INT_SENSDER & MASK_INT_PIN_ALL,
  IZQUIERDA = MASK_INT_SENSIZQ & MASK_INT_PIN_ALL
} estadosInf_t;

extern volatile estadosInf_t sensoresInf;

extern volatile uint8_t flagVisto;
//extern int estado_anterior;
//extern int estado_actual;
//extern int estado_sensores;


//void sensores_update(void);
//void estado_actual_update(void);

void configurar_ojitos();

void encenderEmisorSuperior();

#define encenderEmisorInferior()   SetBit(PORT_EP, EP_NUMBER);
#define apagarEmisorInferior()     ClearBit(PORT_EP, EP_NUMBER);

void configurarPinSensoresSup (void);
void configurarTimerSensoresSup (void);
void configurarTimerEstados(void);
void configurarPinSensoresInf(void);

#endif
