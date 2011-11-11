#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
#include "sensores.h"
#include "skil.h"

volatile estados estado;
volatile estadosInf estadoInf;
volatile estadosTracking estadoInterno;
volatile uint8_t sensoresInf;
volatile uint8_t cantVeces;


#define energizarSolenoide()     SetBit(PORT_SOLENOIDE, SOLENOIDE_NUMBER)
#define desenergizarSolenoide()  ClearBit(PORT_SOLENOIDE, SOLENOIDE_NUMBER)
#define proximoEstadoAleatorio() (TCNT2 & 0x03) //Devuelve un numero aleatorio entre 0 y 3

#define DELAY_ESTADO    5  //  en milisegundos

// Variable de estado de los emisores superiores
// Varia entre 0 y CANT_PULSOS_ALTO_EM_SUP + CANT_PULSOS_BAJO_EM_SUP
volatile uint8_t contPulsosEmSup;

void configurarPulsador(void);
void setup(void);
unsigned char actualizar_estado(void);
void actuar(void);

int main (void) {
	setup();
  while (estado==DETENIDO);
  _delay_ms(1); //tiempo de espera para bajar pollera
  desenergizarSolenoide();
  estado = TRACKING;
  encenderEmisorSuperior();
  encenderEmisorInferior();

	while(1){
    setearSensoresInf();

        //Para probar los sensores superiores ignoro el estado de los senosres inferiores
        //estadoInf = OK;

    switch (estadoInf){
      case OK:
        switch(estado){
          case FIGHT_ADELANTE:
            accionFightAdelante();
            estado = TRACKING;
            _delay_ms(DELAY_ESTADO);
            break;
          case FIGHT_ATRAS:
            accionFightAtras();
            estado = TRACKING;
            _delay_ms(DELAY_ESTADO);
            break;
          case TRACKING:
            //accionTracking();
            GirarIzquierda();
            break;
          case DETENIDO:
          default: 
            ApagarMotores();
            break;
        }
        break;
      case ADELANTE_DER:
        accionAdelanteDer();
        break;
      case ADELANTE_IZQ:
        accionAdelanteIzq();
        break;
      case ATRAS_DER:
        accionAtrasDer();
        break;
      case ATRAS_IZQ:
        accionAtrasIzq();
        break;
      case ATRAS:
        accionAtrasInf();
        break;
      case ADELANTE:
        accionAdelanteInf();
        break;
      default:
        ApagarMotores();
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

	estado = DETENIDO;
	estadoInterno = ADELANTANDO;
    cantVeces = 0;
	contPulsosEmSup = 0;
	sensoresInf = 0xFF;
	estadoInf = OK;
	sei();
}

void configurarPulsador(void){
	PulsadorInit();
	// Configuro el pin change
	PCICR |= (1<<PCIE1);
	PCMSK1 = (1<<PCINT9);
}

void configurarSolenoide(void){
  SetBit(DDR_SOLENOIDE, SOLENOIDE_NUMBER);
}

void setearSensoresInf(void){
  switch(sensoresInf){
		case MASK_INT_SENSA: 
			estadoInf = ADELANTE_IZQ;
			break;
		case MASK_INT_SENSB: 
			estadoInf = ADELANTE_DER;
			break;
		case MASK_INT_SENSD: 
			estadoInf = ATRAS_DER;
			break;
		case MASK_INT_SENSC_2: 
			estadoInf = ATRAS_IZQ;
			break;
		case (MASK_INT_SENSA & MASK_INT_SENSB): 
			estadoInf = ADELANTE;
			break;
		case (MASK_INT_SENSC & MASK_INT_SENSD): 
			estadoInf = ATRAS;
			break;
		default:
			estadoInf = OK;
			break;
	}
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

void accionTracking(void){
	// Tiene que buscar al oponente. Podemos girar en el lugar 180 y movernos un poco hasta que lo encontramos.
	switch (estadoInterno){
	case GIRANDO_DERECHA:
		if (cantVeces <= CANT_REPETICIONES){
			GirarDerecha();
			cantVeces++;
		} else {
			estadoInterno = proximoEstadoAleatorio(); //ADELANTANDO;
			cantVeces = 0;
		}
		break;
	case GIRANDO_IZQUIERDA:
		if (cantVeces <= CANT_REPETICIONES){
			GirarIzquierda();
			cantVeces++;
		} else {
			estadoInterno = proximoEstadoAleatorio(); //ATRAZANDO;
			cantVeces = 0;
		}
		break;
	case ADELANTANDO:
		if (cantVeces <= CANT_REPETICIONES){
			MoverAdelante();
			cantVeces++;
		} else {
			estadoInterno = proximoEstadoAleatorio(); //GIRANDO_IZQUIERDA;
			cantVeces = 0;
		}
		break;
	case ATRAZANDO:
		if (cantVeces <= CANT_REPETICIONES){
			MoverAtras();
			cantVeces++;
		} else {
			estadoInterno = proximoEstadoAleatorio(); //GIRANDO_DERECHA;
			cantVeces = 0;
		}
		break;
	}
}


void accionFightAdelante(void){
	MoverAdelante();
}

void accionFightAtras(void){
	MoverAtras();	
}

/*Accion de las funciones que actuan segun que sensor inferior sale del tatami*/
void accionAdelanteDer(void){
	MoverAtras();

    //Me muevo para atras, pero mas rapido con el derecho porque es con el que me fui
/*    velMI = 0x40;
    velMD = 0x30;
	EncenderMotores();
*/
    _delay_ms(100);
}
void accionAdelanteIzq(void){
	MoverAtras();

    //Me muevo para atras, pero mas rapido con el izquierdo porque es con el que me fui
//    velMI = 0x30;
//    velMD = 0x40;
    
    _delay_ms(100);
}
void accionAtrasDer(void){
	MoverAdelante();

    //Me muevo para adelante, pero mas rapido con el derecho porque es con el que me fui
//    velMI = 0xC0;
//    velMD = 0xD0;

    _delay_ms(100);
}
void accionAtrasIzq(void){
    MoverAdelante();

    //Me muevo para adelante, pero mas rapido con el izquierdo porque es con el que me fui
 //   velMI = 0xD0;
 //   velMD = 0xC0;

    _delay_ms(100);
}
void accionAtrasInf(void){
	MoverAdelante();
  //
    _delay_ms(100);
}
void accionAdelanteInf(void){
	MoverAtras();

    _delay_ms(100);
}

ISR(PCINT2_vect) {
	uint8_t aux = (PIN_RPC | MASK_INT_SENSC);
	if(aux == 0xFF){
		sensoresInf |= ((1<<RPC_NUMBER)>>2);
	} else {
		sensoresInf &= ~((1<<RPC_NUMBER)>>2);
	}
}

ISR(PCINT0_vect) {
	// Uso directamente el PINB por que estan todos ahi.
	uint8_t aux = (PINB | MASK_INT_PORT);
	if(aux == 0xFF){
		sensoresInf |= ((1<<RPA_NUMBER)|(1<<RPB_NUMBER)|(1<<RPD_NUMBER));
	} else {
		sensoresInf &= aux;
	}

}

ISR(PCINT1_vect) {
	// Delay para debounce
	// Dado que no tenemos necesidad de hacer nada mientras esperamos por el
	// debounce lo dejamos asi. Sino, deberiamos utilizar algun timer
	_delay_ms(50);

	if (IsPulsadorSet()==true) { 
		// significa que esta en 1 y hubo flanco ascendente genuino
		// se podria reemplazar la variable por poner apagar todo, poner 
		// el micro a dormir esperando solo esta interrupcion y luego
		// despertalo. Aca se lo despertaria
    EncenderMotores();
	}

  // Este flag se clerea a mano porque el clear por hardware se realiza en el
  // momento que se atiende la interrupcion y no cuando se sale de ella.
  // Esto hace que mientras se esta dentro de la interrupcion, puedan generarse
  // nuevos flancos (ruido) que no queremos atender
  SetBit(EIFR, INTF0);
}


ISR(TIMER2_COMPA_vect){
	// Cuando se da la comparacion cambio el estado del pin solo si estoy en alto
	// Hay una variable global que me dice si estoy en alto o en bajo
	contPulsosEmSup++;
	if(contPulsosEmSup <= CANT_PULSOS_ALTO_EM_SUP){
		SetBit(PIN_EAD, EAD_NUMBER);
		SetBit(PIN_EAT, EAT_NUMBER);
	}
}

ISR(INT0_vect){
    estado = FIGHT_ADELANTE;
}

ISR(INT1_vect){  
    estado = FIGHT_ATRAS;
}




