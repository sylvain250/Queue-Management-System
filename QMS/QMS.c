/*
 * File:   QMS.c
 * Authors: Honore Abikunda
 *          David Sindambiwe
 *          Sylvain Ntezimana 
 *
 * Created on April 15, 2019, 5:01 PM
 */


#define _XTAL_FREQ 4000000
#include <xc.h>

int ones;                    //declaring variable ones
int tens;                    //declaring variable tens  
int value;                   //Declaring variable value of Number corresponds to available clients 
                             //                                    and times the button have been pressed
int door_number;             //declaring variable door number                                                        
int shifter = 0;             //declaring Variables shifter
int a;                       //
int server1a,server1b;               //declaring variable for displaying on room 1
int server2a,server2b;               //declaring variable for  displaying on room 2
int server3a,server3b;               //declaring variable for  displaying on room 3
int server4a,server4b;               //declaring variable for  displaying on room 4
char seg_code[]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

void main(void) {
    
    TRISB = 0b11110000;                //Port B pins from RB4 to RB7 are configured as inputs
    TRISC = 0;                       //All port C pins are configured as outputs
    TRISD = 0;                      //All port D pins are configured as outputs
    TRISA = 0;                      //All port A pins are configured as outputs
    OPTION_REG = 0b00000001;        //Prescaler rate bit PS0 is enabled to make TMR0 1/4 and WDT 1/2
    INTCON = 0b10101000;            //Register for controlling interrupts which enables GIE bit7,TMR0IE bit5,RBIE bit3
    PORTB = 0;                      //Clearing PortB 
    PORTD = 0;                     //Clearing port D
    
    
    while(1){;}             //Endless loop
    
    return;
}

void updateValue(void){                  //Calculation of tens and ones for displaying
     value++;
     tens = value/10;
     ones = value - 10*tens;
}
void __interrupt() my_isr_routine(void){
    if(RBIF){
        __delay_ms(100);
       
   
        a = PORTB; 
  
        if(RB4==0){               //Accepting interrupt of button 1 and update the value button that have been pressed
            __delay_ms(100);
              door_number = 1;
              updateValue();
              server1a=tens;
              server1b=ones;
              
        }
        if(RB5==0){                //Accepting interrupt of button 2 and update the value button that have been pressed
            __delay_ms(100);
             door_number = 2;
             updateValue();
             server2a=tens;
             server2b=ones;
        }
        if(RB6==0){                 //Accepting interrupt of button 3 and update the value button that have been pressed
            __delay_ms(100);
             door_number = 3;
             updateValue();
            server3a=tens;
             server3b=ones;
         
        }
        if(RB7==0){                   //Accepting interrupt of button 4 and update the value button have been pressed
            __delay_ms(100);
             door_number = 4;
             updateValue();
             server4a=tens;
             server4b=ones;
           
        }
        RBIF = 0;   //clearing of interrupt flag
    }
    
     if(TMR0IF){
            //switch digits for every interrupt. 
            shifter++;        
            switch(shifter){
                case 1:                           //Displaying door number
                    PORTC = 0b11111011;
                    PORTA = 0b11111111;
                    PORTD = seg_code[door_number];
                    break;
                case 2:                           //Displaying ones of main display
                    PORTC = 0b11111101;
                    PORTA = 0b11111111;
                    PORTD = seg_code[ones];
                    break;
                case 3:                           // Displaying tens of main display
                    PORTC = 0b11111110;
                    PORTA = 0b11111111;
                    PORTD = seg_code[tens];
                    break;
                case 4:                           //Displaying ones of first door
                    PORTC = 0b11110111;
                    PORTA = 0b11111111;
                    PORTD = seg_code[server1b];
                    break; 
                case 5:                           //Displaying tens of first door
                    PORTC = 0b11101111;
                    PORTA = 0b11111111;
                    PORTD = seg_code[server1a];
                    break;
                case 6:                           //Displaying ones of second door
                    PORTC = 0b10111111;
                    PORTA = 0b11111111;
                    PORTD = seg_code[server2b];                   
                    break; 
                case 7:                          // Displaying tens of second door
                    PORTC = 0b11011111;
                    PORTA = 0b11111111;
                    PORTD = seg_code[server2a];
                    break; 
                case 8:                          // Displaying tens of third door
                    PORTC = 0b11111111;
                    PORTA = 0b11111110;
                    PORTD = seg_code[server3a];
                    break;             
                case 9:                          // Displaying ones of third door
                    PORTC = 0b11111111;
                    PORTA = 0b11111101;
                    PORTD = seg_code[server3b];
                    break;
                case 10:                          // Displaying tens of fourth door
                    PORTC = 0b11111111;
                    PORTA = 0b11111011;
                    PORTD = seg_code[server4a];
                    break;
                case 11:                          // Displaying one of fourth door
                    PORTC = 0b11111111;
                    PORTA = 0b11110111;
                    PORTD = seg_code[server4b];
                    break;             

                case 12:
                    shifter = 0;
                    break;
      
            }
            TMR0IF = 0;     // clearing of interrupt flag
    }
}
