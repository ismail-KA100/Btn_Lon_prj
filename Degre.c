/*
 * Degre.c
 *
 *  Created on: 6 nov. 2023
 *      Author: beepr
 */
#include <stdint.h>
#include <string.h>
/* TI-RTOS Header files */
#include <driverlib.h>
/* Board Header file */
#include "main.h"
#include "hal_LCD.h"
#include "Degre.h"

//*****************************************************************************
// Constante
//*****************************************************************************
#define CALADC_12V_30C  *((unsigned int *) 0x1A1A)
#define CALADC_12V_85C  *((unsigned int *) 0x1A1C)

#define CELCIUS     1
#define FARENHEIT   2

//*****************************************************************************
// Variable Globale
//*****************************************************************************
uint8_t TempUnit;

//*****************************************************************************
// Prototype de fonction
//*****************************************************************************
void Irq_ADC12(unsigned Index);

//*****************************************************************************
// Init_Ref_A()
//*****************************************************************************
void Init_Ref_A(void)
{
    Ref_A_setReferenceVoltage(REF_A_BASE, REF_A_VREF1_2V );
    Ref_A_enableReferenceVoltage(REF_A_BASE);
    Ref_A_enableTempSensor(REF_A_BASE);
    while(!Ref_A_isVariableReferenceVoltageOutputReady(REF_A_BASE));
}

//*****************************************************************************
// Init_ADC12()
//*****************************************************************************
void Init_ADC12(void)
{
    ADC12_B_initParam Adc_Param = {0};
    Adc_Param.clockSourceDivider            = ADC12_B_CLOCKDIVIDER_1;
    Adc_Param.clockSourcePredivider         = ADC12_B_CLOCKPREDIVIDER__1;
    Adc_Param.clockSourceSelect             = ADC12_B_CLOCKSOURCE_ADC12OSC;
    Adc_Param.internalChannelMap            = ADC12_B_TEMPSENSEMAP;
    Adc_Param.sampleHoldSignalSourceSelect  = ADC12_B_SAMPLEHOLDSOURCE_SC;

    ADC12_B_init(ADC12_B_BASE, &Adc_Param);
    ADC12_B_enable(ADC12_B_BASE);

    // Init Sample and  Hold
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,
                               ADC12_B_CYCLEHOLD_256_CYCLES, //clockCycleHoldCountLowMem
                               ADC12_B_CYCLEHOLD_4_CYCLES,  //clockCycleHoldCountHighMem,
                               ADC12_B_MULTIPLESAMPLESDISABLE); //multipleSamplesEnabled

    ADC12_B_configureMemoryParam MemParam = {0};
    MemParam.differentialModeSelect     = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    MemParam.endOfSequence              = ADC12_B_ENDOFSEQUENCE;
    MemParam.inputSourceSelect          = ADC12_B_INPUT_TCMAP;
    MemParam.memoryBufferControlIndex   = ADC12_B_MEMORY_0;
    MemParam.refVoltageSourceSelect     = ADC12_B_VREFPOS_INTBUF_VREFNEG_VSS;
    MemParam.windowComparatorSelect     = ADC12_B_WINDOW_COMPARATOR_DISABLE;

    ADC12_B_configureMemory(ADC12_B_BASE, &MemParam);

    // Irq
    ADC12_B_clearInterrupt(ADC12_B_BASE,
                           0,
                           ADC12_B_IFG0);

    ADC12_B_enableInterrupt(ADC12_B_BASE,
                            ADC12_B_IE0,
                            0,
                            0);

}

//*****************************************************************************
// Irq_ADC12()
//
// nVecteur : ( 45 )
//*****************************************************************************
void Irq_ADC12(unsigned Index)
{

    ADC12_B_clearInterrupt(ADC12_B_BASE,
                           0,
                           ADC12_B_IFG0);

}

//*****************************************************************************
// Conv_Adc12()
//*****************************************************************************
void Conv_ADC12(void)
{
    signed short temp;
    uint16_t GetVal;
    int degC;   // Celcius measurement
    int degF;   // Fahrenheit measurement

    ADC12_B_startConversion(ADC12_B_BASE,
                            ADC12_B_START_AT_ADC12MEM0,
                            ADC12_B_SINGLECHANNEL);

    while(ADC12_B_isBusy(ADC12_B_BASE));

    GetVal = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_0);

    // Calculate Temperature in degree C and F
    temp = (GetVal - CALADC_12V_30C);
    degC = ((long)temp * 10 * (85-30) * 10)/((CALADC_12V_85C - CALADC_12V_30C)*10) + 300;
    degF = (degC) * 9 / 5 + 320;

    TempUnit = CELCIUS;
    Disp_Adc12(degC);
}

//*****************************************************************************
// Disp_Adc12()
//*****************************************************************************
void Disp_Adc12(int Val)
{
    int Deg = Val;

    clearDIGIT();

    if(TempUnit == CELCIUS)
        showChar('C' , pos6);

    if(TempUnit == FARENHEIT)
        showChar('F' , pos6);

    if(Val < 0)
        {
        Deg *= -1;
        LCDMEM[pos1+1] += 0x04;
        }

    if(Deg>=1000)
    showChar((Deg/1000)%10 + '0' , pos2);

    if(Deg>=100)
    showChar((Deg/100)%10 + '0' , pos3);

    if(Deg>=10)
    showChar((Deg/10)%10 + '0' , pos4);

    if(Deg>=1)
    showChar((Deg/1)%10 + '0' , pos5);

    // Decimal point
     LCDMEM[pos4+1] |= 0x01;
     // Degree symbol
     LCDMEM[pos5+1] |= 0x04;
}




