#include <stdio.h>
#include <tusb.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico_tone.hpp"

unsigned char buffer[85];
uint boventonen[7];
		
unsigned char * readLine() {
    unsigned char u , *p ;
    for (p=buffer, u = getchar() ; u != '\r' && p - buffer <80 ; u = getchar()) putchar(*p++=u);
    *p = 0 ;
	printf("\n") ;
    return buffer;
}


int main() {
	
	char * str ;
	
	
	stdio_init_all();
    while (!tud_cdc_connected()) {sleep_ms(100);}

			
	Tone myPlayer(15);
	Tone myPlayer2(14) ;
	printf("Init Machine & channel!\n");
	int res1 = myPlayer.init(TONE_NON_BLOCKING, false) ;
	int res2 = myPlayer2.init(TONE_NON_BLOCKING, false) ;
	printf("De eerste keer %X, %d:\n", res1, res1);
	printf("De tweede keer %X, %d:\n", res2,res2);
//	printf("De derde keer %d:", myPlayer.init(NON_BLOCKING, false));
	
	while (true) {
	
	printf("Defining color of sound!!\n");
	printf("Grondtoon \% :") ;
	str = (char *)readLine();
	boventonen[0] = atoi(str);
	for (int i = 1; i<7 ; i++) {
		printf("Harmonische %d \% :",i+1);
		str = (char *) readLine() ;
		boventonen[i] = atoi(str);
	};
	
	myPlayer.reconfigure_harmonics(boventonen[0],boventonen[1],boventonen[2],boventonen[3],boventonen[4],boventonen[5],boventonen[6]);
	
	printf("Frequentie (Hz): ");
	str = (char *) readLine() ;
	int frequency = atoi(str);
	printf("Duration (in ms): ");
	str = (char *) readLine() ;
	float duration = (atoi(str) / 1000.0) ;

	gpio_init(17);
	gpio_set_dir(17,GPIO_OUT);

	bool nogeens = true ;
	
	while (nogeens) {

	gpio_put(17,1);
	myPlayer2.tone(2*frequency, duration);
	sleep_ms(500);
	myPlayer.tone(frequency, duration);
	printf("One cycle of %f seconds in progress\n",duration);
	sleep_ms(5000);
	gpio_put(17,0);
	printf("Nogmaals (n/j)?");
	str = (char *)readLine() ;
	if (str[0] != 'j') nogeens = false ;
	};

}
    return 0;

}
