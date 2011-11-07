#include "definiciones.h"
#include "sensores.h"

volatile unsigned char analogSD;
volatile unsigned char analogSI;

void configurar_adc() {
  ClearBit(ADMUX, REFS1);  // Agregado para que el ADC use referencia inteAVCCC
  SetBit(ADMUX, REFS0);    // Idem
  SetBit(ADMUX, ADLAR);    // Queremos Left-Adjusted (ver pagina 267)
  ADCPrescalerSelec(2);
	ClearBit(ADCSRA, ADIE);
  SetBit(ADCSRA, ADEN);
}

void leer_sensores_adc() {
  ADSeleccionarCanal(ADC_NUM_SD);
  IniciarConversion();
  while (IsBitSet(ADCSRA,ADIF)==false);
  SetBit(ADCSRA,ADIF);
  analogSD = ADCH;

  ADSeleccionarCanal(ADC_NUM_SI);
  IniciarConversion();
  while (IsBitSet(ADCSRA,ADIF)==false);
  SetBit(ADCSRA,ADIF);
  analogSI = ADCH;
}

void configurarPinSensoresSup () {
	SetBit(DDR_EAD, EAD_NUMBER);
	ClearBit(DDR_EAD, EAD_NUMBER);
	SetBit(DDR_EAT, EAT_NUMBER);
	ClearBit(DDR_EAT, EAT_NUMBER);
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
	OCR2A = OCR_EMISOR_SUP;

	// CTC esta con OCR2A
	TIMSK = (0<<OCIE2B)|(1<<OCIE2A)|(0<<TOIE2);
}
