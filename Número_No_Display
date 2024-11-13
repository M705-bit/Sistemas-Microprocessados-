#include "main.h"
#include <stdio.h>
#include <string.h>

int display[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
int lixo=0;
//@brief: lixo é variável global

void config_serial(void){
    //configurando a porta serial assincrona
    RCC->APB1ENR|=0x20000;   // a usart2 é configurada no bit 17
    GPIOA->MODER|=0xA0; //Configurando Pino A2 e A3 como função alternativa
    GPIOA->AFR[0]|=0x07700;//ativando a função alternativa usart2 nos pinos PA2 e PA3. AFR é alternate function selection,
    //e a função alternativa que é tanto para o receptor quanto transmissor da usart2 é AFR7
    USART2->CR1|=0x202C; //0x200C; ativando interrupção recepção
    USART2->CR2=0;
    USART2->CR3=0;
    USART2->BRR|=(104<<4);//16MHz/(16*9600); //configurando o baud rate, que é a taixa de oscilação
    NVIC_SetPriority(USART2_IRQn, 1); //iniciando as interrupçoes
     NVIC_EnableIRQ(USART2_IRQn);
}

// essa função irá receber um parâmetro 'a', ele representa o tamanho da nossa mensagem, ou seja os bits mensagem
void manda_serial(int a){
    while(!((USART2->SR)&0x80)){}; //aguarda todos os bits de mensagem terem sido setados
    USART2->DR=a; // o data register da usart receberá o bit
}

int _write(int file, char *ptr, int len){

	/* Implement your write code here, this is used 0by puts and printf for example */
	int i=0;
	for(i=0 ; i<len ; i++)
	manda_serial((*ptr++));
	return len;
}

//essa é a função de interrupção da usart ela vai dar a variável lixo o dado recebido pela comunicação serial
//if (USART2->SR & 0x20) verifica se o bit de "receive data register not empty" (RXNE) foi acionado. Este bit é
//setado quando dados são recebidos e estão disponíveis para leitura no registrador de dados da USART2 (USART2->DR).
void USART2_IRQHandler(void) {
if (USART2->SR&0x20){
lixo=USART2->DR;
USART2->SR&=~(0x20);
}
}


int main(void)
{

	RCC->AHB1ENR=0x00000087;    //habilitando o clock dos GPIO
  GPIOA->MODER |=0x29555400;    //configurando O PINO A5, preciso configurar o pino a13?
    GPIOC->MODER |=0x05000000; //LED no PC13/
    GPIOB->MODER=0x5555;
//chama a função que inicializa a usart
    config_serial();

    while (1)
    { /*O loop while(1) no main() está constantemente verificando se há algum caractere recebido na comunicação serial.
    Se um caractere for recebido (armazenado na variável lixo), ele é exibido no console (usando printf) e, dependendo
    do caractere, o LED é ligado ou desligado.*/
    	if(lixo!=0) {
    		printf("%c\r", lixo);
    	if(lixo=='0') {
    		GPIOB->ODR=display[0];
    	}
    	if(lixo=='1') {
    		GPIOB->ODR=display[1];
    	}
    	if(lixo=='2') {
    		GPIOB->ODR=display[2];
    	}
    	if(lixo=='3') {
    		GPIOB->ODR=display[3];
    	}
    	if(lixo=='4') {
    		GPIOB->ODR=display[4];
    	}
    	if(lixo=='5') {
    		GPIOB->ODR=display[5];
    	}
    	if(lixo=='6') {
    		GPIOB->ODR=display[6];
    	}
    	if(lixo=='7') {
    		GPIOB->ODR=display[7];
    	}
    	if(lixo=='8') {
    		GPIOB->ODR=display[8];
    	}
    	if(lixo=='9') {
    		GPIOB->ODR=display[9];
    	}
    	if(lixo=='z') {
    		GPIOA->ODR=0x020;
    	}
    	if(lixo=='x') {
    		GPIOA->ODR=0x0;
    	}
    }
}
}
