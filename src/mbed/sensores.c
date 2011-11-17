#include "sensores.h"

//Emisores superiores; cada salida activa una terna distinta de emisores
DigitalOut emit_sup_1(p22); //Delantero - delantero derecho - trasero derecho             
DigitalOut emit_sup_2(p21); //Trasero - delantero izquierdo - trasero izquierdo        

//Sensores superiores; cada entrada tiene dos sensores conectados
//Defino un Bus para cada conjunto de sensores, manejado cada uno por un emisor diferente
//p15 Delantero y trasero - p16 Delantero derecho y trasero izquierdo - p17 Delantero izquierdo y trasero derecho                    
//BusIn bus_receptor(p15, p16, p17);     

InterruptIn receptorA(p15);
InterruptIn receptorB(p16);
InterruptIn receptorC(p17);

bool emisor_1_prendido;
bool emisor_2_prendido;


void configurar_ojitos(){
    emisor_1_prendido = false;
    emisor_2_prendido = false;
    receptorA.mode(PullNone);
    receptorB.mode(PullNone);
    receptorC.mode(PullNone);
}

Ticker portadora1;
Ticker modulacion1;
#define CANTMEDIOPULSOS 20

Ticker portadora2;
Ticker modulacion2;
int cantpulsos;
// Cuadrada modulada del emisor 1
void portadora1_tick() {
    emit_sup_1 = pulso1 & (! emit_sup_1);
}

void modulacion1_tick() {
    pulso1 = !pulso1;
    cantpulsos--;
    if (cantpulsos == 0) emisor1_sup_off();
}

// Cuadrada modulada del emisor 2
void portadora2_tick() {
    emit_sup_2 = (!emit_sup_2) & pulso2;
}

void modulacion2_tick() {
    pulso2 = !pulso2;
    cantpulsos--;
    if (cantpulsos == 0) emisor1_sup_off();
}

void emisor1_sup_on(void){
    emisor_1_prendido = true;
    cantpulsos = CANTMEDIOPULSOS;
    portadora1.attach_us(&portadora1_tick, SEMIPERIODO_PORTADORA_US);
    modulacion1.attach_us(&modulacion1_tick, ANCHO_PULSO_SENIAL_US);
}
void emisor1_sup_off(void){
    emisor_1_prendido = false;
    emit_sup_1 = 0;
    portadora1.detach();
    modulacion1.detach();
}

void emisor2_sup_on(void){
    emisor_2_prendido = true;
    cantpulsos = CANTMEDIOPULSOS;
    portadora2.attach_us(&portadora2_tick, SEMIPERIODO_PORTADORA_US);
    modulacion2.attach_us(&modulacion2_tick, ANCHO_PULSO_SENIAL_US);
}
void emisor2_sup_off(void){
    emisor_2_prendido = false;
    emit_sup_2 = 0;
    portadora2.detach();
    modulacion2.detach();
}

//Sensores inferiores, conectados a entradas digitales porque solo sensamos blaco o negro 


//Emisores inferiores
DigitalOut emit_inf(p11); //Todos los sensores se prenden con una sola salida
DigitalOut emit_inf2(p12); //Todos los sensores se prenden con una sola salida

void emisor_inf_on(void) {
    emit_inf = 1;
    emit_inf2 = 1;
}

void emisor_inf_off(void) {
    emit_inf = 0;
    emit_inf2 = 0;
}

void emisores_superior_on() {
    emit_sup_1 = 1;
    emit_sup_2 = 0;
    wait(2);
    emit_sup_1 = 0;
    emit_sup_2 = 1;
    wait(2);
}


void evaluar_ojitos_A(void) {
    if (emisor_1_prendido == true)
        estado_sensores |= (1<<A1ON);
    else if (emisor_2_prendido == true)
        estado_sensores |= (1<<A2ON);
        // analizar que pasa en el caso de una deteccion sin emisor encendido
    receptorA.fall(0);
}

void evaluar_ojitos_B(void) {
    if (emisor_1_prendido == true)
        estado_sensores |= (1<<B1ON);
    else if (emisor_2_prendido == true)
        estado_sensores |= (1<<B2ON);
        // analizar que pasa en el caso de una deteccion sin emisor encendido
    receptorB.fall(0);
}

void evaluar_ojitos_C(void) {
    if (emisor_1_prendido == true)
        estado_sensores |= (1<<C1ON);
    else if (emisor_2_prendido == true)
        estado_sensores |= (1<<C2ON);
        // analizar que pasa en el caso de una deteccion sin emisor encendido
    receptorC.fall(0);
}

void sensores_update(void){
//    int aux;
    estado_sensores = 0;
   
    //Prendo el sensor1, chequeo condicion sobre una terna de receptores
    receptorA.fall(&evaluar_ojitos_A);    
    receptorB.fall(&evaluar_ojitos_B);
    receptorC.fall(&evaluar_ojitos_C);
    emisor1_sup_on();
    wait(2);
    emisor1_sup_off();
    
    
    //Prendo el sensor2, chequeo condicion sobre otra terna de receptores
    receptorA.fall(&evaluar_ojitos_A);    
    receptorB.fall(&evaluar_ojitos_B);
    receptorC.fall(&evaluar_ojitos_C);
    emisor2_sup_on();
    wait(2);
    emisor2_sup_off();
}

void estado_actual_update(void){
    sensores_update();
    estado_anterior = estado_actual;
    
    switch(estado_sensores){
//emisor_1
        case (1<<0):
            estado_actual = OPONENTE_TD;
            break;
        case (1<<1):
            estado_actual = OPONENTE_AD;
            break;
        case (1<<2):
            estado_actual = OPONENTE_ADELANTE;
            break;
//emisor_2
        case (1<<3):
            estado_actual = OPONENTE_AI;
            break;
        case (1<<4):
            estado_actual = OPONENTE_TI;
            break;
        case (1<<5):
            estado_actual = OPONENTE_ATRAS;
            break;
        default:
            estado_actual = 0;
            break;
     }          
    

}    