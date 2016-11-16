#define FOSC 1843200
#define BAUD 9600
#define MYUBBR FOSC/16/BAUD-1

void USART_Init(unsigned int ubbr)
{
	UBRR0H = (unsigned char)(ubbr>>8);
	UBRR0L = (unsigned char)ubbr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_transmit(unsigned char data)
{
	while(!(UCSR0A) & (1<<UDRE0));
	UDR0=data;
}

unsigned char USART_receive(void)
{
	while(!(UCSR0A) & (1<<RXC0));
	return UDR0;
}


void main()
{
	USART_Init(MYUBBR);
	USART_transmit(0x39);
	unsigned char a = USART_receive();
}
