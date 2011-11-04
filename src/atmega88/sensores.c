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

