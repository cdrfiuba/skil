#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "skil.h"

volatile estados estado;

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
		switch(estado){
			case FIGHT:
			case TRACKING:
				//accionTracking();
				movimientoPrueba();
				break;
		    case ADELANTE_DER:
				MoverAdelante();
				break;
		    case ADELANTE_IZQ:
				GirarIzquierda();
				break;
		    case ATRAS_DER:
				GirarDerecha();
				break;
		    case ATRAS_IZQ:
				MoverAtras();
				break;
		    case DETENIDO:
		    default: 
				ApagarMotores();
				break;
		}
	}
}

void setup (void) {
	ConfigurarMotores();
	configurarPinSensoresSup();
	configurarTimerSensoresSup();
	configurarPulsador();
	estado = DETENIDO;
	sei();
}

void movimientoPrueba(void){
	MoverAdelante();
	_delay_ms(1000);
	MoverAtras();
	_delay_ms(1000);
	GirarIzquierda();
	_delay_ms(1000);
	GirarDerecha();
	_delay_ms(1000);
}

void actuar (void) {
  switch(estado){
    case FIGHT:
    case TRACKING:
      //accionTracking();
	  movimientoPrueba();
      break;
    case ADELANTE_DER:
	  MoverAdelante();
      break;
    case ADELANTE_IZQ:
	  GirarIzquierda();
      break;
    case ATRAS_DER:
	  GirarDerecha();
      break;
    case ATRAS_IZQ:
	  MoverAtras();
      break;
    case DETENIDO:
    default: 
	  ApagarMotores();
      break;
  }
}

void configurarPulsador(void){
	PulsadorInit();
	// Configuro el pin change
	PCICR |= (1<<PCIE1);
	PCMSK1 |= (1<<PCINT9);
}
ISR(PCINT2_vect) {
	sensoresInf &= ((PIN_RPC>>2) | MASK_INT_SENSC);
}

ISR(PCINT0_vect) {
	sensoresInf &= PIN_RPA;
}

void setearSensoresInf(sensoresInf){
	switch(aux | MASK_INT_PORT){
		case MASK_INT_SENSA: 
			estado = ADELANTE_IZQ;
			break;
		case MASK_INT_SENSB: 
			estado = ADELANTE_DER;
			break;
		case MASK_INT_SENSD: 
			estado = ATRAS_DER;
			break;
		case (MASK_INT_SENSA & MASK_INT_SENSB): 
			estado = ADELANTE_INF;
			break;
	asdasdasd
			estado = ATRAS_IZQ;
		default:
			break;
	}
}

ISR(PCINT1_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);

	if (IsPulsadorSet()==false) { 
		// significa que esta en 1 y hubo flanco ascendente genuino
		// se podria reemplazar la variable por poner apagar todo, poner 
		// el micro a dormir esperando solo esta interrupcion y luego
		// despertalo. Aca se lo despertaria
		if (estado == DETENIDO) {
			estado = TRACKING;
		}
		else {
			estado = DETENIDO;
		}
	}
}


ISR(TIMER2_COMPA_vect){
	// Cuando se da la comparacion cambio el estado del pin solo si estoy en alto
	// Hay una variable global que me dice si estoy en alto o en bajo
	contPulsosEmSup++;
	if(contPulsosEmSup <= CANT_PULSOS_ALTO_EM_SUP){
		SetBit(PIN_EAD, EAD_NUMBER);
		SetBit(PIN_EAT, EAT_NUMBER);
	}else if((contPulsosEmSup >= CANT_PULSOS_ALTO_EM_SUP)&&(contPulsosEmSup <=
	CANT_PULSOS_ALTO_EM_SUP+CANT_PULSOS_BAJO_EM_SUP )){
		ClearBit(PORT_EAD, EAD_NUMBER);
		ClearBit(PORT_EAT, EAT_NUMBER);
	}else{
		contPulsosEmSup=0;
	}
}
