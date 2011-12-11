#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "skil.h"

volatile estados estado;
//volatile estadosTracking estadoInterno; //no se esta usando
//volatile uint8_t cantVeces;

#define proximoEstadoAleatorio() (TCNT2 & 0x03) //Devuelve un numero aleatorio entre 0 y 3

#define DELAY_ESTADO    50 // en milisegundos
#define DELAY_INICIO    2000 // en milisegundos 5200

int main (void) {
	setup();
Led1Off();

  while (estado == DETENIDO);
  
  _delay_ms(DELAY_INICIO); //tiempo de espera para bajar pollera
  desenergizarSolenoide();
  encenderEmisorSuperior();
  encenderEmisorInferior();

Led1On();
	while(1){
    if (IsnFaultSet()==0) MostrarError(); //debería recuperarse del error
    if (flagVisto==1) {
      estado = FIGHT_ADELANTE;
      flagVisto = 0;
    }

    switch (estadoInf){
      case OK:
        switch(estado){
          case FIGHT_ADELANTE:
            estado = TRACKING;
            accionFightAdelante();
            _delay_ms(DELAY_ESTADO);
            break;
          case TRACKING:
            accionTracking();
//            GirarDerecha();
//            _delay_ms(200);
            break;
          case DETENIDO:
          default: 
            ApagarMotores();
            break;
        }
        break;
      case ATRAS:
        estadoInf = OK;
        MoverAdelante();
        _delay_ms(200);
        break;
      case ADELANTE:
        estadoInf = OK;
        MoverAtras();
        _delay_ms(200);
        break;
      case ADELANTE_DER:
        estadoInf = OK;
        GirarDerecha();
        _delay_ms(100);
        MoverAtras();
        _delay_ms(200);
        break;
      case ADELANTE_IZQ:
        estadoInf = OK;
        GirarIzquierda();
        _delay_ms(100);
        MoverAtras();
        _delay_ms(200);
        break;
      case ATRAS_DER:
        estadoInf = OK;
        GirarIzquierda();
        _delay_ms(100);
        MoverAdelante();
        _delay_ms(200);
        break;
      case ATRAS_IZQ:
        estadoInf = OK;
        GirarDerecha();
        _delay_ms(100);
        MoverAdelante();
        _delay_ms(200);
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
  configurarSolenoide();
	configurarPinSensoresSup();
	configurarPinSensoresInf();
	configurarTimerSensoresSup();
	configurarPulsador();
  energizarSolenoide();
  Led1Init();

	estado = DETENIDO;
//	estadoInterno = ADELANTANDO; //no se esta usando
//  cantVeces = 0;
	sei();
}

void configurarPulsador(void){
	PulsadorInit();
	// Configuro el pin change
	PCICR |= (1<<PCIE1);
	PCMSK1 = (1<<PCINT9);
}

void accionFightAdelante(void){
	MoverAdelante();
}

/*
 * void accionFightAtras(void){
	MoverAtras();	
}
*/

/*Accion de las funciones que actuan segun que sensor inferior sale del tatami*/
/*void accionAtrasInf(void){
	MoverAdelante();

  estadoInf = OK;
  _delay_ms(200);

  // no se si borraria este flag (AB)
  PCIFR |= (1<<PCIF0);
}

void accionAdelanteInf(void){
	MoverAtras();

  estadoInf = OK;
  _delay_ms(200);

  // no se si borraria este flag (AB)
  PCIFR |= (1<<PCIF0); // | (1<<PCIF0);    
}
*/

void accionTracking(void){
	uint8_t temp = proximoEstadoAleatorio();
  switch(temp) {
    case 0:
      MoverAdelante();
      break;
    case 1:
      MoverAtras();
      break;
    case 2:
      GirarIzquierda();
      break;
    case 3:
      GirarDerecha();
      break;
  }
  _delay_ms(200);
}

// Interrupcion de pulsador (vetor_4)
ISR(PCINT1_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);

	if (IsPulsadorSet() == true) { 
	// significa que esta en 1 y hubo flanco ascendente genuino
	// se podria reemplazar la variable por poner apagar todo, poner 
	// el micro a dormir esperando solo esta interrupcion y luego
	// despertalo. Aca se lo despertaria
//    EncenderMotores();
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
	_delay_ms(300);
	MoverAtras();
	_delay_ms(300);
	GirarIzquierda();
	_delay_ms(100);
	GirarDerecha();
	_delay_ms(100);
}

void MostrarError() {
  Led1Off();
  while(1) {
    Led1Toggle();
    _delay_ms(100);
    Led1Toggle();
    _delay_ms(100);
    Led1Toggle();
    _delay_ms(100);
    Led1Toggle();
    _delay_ms(100);
    Led1Toggle();
    _delay_ms(500);
    Led1Toggle();
    _delay_ms(100);
  }
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

