/*
 * Clock.c
 *
 *  Created on: 18 oct. 2023
 *      Author: beepr
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <driverlib.h>
#include <RTC.h>

#include "hal_LCD.h"


void Irq_RTC(unsigned Index);

//*****************************************************************************
// Init_Clock
//*****************************************************************************
void Init_RTC(void)
{
    RTC_C_disableInterrupt(RTC_C_BASE, RTC_C_CLOCK_READ_READY_INTERRUPT+
                           RTC_C_TIME_EVENT_INTERRUPT+
                           RTC_C_CLOCK_ALARM_INTERRUPT);

    RTC_C_holdClock(RTC_C_BASE);

    Currentime.DayOfMonth   =   0x12;
    Currentime.DayOfWeek    =   0x03;
    Currentime.Hours        =   0x0D;
    Currentime.Minutes      =   0x37;
    Currentime.Month        =   0x0A;
    Currentime.Seconds      =   0x37;
    Currentime.Year         =   0x7E7;

    RTC_C_initCalendar(RTC_C_BASE, &Currentime, RTC_C_FORMAT_BINARY );

    RTC_C_clearInterrupt(RTC_C_BASE, RTC_C_CLOCK_READ_READY_INTERRUPT);
    RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_CLOCK_READ_READY_INTERRUPT);

    RTC_C_startClock(RTC_C_BASE);
}

//*****************************************************************************
// Irq_Clock
// Vect: 28
//*****************************************************************************
void Irq_RTC(unsigned Index)
{
    uint8_t Status = RTC_C_getInterruptStatus(RTC_C_BASE,
                                              RTC_C_CLOCK_READ_READY_INTERRUPT
                                              );

    switch(Status)
        {
        case RTC_C_CLOCK_READ_READY_INTERRUPT:
            Disp_RTC();
            RTC_C_clearInterrupt(RTC_C_BASE, RTC_C_CLOCK_READ_READY_INTERRUPT);
            break;

        default:
            break;
        }
}

//*****************************************************************************
// Disp_RTC
//*****************************************************************************
void Disp_RTC(void)
{
    Calendar StructRTC = RTC_C_getCalendarTime(RTC_C_BASE);
    clearDIGIT();

    showChar(StructRTC.Hours /10 + '0', pos1);
    showChar(StructRTC.Hours %10 + '0', pos2);

    showChar(StructRTC.Minutes /10 + '0', pos3);
    showChar(StructRTC.Minutes %10 + '0', pos4);

    showChar(StructRTC.Seconds /10 + '0', pos5);
    showChar(StructRTC.Seconds %10 + '0', pos6);

    // separateur
    LCDM7   |= 0x04;
    LCDBM7  |= 0x04;
    LCDM20  |= 0x04;
    LCDBM20 |= 0x04;
}

//*****************************************************************************









