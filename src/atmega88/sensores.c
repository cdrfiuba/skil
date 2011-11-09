#include "definiciones.h"
#include "sensores.h"

void configurarPinSensoresSup () {
	SetBit(DDR_EAD, EAD_NUMBER);
	ClearBit(PORT_EAD, EAD_NUMBER);
	SetBit(DDR_EAT, EAT_NUMBER);
	ClearBit(PORT_EAT, EAT_NUMBER);
}

void configurarTimerSensoresSup () {
	// Se configura el timer 2 en modo CTC segun las definiciones del .h

	TCCR2A = (0<<COM2A1)|(0<<COM2A0)|(0<<COM2B1)|(0<<COM2B0)|(1<<WGM21)|(0<<WGM20);
	TCCR2B = (0<<WGM22);
	
	#if PRESCALER_EMISORES_SUP == 1
		ClearBit(TCCR2B, CS22);
		ClearBit(TCCR2B, CS21);
		SetBit(TCCR2B, CS20);
	#elif PRESCALER_EMISORES_SUP == 8
		ClearBit(TCCR2B, CS22);
		SetBit(TCCR2B, CS21);
		ClearBit(TCCR2B, CS20);
	#elif PRESCALER_EMISORES_SUP == 32
		ClearBit(TCCR2B, CS22);
		SetBit(TCCR2B, CS21);
		SetBit(TCCR2B, CS20);
	#elif PRESCALER_EMISORES_SUP == 64
		SetBit(TCCR2B, CS22);
		ClearBit(TCCR2B, CS21);
		ClearBit(TCCR2B, CS20);
	#elif PRESCALER_EMISORES_SUP == 128
		SetBit(TCCR2B, CS22);
		ClearBit(TCCR2B, CS21);
		SetBit(TCCR2B, CS20);
	#elif PRESCALER_EMISORES_SUP == 256
		SetBit(TCCR2B, CS22);
		SetBit(TCCR2B, CS21);
		ClearBit(TCCR2B, CS20);
	#elif PRESCALER_EMISORES_SUP == 1024
		SetBit(TCCR2B, CS22);
		SetBit(TCCR2B, CS21);
		SetBit(TCCR2B, CS20);
	#else
		ClearBit(TCCR2B, CS22);
		ClearBit(TCCR2B, CS21);
		ClearBit(TCCR2B, CS20);
	#endif	

	TCNT2 = 0;
	OCR2A = OCR_EMISORES_SUP;

	// CTC esta con OCR2A
	TIMSK2 = (0<<OCIE2B)|(1<<OCIE2A)|(0<<TOIE2);
}

void configurarPinSensoresInf(){
	// Configuro los leds de los sensores en salida
	SetBit(DDR_EP, EP_NUMBER);
	SetBit(PORT_EP, EP_NUMBER);

	// Configuro todos los sensores en entrada sin pull-up
	ClearBit(DDR_RPA, RPA_NUMBER);
	SetBit(PORT_RPA, RPA_NUMBER);
	ClearBit(DDR_RPB, RPB_NUMBER);
	SetBit(PORT_RPB, RPB_NUMBER);
	ClearBit(DDR_RPC, RPC_NUMBER);
	SetBit(PORT_RPC, RPC_NUMBER);
	ClearBit(DDR_RPD, RPD_NUMBER);
	SetBit(PORT_RPD, RPD_NUMBER);

	PCICR |= (1<<PCIE2)|(1<<PCIE0);
	PCMSK2 = (1<<PCINT23);
	PCMSK0 = (1<<PCINT7)|(1<<PCINT6)|(1<<PCINT0);
}
