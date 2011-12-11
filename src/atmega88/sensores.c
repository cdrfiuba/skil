#include <avr/interrupt.h>

// solo para usar estado en la interrupcion de sensores inferiores
// deberiamos eviatar usar el estado global
//#include "skil.h"

#include "sensores.h"

volatile uint8_t contPulsosEmSup;
volatile uint8_t flagVisto;

volatile estadosInf estadoInf;
//volatile uint8_t sensoresInf;

void configurarPinSensoresSup () {
	SetBit(DDR_EAD, EAD_NUMBER);
	ClearBit(PORT_EAD, EAD_NUMBER);
	
  ClearBit(DDR_RAD, RAD_NUMBER);
	SetBit(PORT_RAD, RAD_NUMBER);
	
  EICRA = (1<<ISC01) | (0<<ISC00);
  EIMSK = (1<<INT0);
}

void configurarTimerSensoresSup () {
	// Se configura el timer 2 en modo CTC segun las definiciones del .h

	TCCR2A = (0<<COM2A1)|(0<<COM2A0)|(0<<COM2B1)|(0<<COM2B0)|(1<<WGM21)|(0<<WGM20);
	TCCR2B = (0<<WGM22);
	
	TCNT2 = 0;
	OCR2A = OCR_EMISORES_SUP;

  contPulsosEmSup = 0;
  flagVisto = 0;

	// CTC esta con OCR2A
	TIMSK2 = (0<<OCIE2B)|(1<<OCIE2A)|(0<<TOIE2);
}

void encenderEmisorSuperior(){
    TCCR2B &= ~((1<<CS22)|(1<<CS21)|(1<<CS20));
	#if PRESCALER_EMISORES_SUP == 1
    TCCR2B |= ((0<<CS22)|(0<<CS21)|(1<<CS20));
	#elif PRESCALER_EMISORES_SUP == 8
    TCCR2B |= ((0<<CS22)|(1<<CS21)|(0<<CS20));
	#elif PRESCALER_EMISORES_SUP == 32
    TCCR2B |= ((0<<CS22)|(1<<CS21)|(1<<CS20));
	#elif PRESCALER_EMISORES_SUP == 64
    TCCR2B |= ((1<<CS22)|(0<<CS21)|(0<<CS20));
	#elif PRESCALER_EMISORES_SUP == 128
    TCCR2B |= ((1<<CS22)|(0<<CS21)|(1<<CS20));
	#elif PRESCALER_EMISORES_SUP == 256
    TCCR2B |= ((1<<CS22)|(1<<CS21)|(0<<CS20));
	#elif PRESCALER_EMISORES_SUP == 1024
    TCCR2B |= ((1<<CS22)|(1<<CS21)|(1<<CS20));
  #else
    #warning Error en el prescaler del timer 2. Ver sensores.h
	#endif
}


void configurarPinSensoresInf(){
	// Configuro los leds de los sensores en salida
	SetBit(DDR_EP, EP_NUMBER);
  apagarEmisorInferior();

	// Configuro todos los sensores en entrada sin pull-up
	ClearBit(DDR_RPA, RPA_NUMBER);
	SetBit(PORT_RPA, RPA_NUMBER);
	ClearBit(DDR_RPB, RPB_NUMBER);
	SetBit(PORT_RPB, RPB_NUMBER);
	ClearBit(DDR_RPC, RPC_NUMBER);
	SetBit(PORT_RPC, RPC_NUMBER);
	ClearBit(DDR_RPD, RPD_NUMBER);
	SetBit(PORT_RPD, RPD_NUMBER);

	estadoInf = OK;

	PCICR |= (1<<PCIE0);
	PCMSK0 = (1<<PCINT7)|(1<<PCINT6)|(1<<PCINT4)|(1<<PCINT0);
}


// Interrupcion para generar el pulso de emisor infrarrojo superior (vector_7)
ISR(TIMER2_COMPA_vect){
	// Cuando se da la comparacion cambio el estado del pin solo si estoy en alto
	// Hay una variable global que me dice si estoy en alto o en bajo
	contPulsosEmSup++;
	if(contPulsosEmSup <= (2*CANT_PULSOS_ALTO_EM_SUP))
    SetBit(PIN_EAD, EAD_NUMBER);
}


// Interrupcion receptor superior (vector_1)
ISR(INT0_vect){
//  estado = FIGHT_ADELANTE;
  flagVisto = 1;
}


// Interrupcion de sensores inferiores (vector_3)
ISR(PCINT0_vect) {
  estadoInf = PINB & MASK_INT_PIN_ALL;

  // no se si borraria este flag (AB)
//  PCIFR |= (1<<PCIF0);
}

