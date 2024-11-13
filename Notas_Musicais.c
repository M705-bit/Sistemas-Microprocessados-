#include "main.h"
#include "locale.h"
/*A partir do exercíio 9 toque faça com que o ARM toque uma música automaticamente*/
void wait(int tempo){
	TIM11->PSC = 15999;
	TIM11->ARR = tempo - 1;
	TIM11->CNT=0;
	while((TIM11->SR & 0x1) == 0x0){}
	TIM11->SR &= ~0x1;
}

void playmusic(float freq, float tempo){
	TIM10->PSC = 15;
	TIM10->ARR = (1000000.0/freq)-1;
	TIM11->PSC = 15999;
	TIM11->ARR = tempo - 1;
	TIM11->CNT=0;
	while((TIM11->SR & 0x1) == 0x0){
		if(TIM10->SR & 0x1){
			GPIOA->ODR ^= 0x40;
			TIM10->SR &= ~0x1;
		}
	}
	TIM11->SR &= ~0x1;
	TIM10->SR &= ~0x1;
	wait(100); //essencial, pois as notas tem uma pausa entre si
}
int main(void)
{
	setlocale(LC_ALL, "");
	RCC->AHB1ENR=0x87;
	GPIOA->MODER=0x28001000; //A6 output
	RCC->APB2ENR = 1 << 18;
	RCC->APB2ENR |= 1 << 17;
	TIM11->CR1 = 0x1;
	TIM10->CR1 = 0x1;
	int x,tam,i;

	char music[] = "aaeeffe ddccbba eeddccb eeddccb aaeeffe ddccbba ";
	  char name[]= {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
	  float psc[]={261.63, 293.66, 329.63, 349.23, 392, 440};
	//float notes[]= {a,a,e,e,f,f,e};
	tam = sizeof(music)/sizeof(char);
	while(1){
		for(x=0; x<tam; x++){
			if(music[x]==' '){
			wait(250);
			}

			for(i=0; i<7; i++){
					if (music[x]==name[i]){
						playmusic(psc[i], 300);
							}
		}



	}
		wait(5000);
}}
