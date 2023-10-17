//Luis Pedro Gonzalez 21513
//Lab7ED2



#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h" // libreria para control del sistema, aqui tambien esta el reloj

#define XTAL 16000000 //reloj externo de 16MHz


void setup(void); //Función del setup


void setup(void){

    //Define que PLL se divide en 4
    //Se lockea hasta que hasta la nueva configuracion
    //Frecuanci adel osciladro de 16mhz
    //uitliza el oscilaro principal para el reloj
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);

}

int main(void){
    setup(); //Llamar al setup


//loop principal
while(1) {

    //hola
}


}


