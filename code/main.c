#include <16f877A.h>     // Kullanýlacak denetleyicinin aþlýk dosyasý tanýtýlýyor.

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay(clock=4000000)   // Gecikme fonksiyonu için kullanýlan osilatör frekansý belirtiliyor


#use fast_io(a) // Port yönlendirme komutlarý a portu için geçerli
#use fast_io(b) // Port yönlendirme komutlarý b portu için geçerli

#define   display_1   pin_a0      //display_1 ifadesi pin_a0 ifadesine eþleniyor
#define   display_2   pin_a1
#define   display_3   pin_a2
#define   buzzer      pin_a3
#define   buton_azal  pin_a4
#define   buton_art   pin_a5

char dakika=2, saniye=60, sayi=100;       // char tipinde deðiþkenler tanýmlanýyor

const int digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

/********* ANA PROGRAM FONKSÝYONU********/

void main ()
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   set_tris_a(0b00110000);
   set_tris_b(0x00);

   output_a(0b00110000);     
   output_b(0x00);   
   
   output_low(display_1); 
   output_low(display_2); 
   output_low(display_3);
   output_high(buzzer);
   
while(true)
{         
      sayi--;

      output_high(display_1);  
      output_b(digit[saniye%10]); 
      delay_ms(4);             
      output_low(display_1);
         
      output_high(display_2);  
      output_b(digit[saniye/10]); 
      delay_ms(3);             
      output_low(display_2);

      output_high(display_3);  
      output_b(digit[dakika]); 
      delay_ms(3);             
      output_low(display_3);
       
   if (sayi==0)  
   {
      sayi=99;
      saniye--;
   }
         
   if (saniye == 0)
   {
      saniye=59;
      if(dakika == 0)
      {
         output_high(display_1); 
         output_high(display_2); 
         output_high(display_3);
         output_b(0x3F);
         output_low(buzzer);
      }
      dakika--;
   }
         
   if (input(buton_azal)) 
   {
      delay_ms(10);
      dakika--;
      saniye=59;
      
      if(dakika<=0)   {  dakika=0;  }
      
      while(input(buton_azal))
      {
      output_high(display_1);  
      output_b(digit[saniye%10]); 
      delay_ms(1);             
      output_low(display_1);
         
      output_high(display_2);  
      output_b(digit[saniye/10]); 
      delay_ms(1);             
      output_low(display_2);

      output_high(display_3);  
      output_b(digit[dakika]); 
      delay_ms(1);             
      output_low(display_3);
      }
   }     
   if (input(buton_art)) 
   {
      delay_ms(10);
      dakika++;
      saniye=59;
      
      if(dakika>9)   {  dakika=9;  }
      
      while(input(buton_art))
      {
      output_high(display_1);  
      output_b(digit[saniye%10]); 
      delay_ms(1);             
      output_low(display_1);
         
      output_high(display_2);  
      output_b(digit[saniye/10]); 
      delay_ms(1);             
      output_low(display_2);

      output_high(display_3);  
      output_b(digit[dakika]); 
      delay_ms(1);             
      output_low(display_3);
      }
   }
}
}

