#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "motores.h"
//#include "sensores.h"
#include "skil.h"

volatile unsigned char estado;

void configurarPulsador(void);
void setup(void);
unsigned char actualizar_estado(void);
void actuar(void);

int main (void) {
  setup();
  EncenderMotores();
  while(1){
    MoverAdelante();
    _delay_ms(1000);
    MoverAtras();
    _delay_ms(1000);
    GirarIzquierda();
    _delay_ms(1000);
    GirarDerecha();
    _delay_ms(1000);
//    leer_sensores_adc();
//	  if(estado != DETENIDO){
//      estado = actualizar_estado();
//      actuar();
    
  }
}

void setup (void) {
  ConfigurarMotores();
//  configurar_adc();
//  configurarPulsador();
//  Led1Init();
//  estado = DETENIDO;
  sei();
}

/*
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
  
  return DETENIDO; // no deberia llegar aca
}
*/

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

/*
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
*/
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
