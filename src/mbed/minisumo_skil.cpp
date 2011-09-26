#include "mbed.h"
#include "motores.h"
#include "sensores.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

InterruptIn sens_inf_DI(p5); //Adelante izquierda
InterruptIn sens_inf_DD(p6); //Adelante derecha
InterruptIn sens_inf_TI(p7); //Atras izquierda
InterruptIn sens_inf_TD(p8); //Atras derecha

#define APAGADO    0
#define ENCENDIDO  1

InterruptIn pulsador(p30); // Pulsador

int sensor_prendido(int);
void evitar_limite(void);

int estado_anterior;
int estado_actual;
int estado_sensores;

int estado_global = APAGADO;

int pulso1;
int pulso2;

//Serial pc (USBTX,USBRX);

DigitalOut solenoide(p10);


void puls_handler(void) {
    if (estado_global == ENCENDIDO) {
        estado_global = APAGADO;
        detener_motores();
        solenoide = 1;
    }
    else if (estado_global == APAGADO) {
        estado_global = ENCENDIDO;
        mover_adelante();
        solenoide = 0;
    }
}


int main() {
//   pc.baud(57600);
    configurar_motores();
    solenoide = 1;
    pulsador.rise(&puls_handler);
    pulsador.mode(PullUp);
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    
    pulso1 = 0;
    pulso2 = 0;
 
/*    //Si algun sensor del suelo ve el borde del cuadrilatero, entonces hago algo
    sens_inf_DI.fall(&evitar_limite); //Adelante izquierda
    sens_inf_DD.fall(&evitar_limite); //Adelante derecha
    sens_inf_TI.fall(&evitar_limite); //Atras izquierda
    sens_inf_TD.fall(&evitar_limite); //Atras derecha
*/
   // configurar_ojitos();
    emisor1_sup_on();
    led4=1;

    estado_anterior = OPONENTE_ADELANTE;

    while(1){

    led4 = 1;
    wait_ms(1);
    led4=0;
    wait_ms(1);
    emisor1_sup_on();
/* PRUEBA SENSORES DE ABAJO   
    emisor_inf_off();
    wait(4);
    emisor_inf_on();
    wait(4);
*/

/***** PRUEBA MOTORES!!!!!!!*******/
    
/*    avanzar_adelante();
    wait(2);
    avanzar_atras();
    wait(2);
    girar_izquierda();
    wait(2);
    girar_derecha(); 
    wait(2);
    //detener_motores();
    //wait(3);*/

/**********************************/

                //estado_actual_update();
//        sensores_update();
//        pc.printf("Estados: %X", estado_sensores);
//        wait(5);
        //corregir_curso();
           
    }      
}

/*void corregir_curso(void){
    switch(estado_actual){
        case OPONENTE_ADELANTE:
            avanzar_adelante();
            led1 = 0;
            led2 = 1;
            led3 = 1;
            led4 = 0;

               break;
        case OPONENTE_ATRAS:
            avanzar_atras();
            led1 = 1;
            led2 = 0;
            led3 = 0;
            led4 = 1;

               break;
        case OPONENTE_AI:  //ADELANTE IZQUIERDA
            girar_izquierda();
            led1 = 1;
            led2 = 0;
            led3 = 0;
            led4 = 0; 
               break;
        case OPONENTE_AD:  //ADELANTE DERECHA
            girar_derecha();
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 1;
               break;
        case OPONENTE_TI:  //ATRAS IZQUIERDA
            girar_derecha();
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 1;            
               break;
        case OPONENTE_TD:  //ATRAS DERECHA
            girar_izquierda();
            led1 = 1;
            led2 = 0;
            led3 = 0;
            led4 = 0;
               break;
        case ME_CAIGO:
            evitar_limite();
            led1 = 1;
            led2 = 1;
            led3 = 1;
            led4 = 1;
                break;
        default: 
            led1 = 0;
            led2 = 0;
            led3 = 0;
            led4 = 0;
                break;
     }
}*/

int sensor_prendido(int num) {
    switch(num) {
    case 1: return sens_inf_DI;
    case 2: return sens_inf_DD;
    case 3: return sens_inf_TI;
    case 4: return sens_inf_TD;
    default: return 0;
    }
}


void evitar_limite(void){
    detener_motores();
    
    
    //if(sens_inf_DI) || sens_inf_DD)
        //avanzar_atras();
    if(!sens_inf_DI){
        led1 = 1;
        led2 = 0;
        led3 = 0;
        led4 = 0;
    }
    else if(!sens_inf_DD){
        led1 = 0;
        led2 = 1;
        led3 = 0;
        led4 = 0;
    }
    else if(!sens_inf_TI){
        led1 = 0;
        led2 = 0;
        led3 = 1;
        led4 = 0;
    }
    else if(!sens_inf_TD){
        led1 = 0;
        led2 = 0;
        led3 = 0;
        led4 = 1;
    }
  //  else
    //    avanzar_adelante();

    //decidir para donde salir en funcion del estado anterior, para eso definir un nuevo flag
}