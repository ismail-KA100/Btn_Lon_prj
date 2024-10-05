/******************************************************************************
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 ******************************************************************************/

/*
 *  ======== main.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h>
/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Mailbox.h>
/* TI-RTOS Header files */
#include <driverlib.h>
/* Board Header file */
#include "main.h"
#include "hal_LCD.h"
#include "Degre.h"
#include "RTC.h"

//******************************************************************************
// Constante
//******************************************************************************
#define TIMEOUT             12

#define BTN_TIMEOUT         200
#define EVENT_BTN1          Event_Id_01
#define EVENT_BTN2          Event_Id_02

#define EVENT_BTN1_SHORT    Event_Id_03
#define EVENT_BTN1_LONG     Event_Id_04
#define EVENT_BTN2_SHORT    Event_Id_05
#define EVENT_BTN2_LONG     Event_Id_06


//******************************************************************************
// Varaibles Globales
//******************************************************************************
typedef struct MailObj {
    int id;
    char val;
} MailObj;

MailObj Msg;

uint32_t Millis;

//******************************************************************************
// Prototype de fonction
//******************************************************************************
void Inti_GPIO(void);
Void heartBeatFxn(UArg arg0, UArg arg1);
Void Blink_LedV(UArg arg0, UArg arg1);
void Irq_Port1(unsigned Iendex);
void Irq_Timer0(unsigned Index);
void Event_BTNx(UArg arg0, UArg arg1);
void Event_BTN_SL(UArg arg0, UArg arg1);

/******************************************************************************
 *  ======== main ========
 ******************************************************************************/
int main(void)
{
    WDT_A_hold(WDT_A_BASE); //Stop WDT
    PM5CTL0 &= ~LOCKLPM5;

    Inti_GPIO();
    Init_LCD();
    Init_Ref_A();
    Init_ADC12();
    Init_RTC();

    displayText("TEXTE");

    /* Start BIOS */
    BIOS_start();

    return (0);
}

//****************************************************************************
//  Inti_GPIO
//****************************************************************************
void Inti_GPIO(void)
{
    // PORT1
    GPIO_setAsOutputPin(GPIO_PORT_P1, LEDR);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, LEDR);
    GPIO_setAsInputPin(GPIO_PORT_P1, BTN1+BTN2);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, BTN1+BTN2);

    // PORT9
    GPIO_setAsOutputPin(GPIO_PORT_P9, LEDV);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, LEDV);

    // IRQ
    GPIO_enableInterrupt(GPIO_PORT_P1, BTN1+BTN2);
    GPIO_clearInterrupt(GPIO_PORT_P1, BTN1+BTN2);

}

//****************************************************************************
/*
 *  ======== heartBeatFxn ========
 *  Toggle the Board_LEDR.
 *****************************************************************************/
Void heartBeatFxn(UArg arg0, UArg arg1)
{
    while (1)
        {
        Task_sleep(1000); //ms
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, LEDR);
        }
}

//****************************************************************************
/*
 *  ======== Blink_LedV ========
 *  Toggle the Board_LEDV.
 *****************************************************************************/
Void Blink_LedV(UArg arg0, UArg arg1)
{
    while (1)
        {
        GPIO_toggleOutputOnPin(GPIO_PORT_P9, LEDV);
        Task_sleep(500);    //ms
        }
}

//****************************************************************************
// Irq_Port1
//****************************************************************************
void Irq_Port1(unsigned Index)
{
    uint16_t Status = GPIO_getInterruptStatus(GPIO_PORT_P1, BTN1+BTN2);

    switch(Status)
        {
        case BTN1:
            Event_post(h_event0, EVENT_BTN1);
            GPIO_clearInterrupt(GPIO_PORT_P1, BTN1);
            break;

        case BTN2:
            Event_post(h_event0, EVENT_BTN2);
            GPIO_clearInterrupt(GPIO_PORT_P1, BTN2);
            break;
        }
}

//******************************************************************************
//  EVENt_BTNX
//******************************************************************************
void Irq_Timer0(unsigned Index)
{
    ++Millis;
}

//******************************************************************************
//  EVENt_BTNX
//******************************************************************************
void Event_BTNx(UArg arg0, UArg arg1)
{
    uint16_t Posted;
    uint32_t tt;

    while(1)
        {
        Posted = Event_pend(h_event0,
                            0,                      // Mask AND
                            EVENT_BTN1+EVENT_BTN2,  // Mask OR
                            TIMEOUT
                            );

        switch(Posted)
            {
            case EVENT_BTN1:
                tt = Millis;
                Timer_start(h_timer0);

                while(1)
                    {
                    if(GPIO_getInputPinValue(GPIO_PORT_P1, BTN1))
                        {
                        Event_post(h_event0, EVENT_BTN1_SHORT); // SHORT
                        break;
                        }

                    if((Millis - tt) > BTN_TIMEOUT)
                        {
                        Event_post(h_event0, EVENT_BTN1_LONG);  // LONG
                        break;
                        }

                    Task_sleep(1);
                    }

                Timer_stop(h_timer0);
                break;

            case EVENT_BTN2:
                break;
            }

        Task_sleep(1);
        }
}

//******************************************************************************
//  EVENt_BTNX SHORT_LONG
//******************************************************************************
void Event_BTN_SL(UArg arg0, UArg arg1)
{
    uint16_t Posted;

    while(1)
        {
        Posted = Event_pend(h_event0,
                            0,                      // Mask AND
                            EVENT_BTN1_SHORT+EVENT_BTN1_LONG,  // Mask OR
                            TIMEOUT
                            );

        switch(Posted)
            {
            case EVENT_BTN1_SHORT:
                GPIO_setOutputHighOnPin(GPIO_PORT_P9, LEDV);
                break;
            case EVENT_BTN1_LONG:
                GPIO_setOutputLowOnPin(GPIO_PORT_P9, LEDV);
                break;
            }

        Task_sleep(1);
        }

}






