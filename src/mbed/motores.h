#ifndef _MOTORES_H_
#define _MOTORES_H_

#include "mbed.h"

#define PERIODO_PWM_US    25   // T = 1/f; f = 40khz

#define AVANZAR          0.01
#define RETROCEDER       0.99
#define GIRAR            0.75
#define FRENADO          0.5

void configurar_motores(void);
void detener_motores(void);
void mover_adelante(void);
void mover_atras(void);
void girar_izquierda(void);
void girar_derecha(void);  

void capturar_interrupt(void);          

#endif