#ifndef _SENSORES_H_
#define _SENSORES_H_
#include "mbed.h"


#define SEMIPERIODO_PORTADORA_US      13
#define ANCHO_PULSO_SENIAL_US        600
#define  A1ON   0
#define  A2ON   1
#define  B1ON   2
#define  B2ON   3
#define  C1ON   4
#define  C2ON   5


#define OPONENTE_ADELANTE 1
#define OPONENTE_ATRAS    2
#define OPONENTE_AI       3  //ADELANTE IZQUIERDA
#define OPONENTE_AD       4  //ADELANTE DERECHA
#define OPONENTE_TI       5  //ATRAS IZQUIERDA
#define OPONENTE_TD       6  //ATRAS DERECHA
#define ME_CAIGO          7

extern int estado_anterior;
extern int estado_actual;
extern int estado_sensores;
extern int pulso1;
extern int pulso2;

void sensores_update(void);
void estado_actual_update(void);
void portadora1_tick();
void modulacion1_tick();
void portadora2_tick();
void modulacion2_tick();

void configurar_ojitos();

void emisor1_sup_on(void);
void emisor1_sup_off(void);
void emisor2_sup_on(void);
void emisor2_sup_off(void);

void emisores_superior_on();

void emisor_inf_on(void);
void emisor_inf_off(void);
int sensor_prendido(int num);


#endif