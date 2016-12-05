/***************************************************************** 
**    程序名：MC9S12G128 PLL锁相环 
**    参  数：无 
**    功  能：将G128总线时钟超至32MHz   
**    注  意：观察LED闪烁频率可知超频是否成功 
**    作  者：赵露露 
**    版  本：v1.0 
**    时  间：2012.5.8    
******************************************************************/  
#include <hidef.h>            /* common defines and macros */  
#include "derivative.h"       /* derivative-specific definitions */  
  
  
/***************************************************************** 
**    函数名: delayms（） 
**    参  数：xms 
**    功  能：在32MHz总线时钟下大约延时xms毫秒   
**    注  意：     
******************************************************************/  
void delayms(uint xms)  
{  
  uint z,j;  
    for(z=xms;z>0;z--)  
        for(j=5340;j>0;j--);  
}  
void PLL_Init(void)   
{  
  CPMUPROT = 0x26;            //保护时钟配置寄存器  
  CPMUCLKS_PSTP = 0;          //禁用PLL  
  CPMUCLKS_PLLSEL = 1;        //选择PLL作为系统时钟源  
  CPMUOSC_OSCE = 1;           //外部晶振使能  
    
  CPMUSYNR = 0x07;            //fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)                       
  CPMUREFDIV = 0x07;          //16M:07,0F;32M:07,07;64M:07,03  
      
  CPMUPOSTDIV = 0x00;         // PLL CLOCK = VCO CLOCK / (POSTDIV + 1)   
                                
  _asm(nop);  
  _asm(nop);  
    
  CPMUPLL=0x10;               //锁相环调频启用,用以减少噪音  
      
  while(CPMUFLG_LOCK == 0);   //等待PLL稳定     
  CPMUPROT = 0x00;            //关闭保护时钟  
  CPMUCLKS_PLLSEL = 1;        //使能PLL  
 }  
  
void main(void)   
{  
  DDRD = 0xFF;                //设置PD（0-7）方向为输出  
  PORTD = 0xFF;               //设置PD（0-7）输出高电平  
   
  PLL_Init();  
                                
 while(1)  
  {  
    PORTD_PD0 = ~PORTD_PD0;   //LED取反  
    delayms(5000);  
  }              
  
}  
