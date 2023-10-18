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
#define BUTTON_PIN GPIO_PIN_4 //pin para el boton SW1

//Variables
volatile uint32_t ui32Loop; //variable para el delay
volatile bool delayComplete = false; // Usado para indicar cuando el SysTick ha completado el delay
int estado = 0; //bandera para el estado de las leds

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

//chequear si el boton se presiona
bool pressed(void) {
    return GPIOPinRead(GPIO_PORTF_BASE, BUTTON_PIN) == 0; //true 0 si se presiona, false  1 si no
}

//delay para los LEDS
void delay(void) {
    for(ui32Loop = 0; ui32Loop < 3000000; ui32Loop++) {} // Simple delay
}

void setup(void){
    // Define que PLL se divide en 4
    // Se lockea hasta que hasta la nueva configuracion
    // Frecuanci adel osciladro de 16mhz
    // uitliza el oscilaro principal para el reloj
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL |SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //habilita gpio para los leds
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); //Esperar a que se inicialice
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED); // definir leds como salidas
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BUTTON_PIN); //configurar el pin como entrada para el boton SW1
    GPIOPadConfigSet(GPIO_PORTF_BASE, BUTTON_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
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
        if(pressed()) {//recibe true, low del botn
            delay(); // delay para debounce
            while(!pressed()) {} // Esperar hasta que se suelte el botón para ejecutar, boton no est presionado

            // Ejecutar la secuencia completa al presionar el botón
            // Verde
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, GREEN_LED);
            delay();

            // Parpadeante verde
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, 0);//apaga
            delay();
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, GREEN_LED);//enciende
            delay();
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, 0);//apaga
            delay();

            // Amarillo
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, RED_LED | GREEN_LED);
            delay();

            // Rojo
            GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, RED_LED);
            delay();

            // Espera hasta el próximo botón presionado
            while(!pressed()) {}//si el boton no esta presionado sigue sigue ejecutando el bucle
        }
    }
}

