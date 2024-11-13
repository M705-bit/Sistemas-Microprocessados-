#include "main.h"
#include <stdio.h>
#include <string.h>
/*
Você deverá criar um um código para o ARM onde irás controlar no mínimo quatro saídas do microcontrolador. Os comandos para controlar as saídas serão recebidos pela porta serial, 
este comando deverá ser uma palavra diferente para cada saída. Ao receber um comando, o microcontrolador deverá enviar uma resposta informando se o comando foi executado.
Também deverá ser criado um software específico para ser utilizado no computador onde serão enviados os comandos e exibidos os retornos do microcontrolador.
*/
int i=0;
char palavra[20], dado_rx;
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

void manda_serial(int a){
	while(!((USART2->SR)&0x80)){};
	USART2->DR=a;
}

int _write(int file, char *ptr, int len){
	int i=0;
	for(i=0 ; i<len ; i++)
		manda_serial((*ptr++));
	return len;
}
/*
void retorna_estado(){
	if(GPIOB->IDR&0x1){
		printf("liga_led");
	}
	else{
		printf("led_desligado");
	}
}*/
void liga_led(char palavra[20]){

	if(strcmp (palavra,"azul")==0){
		GPIOB->ODR=0x1;
		printf("led_ligado\n");
	}
	 if(strcmp (palavra, "amarelo")==0){
		GPIOB->ODR=0x2;
		printf("led_ligado\n");
	}
	 if(strcmp (palavra, "vermelho")==0){
		GPIOB->ODR=0x4;
		printf("led_ligado\n");
	}
	 if(strcmp (palavra, "verde")==0){
		GPIOB->ODR=0x8;
		printf("led_ligado\n");
	}
	 if(strcmp (palavra, "desliga")==0){
			GPIOB->ODR=0x0;
			printf("\ndesliga\n");
		}
}

void USART2_IRQHandler(void) {
	if (USART2->SR & 0x20) {
		dado_rx = USART2->DR;
		if (dado_rx == '$') {
			i = 0;
		} else if (dado_rx == '*') {
			palavra[i] = '\0';
			liga_led(palavra);
			i = 0;
		} else {
			palavra[i++] = dado_rx;
		}

	}
	USART2->SR &= ~(0x20);
}

int main(void)
{

	RCC->AHB1ENR=0x00000087;    //habilitando o clock dos GPIO
	GPIOA->MODER |=0x29555400;    //configurando O PINO A5, preciso configurar o pino a13?
	GPIOB->MODER=0x5555;

	config_serial();

	while (1)
	{

	}
}
