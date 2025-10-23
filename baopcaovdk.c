
#include <18F452.h>
#fuses HS, NOWDT, PUT, NOPROTECT
#use delay(clock = 20000000)

#include <lcd.c>  

#define IN1 PIN_B0
#define IN2 PIN_B1
#define IN3 PIN_B2
#define IN4 PIN_B3

float nhietdo = 0;

void step_motor_forward()
{
  
   output_high(IN1); output_low(IN2); output_low(IN3); output_low(IN4);
   delay_ms(5);
   output_low(IN1); output_high(IN2); output_low(IN3); output_low(IN4);
   delay_ms(5);
   output_low(IN1); output_low(IN2); output_high(IN3); output_low(IN4);
   delay_ms(5);
   output_low(IN1); output_low(IN2); output_low(IN3); output_high(IN4);
   delay_ms(5);
}

void step_motor_stop()
{
   output_low(IN1);
   output_low(IN2);
   output_low(IN3);
   output_low(IN4);
}

void main()
{
   set_tris_d(0x00);      
   set_tris_b(0x00);      
   lcd_init();            
   delay_ms(10);

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);  
   set_adc_channel(0);
   delay_us(20);

   while(TRUE)
   {
      int16 adc_value = read_adc(); 
      nhietdo = adc_value * 0.488; 

      lcd_gotoxy(1,1);
      printf(lcd_putc, "Nhiet do:%4.1f", nhietdo);
      lcd_gotoxy(1,2);

      if(nhietdo > 30.0)
      {
         printf(lcd_putc, "Motor: QUAY   ");
         step_motor_forward();
      }
      else
      {
         printf(lcd_putc, "Motor: DUNG   ");
         step_motor_stop();
      }

      delay_ms(100);
   }
}
