//Luis Pedro Gonzalez 21513
//Lab7ED2
//blinky example



#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h" // libreria para control del sistema, aqui tambien esta el reloj
#include "inc/hw_types.h"
#include "driverlib/systick.h" //libreria para el segundo delay



#define XTAL 16000000 //reloj externo de 16MHz

// Definiciones para los LEDS
#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

//Variables
volatile uint32_t ui32Loop; //variable para el delay
volatile bool delayComplete = false; // Usado para indicar cuando el SysTick ha completado el delay


void setup(void); //Función del setup



//funciones

//segundo delay2

void SysTickHandler(void) {
    delayComplete = true; // Indica que el delay ha sido completado
}


//delay2
void delay2(void) {
    delayComplete = false; // Reiniciar el indicador
    while (!delayComplete) {
        // Esperar a que el SysTick complete el delay
    }
}


//delay para los LEDS

void delay(void) {
    for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++) {} // Simple delay
}


void setup(void){

    //Define que PLL se divide en 4
    //Se lockea hasta que hasta la nueva configuracion
    //Frecuanci adel osciladro de 16mhz
    //uitliza el oscilaro principal para el reloj
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);//habilita gpio para los leds

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED);// definir leds como salidas


//otra forma de realizar el delay

    // Configurar el SysTick para 1 segundo
    SysTickPeriodSet(SysCtlClockGet());
    SysTickIntRegister(&SysTickHandler); // Registrar la función del manejador
    SysTickIntEnable();
    SysTickEnable();

}

int main(void){
    setup(); //Llamar al setup


//loop principal
while(1) {


    //empezar a encender los leds

    //enciende led rojo
    //gpioporff es para el puerto f
    //pines quev voy a usar


    //pin a enceder, en esre caso el rojos

    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, RED_LED);
    delay();

    // amariilo, es la combinacion enr verde  y rojo
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, RED_LED | GREEN_LED);
    delay();


    // verde
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, GREEN_LED);
    delay();


}



}


