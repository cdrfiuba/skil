#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "skil.h"

#define DELAY_ESTADO    5 // en milisegundos
#define DELAY_ESCAPE    500 // en milisegundos
#define DELAY_INICIO    1000 // en milisegundos 5200
#define ALEATOREO_DELAY   500

// la macro 
#define proximoEstadoAleatorio() (TCNT2 & 0x03) //Devuelve un numero aleatorio entre 0 y 3
#define ALEATOREO_MAX_CUENTA   ALEATOREO_DELAY/DELAY_ESTADO

volatile estados estado;

// utilizado para definir la cantidad de repeticion de la misma accion aleatorea
// (ver accionTracking )
volatile uint8_t cantVeces;

int main (void) {
	setup();

  while (estado == DETENIDO);
  //tiempo de espera para bajar pollera
  _delay_ms(DELAY_INICIO);

  // la pollera no la estamos usando, pero mejor desconectarla
  // el solenoide no puede que
  desenergizarSolenoide();
  
  encenderEmisorSuperior();
  encenderEmisorInferior();

	while(1){
    if (IsnFaultSet()==0) {
      titilarLed(20);
      ConfigurarMotores();
      EncenderMotores();
      MoverAdelante();
    }
    if (flagVisto==1) {
      estado = FIGHT_ADELANTE;
      flagVisto = 0;
    }
    
    estadoInf = PINB & MASK_INT_PIN_ALL;

    switch (estadoInf){
      case OK:
        switch(estado){
          case FIGHT_ADELANTE:
            estado = TRACKING;
            Led1On();
	          MoverAdelante();
            _delay_ms(DELAY_ESTADO);
            break;
          case TRACKING:
            accionTracking();
            Led1Toggle();
            _delay_ms(DELAY_ESTADO);
            break;
          case DETENIDO:
          default: 
            ApagarMotores();
            titilarLed(12);
            break;
        }
        break;
      case ATRAS:
        MoverAdelante();
        _delay_ms(DELAY_ESCAPE);
        break;
      case ADELANTE:
        MoverAtras();
        _delay_ms(DELAY_ESCAPE);
        break;
      case ADELANTE_DER:
        GirarIzquierdaAtras();
        _delay_ms(DELAY_ESCAPE);
        break;
      case ADELANTE_IZQ:
        GirarDerechaAtras();
        _delay_ms(DELAY_ESCAPE);
        break;
      case ATRAS_DER:
        GirarIzquierdaAdelante();
        _delay_ms(DELAY_ESCAPE);
        break;
      case ATRAS_IZQ:
        GirarDerechaAdelante();
        _delay_ms(DELAY_ESCAPE);
        break;
      default:
        ApagarMotores();
        titilarLed(10);
        break;
    }
  }
}


void setup (void) {
	ConfigurarMotores();
	configurarPinSensoresSup();
	configurarPinSensoresInf();
	configurarTimerSensoresSup();
	configurarPulsador();
  configurarSolenoide();
  energizarSolenoide();
  Led1Init();
  Led1Off();

	estado = DETENIDO;
  cantVeces = 0;
	sei();
}

void configurarPulsador(void){
	PulsadorInit();
	// Configuro el pin change
	PCICR |= (1<<PCIE1);
	PCMSK1 = (1<<PCINT9);
}

void accionTracking(void){
	uint8_t temp;
  if (cantVeces < ALEATOREO_MAX_CUENTA) {
    cantVeces++;
  }
  else{
    cantVeces=0;
    temp = proximoEstadoAleatorio();
    switch(temp) {
      case 0:
        RotarIzquierda();
        break;
      case 1:
        GirarDerechaAdelante();
        break;
      case 2:
        GirarDerechaAtras();
        break;
      case 3:
        RotarDerecha();
        break;
    }
  }
}

// Interrupcion de pulsador (vetor_4)
ISR(PCINT1_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(250);

	if (IsPulsadorSet() == true) { 
	// significa que esta en 1 y hubo flanco ascendente genuino
	// se podria reemplazar la variable por poner apagar todo, poner 
	// el micro a dormir esperando solo esta interrupcion y luego
	// despertalo. Aca se lo despertaria
    EncenderMotores();
//  
    estado = TRACKING;
	}

  // Este flag se clerea a mano porque el clear por hardware se realiza en el
  // momento que se atiende la interrupcion y no cuando se sale de ella.
  // Esto hace que mientras se esta dentro de la interrupcion, puedan generarse
  // nuevos flancos (ruido) que no queremos atender
  SetBit(EIFR, INTF0);
}


/* funciones de prueba */
void movimientoPrueba(void){
	MoverAdelante();
	_delay_ms(400);
	GirarIzquierdaAtras();
	_delay_ms(400);
	GirarDerechaAtras();
	_delay_ms(400);
	MoverAtras();
	_delay_ms(100);
}

void titilarLed(uint8_t numero){
  uint8_t i;
  
  Led1Off();
  for (i=0;i<(2*numero);i++){
    Led1Toggle();
    _delay_ms(200);
  }
    _delay_ms(300);
}

