
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico_tone.hpp"


int main() {
	
	uint melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
	uint values[] = {4,       8,       8,       4,       4,       4, 4,       4      };	
	
	Tone myPlayer(15,50,0,20,0,20,0,10);
	Tone myPlayer2(14) ;
	myPlayer.init(TONE_NON_BLOCKING) ;
	myPlayer2.init(TONE_NON_BLOCKING) ;
	
	while (true) {

	myPlayer.play_melody(T_PRESTO,8,melody,values);
	myPlayer2.tone(NOTE_FS4, 2.0);
	sleep_ms(4000);

	};
    return 0;
}
