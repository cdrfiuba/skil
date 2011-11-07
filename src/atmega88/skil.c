#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "skil.h"

volatile unsigned char estado;

// Variable de estado de los emisores superiores
// Varia entre 0 y CANT_PULSOS_ALTO_EM_SUP + CANT_PULSOS_BAJO_EM_SUP
volatile uint16_t contPulsosEmSup;

void configurarPulsador(void);
void setup(void);
unsigned char actualizar_estado(void);
void actuar(void);

int main (void) {
	contPulsosEmSup=0;
	setup();
	while(1){
		leer_sensores_adc();
		if(estado != DETENIDO){
			estado = actualizar_estado();
			actuar();
		}
	}
}

void setup (void) {
  configurar_motores();
  configurar_adc();
  configurarPulsador();
  Led1Init();
  estado = DETENIDO;
  configurarPinSensoresSup();
  configurarTimerSensoresSup();
  sei();
}

unsigned char actualizar_estado(void) {
//  if (estado == DETENIDO)
//      return DETENIDO;

  if((analogSI < SALIENDO_LINEA) && (analogSD < SALIENDO_LINEA))
    return EN_LINEA;

  if((analogSI >= SALIENDO_LINEA) && (analogSD >= SALIENDO_LINEA)){
    if ( (estado == SALIENDO_DER) || (estado == AFUERA_DER))
      return AFUERA_DER;
    if ( (estado == SALIENDO_IZQ) || (estado == AFUERA_IZQ))
      return AFUERA_IZQ;
  }

  if((analogSI >= SALIENDO_LINEA) && (analogSD < SALIENDO_LINEA))
    return SALIENDO_IZQ;

  if((analogSD >= SALIENDO_LINEA) && (analogSI < SALIENDO_LINEA))
    return SALIENDO_DER;
  
  return DETENIDO; /* no deberia llegar aca */
}

/*
void actuar (void) {
  switch(estado){
    case EN_LINEA:
      Led1Toggle();
      _delay_ms(20);
      break;
    case SALIENDO_IZQ:
      Led1Toggle();
      _delay_ms(10);
      break;
    case SALIENDO_DER:
      Led1Toggle();
      _delay_ms(30);
      break;
    case AFUERA_IZQ:
      Led1Toggle();
      _delay_ms(5);
      break;
    case AFUERA_DER:
      Led1Toggle();
      _delay_ms(35);
      break;
    case DETENIDO:
    default: 
      break;
  }
}
*/
void actuar (void) {
  switch(estado){
    case EN_LINEA:
      avanzar();
      break;
    case SALIENDO_IZQ:
      correccion_suave_izq();
      break;
    case SALIENDO_DER:
      correccion_suave_der();
      break;
    case AFUERA_IZQ:
      correccion_fuerte_izq();
      break;
    case AFUERA_DER:
      correccion_fuerte_der();
      break;
    case DETENIDO:
    default: 
      break;
  }
}

void configurarPulsador(void){
	PulsadorInit();
	// Configuracion de modo de interrupcion (pagina 73)
	// EICRA |= ((0<<ISC11) | (0<<ISC10)); // Nivel bajo. 
	// EICRA |= ((0<<ISC11) | (1<<ISC10)); // Cualquier cambio de nivel
	// EICRA |= ((1<<ISC11) | (0<<ISC10)); // Flanco descendente 
	EICRA |= ((1<<ISC11) | (1<<ISC10)); // Flanco ascendente.

	// Esto habilita la interrupción INT1 escribiendo un '1' en el bit INT1
	// de la mascara de interrupciones externas
	SetBit(EIMSK, INT1); 
}

ISR(INT1_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);

  if (IsPulsadorSet()==true) { 
		// significa que esta en 1 y hubo flanco ascendente genuino
		// se podria reemplazar la variable por poner apagar todo, poner 
		// el micro a dormir esperando solo esta interrupcion y luego
		// despertalo. Aca se lo despertaria
    if (estado == DETENIDO) {
      estado = EN_LINEA;
      EncenderMotores();
    }
    else {
      estado = DETENIDO;
      ApagarMotores();
    }
	}
}


ISR(TIMER2_COMPA_vect){
	// Cuando se da la comparacion cambio el estado del pin solo si estoy en alto
	// Hay una variable global que me dice si estoy en alto o en bajo
	contPulsosEmSup++;
	if(contPulsosEmSup <= CANT_PULSOS_ALTO_EM_SUP){
		if(IsBitSet(PORT_EAD, EAD_NUMBER)){
			ClearBit(PORT_EAD, EAD_NUMBER);
		} else {
			SetBit(PORT_EAD, EAD_NUMBER);
		}
		if(IsBitSet(PORT_EAT, EAT_NUMBER)){
			ClearBit(PORT_EAT, EAT_NUMBER);
		} else {
			SetBit(PORT_EAT, EAT_NUMBER);
		}
	}else if((contPulsosEmSup >= CANT_PULSOS_ALTO_EM_SUP)&&(contPulsosEmSup <=
	CANT_PULSOS_ALTO_EM_SUP+CANT_PULSOS_BAJO_EM_SUP )){
		ClearBit(PORT_EAD, EAD_NUMBER);
		ClearBit(PORT_EAT, EAT_NUMBER);
	}else{
		contPulsosEmSup=0;
	}
}

