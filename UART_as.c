#include <lpc17xx.h>

void clock_config(void)
{
	LPC_SC->SCS=(1<<4)|(1<<5);
	LPC_SC->PLL0CON=0;
	LPC_SC->PLL0FEED=0xAA;
	LPC_SC->PLL0FEED=0x55;
	
	while(!(LPC_SC->SCS&(1<<6)));
	
	LPC_SC->CLKSRCSEL=1;			
	LPC_SC->PLL0CFG=0x00F;			   
	LPC_SC->PLL0CON=1;
	LPC_SC->PLL0FEED=0xAA;
	LPC_SC->PLL0FEED=0x55;
	
	LPC_SC->CCLKCFG=3;
	
	while(!(LPC_SC->PLL0STAT&(1<<26))); 
	
	LPC_SC->PLL0CON=(1<<0)|(1<<1);
	LPC_SC->PLL0FEED=0xAA;
	LPC_SC->PLL0FEED=0x55;
}
//void delay(unsigned int d)
//{
//	unsigned int i,j;
//	for(i=0; i<d; i++)
//	{
//		for(j=0;j<3000;j++)
//		{
//		}
//	}
//}
void tx_string(char str )
{
	while(!(LPC_UART0->LSR & (1<<5))); 
	{
		LPC_UART0->THR= str;
		//LPC_UART0->THR= str2;
	}
}
char str[] ="Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for \r\npredicting that the next banking crisis would be triggred by MSME lending, saying postmortem is\r\neasier than taking action when required. Rajan, who had as the chief economist at IMF\r\nwarned of impending financial crisis of 2008, in a note to a parliamentry committee warned\r\nagainst ambitious credit targets and loan waviers, saying that they could be sources of next\r\nbanking crisis. Government should focus on sources of next crisis, not just the last one.\r\n";		
char str2[] ="\nIn particular, government should refrain from setting ambitious credit targets or waving loans.\r\nCredit targets are sometimes achieved by abandoning appropriate due diligence, creaiting the\r\nenvironment for future NPAs,\"Rajan said in the note\".Both MUDRA loans as well as the Kisan\r\nCredit Card, while popular, have to be examined more closely for potential credit risk. Rajan, who\r\n was RBI governor for three years till September 2016, is currently.";	
int main()
{
	
	
	//char str2[] ="In particular, government should refrain from setting ambitious credit targets or waving loans. Credit targets are sometimes achieved by abandoning appropriate due diligence, crediting the environment for future NPAs,Rajan said in the note.Both MUDRA loans as well as the kisan credit card, while popular, have to be examined more closely for potential credit risk. Rajan, who was RBI governor for three years till September 2016, is currently.";
	int i =0, j = 0;
	//lcd_config();
	clock_config();
	
	LPC_PINCON->PINSEL0|=(1<<4)|(1<<6);
	
	LPC_UART0->LCR=0x83;
	LPC_UART0->DLL=73;
	LPC_UART0->DLM=2;
	LPC_UART0->FDR=(1<<0)|(15<<4);
	LPC_UART0->LCR&=~(1<<7);

	for(i =0; str[i] != '\0';i++){
		tx_string(str[i]);
		//delay(1000);
	}
	for(j = 0; str2[j] != '\0'; j++){
		tx_string(str2[j]);
		//delay(1000);
	}
		
	
}
