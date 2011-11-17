#include "motores.h"
//#include "sensores.h"

PwmOut drv_PWMD(p24);               
PwmOut drv_PWMI(p25);

DigitalOut drv_EnableMD(p23);
DigitalOut drv_EnableMI(p26);

/*
PwmOut drv_PWMD_1(p24);               
PwmOut drv_PWMD_2(p23);
PwmOut drv_PWMI_1(p25);
PwmOut drv_PWMI_2(p26);
*/
DigitalOut drv_nRESET(p29);  // Entrada de Reset del puente H. Un '0' reinicia la logica de entrada del puente y deshabilita las salidas.
DigitalOut drv_nSLEEP(p28);  // Un '1' habilita el puente H. Un '0' lo pone en estado de bajo consumo. 

InterruptIn drv_nFAULT(p27); // Salida de estado del puente H. "Low" cuando en estado de falla (sobretemperatura, sobrecorriente).
DigitalOut  drv_nFAULT_restore(p27);

void configurar_motores(void) {
    drv_EnableMD = 0;
    drv_EnableMI = 0;
    drv_PWMD.period_us(PERIODO_PWM_US);
    drv_PWMI.period_us(PERIODO_PWM_US);
    detener_motores();
    drv_EnableMD = 1;
    drv_EnableMI = 1;

/*
    drv_PWMD.period_us(PERIODO_PWM_US);
    drv_PWMI.period_us(PERIODO_PWM_US);
    drv_EnableMD = 1;
    drv_EnableMI = 1;
    drv_nSLEEP = 0;       // 0 = motores deshabilitados
    //drv_nFAULT.fall(&capturar_interrupt);
*/
}

void capturar_interrupt(void){
   drv_nRESET = 0;
//   wait(0.1);
//   drv_nFAULT_restore = 1;
//   drv_nRESET = 0;
}

void detener_motores(void){
   /*drv_nSLEEP = 0;*/
    drv_PWMD = FRENADO;
    drv_PWMI = FRENADO;
}

void mover_adelante(void){
    drv_PWMD = AVANZAR;
    drv_PWMI = AVANZAR;
}

void mover_atras(void){
    drv_PWMD = RETROCEDER;
    drv_PWMI = RETROCEDER;
}

void girar_izquierda(void){
    drv_PWMD = AVANZAR;
    drv_PWMI = RETROCEDER;
}

void girar_derecha(void){
    drv_PWMI = AVANZAR;
    drv_PWMD = RETROCEDER;
}