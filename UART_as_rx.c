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
char Uart0_rx_data[1010];
void tx_data(char data)
{
	while(!(LPC_UART0->LSR & (1<<5)));
	LPC_UART0->THR = data;
}
void rx_string(char *str, int *index, int size)
{
	while(*index < size)
	{
		while(!(LPC_UART0->LSR & (1<<0)));
		str[*index] = LPC_UART0->RBR;
		tx_data(str[*index]);
		(*index)++;
		if(str[*index -1 ] =='\0')
		{
		break;
		}
	}
}
void uart_tx_string(char *final)
{
	while(*final != '\0')
	{
		tx_data(*final);
		final++;
	}
}

int main()
{
	int i=0;
	clock_config();
	LPC_PINCON->PINSEL0|=(1<<4)|(1<<6);
	LPC_UART0->LCR=0x83;
	LPC_UART0->DLL=73;
	LPC_UART0->DLM=2;
	LPC_UART0->FDR=(1<<0)|(15<<4);
	LPC_UART0->LCR&=~(1<<7);
	while(1)
	{
		rx_string(Uart0_rx_data,&i, 1010);
		if(Uart0_rx_data[i - 1] == '\0')
		{
		  	uart_tx_string(Uart0_rx_data);
		}
		//tx_data(Uart0_rx_data[i]);
		
	}
	//delay(1000);
		
}