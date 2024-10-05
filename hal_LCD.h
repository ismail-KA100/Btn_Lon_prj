/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * --/COPYRIGHT--*/
/*******************************************************************************
 *
 * hal_LCD.h
 *
 * Hardware abstraction layer for the FH-1138P Segmented LCD
 * on MSP-EXP430FR6989
 *
 * February 2015
 * E. Chen
 *
 ******************************************************************************/

#ifndef OUTOFBOX_MSP430FR6989_HAL_LCD_H_
#define OUTOFBOX_MSP430FR6989_HAL_LCD_H_

//Change based on LCD Memory locations
#define pos1 9   /* Digit A1   begins  at S18/2=9 */
#define pos2 5   /* Digit A2   begins  at S10/2=5 */
#define pos3 3   /* Digit A3   begins  at S6/2=3  */
#define pos4 18  /* Digit A4   begins  at S36/2=18 */
#define pos5 14  /* Digit A5   begins  at S28/2=14 */
#define pos6 7   /* Digit A6   begins  at S14/2=7 */
#define pos7 2   /* Digit A7   begins  at S4/2=2 */
#define pos8 13  /* Digit BATT begins  at S26/2=13 */
#define pos9 17  /* Digit BATT begins  at S34/2=17 */
#define pos_ANT 4  /* Digit ANT begins at S8/2=4 */

#define BATL    0x10    // indication affichage de la batterie
#define BATR    0x10
#define BAT1    0x20
#define BAT2    0x20
#define BAT3    0X40
#define BAT4    0X40
#define BAT5    0X80
#define BAT6    0X80

// Define word access definitions to LCD memories
#ifndef LCDMEMW
#define LCDMEMW    ((int*) LCDMEM) /* LCD Memory (for C) */
#endif

//*****************************************************************************

char BufferText[30];    // pour strupr()

//*****************************************************************************

extern const char digit[10][2];
extern const char alphabetBig[26][2];
extern const char small_digit[10][2];
extern const char specialcar[11][2];

void Init_LCD(void);
void displayScrollText(char *msg);
void displayText(char *msg);
void showChar(char, int);
void clearLCD(void);
void clearDIGIT(void);
void clearOneDIGIT(uint8_t Position);
void NegCar_ON(void);
void NegCar_OFF(void);
void NegCar_Toggle(void);
void Decimal_ON(int position);
void Degre_ON(void);
void RXD_ON(void);
void RXD_OFF(void);
void RXD_Toggle(void);
void TXD_ON(void);
void TXD_OFF(void);
void TXD_Toggle(void);
void Ant_ON(void);
void Ant_OFF(void);
void Ant_Toggle(void);
void Heart_ON(void);
void Heart_OFF(void);
void Heart_Toggle(void);
void Exclamation_ON(void);
void Exclamation_OFF(void);
void Exclamation_Toggle(void);
void Rec_ON(void);
void Rec_OFF(void);
void Rec_Toggle(void);
void Bat_ON(void);
void Bat_OFF_LEVEL(void);
void Bat_Percent(uint16_t Pourcent);
void Clock_ON(void);
void Clock_OFF(void);
void Clock_Toggle(void);
char *strupr(char *string);

#endif /* OUTOFBOX_MSP430FR6989_HAL_LCD_H_ */
