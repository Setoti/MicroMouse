#include "define_wakaba.h"
#include "interface.h"

void main(void){
	unsigned char spk_note_num = 0;

	init_rx631();       // Overall Initialization

	while(1){
		if(g_sw_chg){   // Enter when SW is pressed
			g_sw_chg = 0;
			switch(spk_note_num){
			case 0:
				SPK_Soundout(C5, 50);
				break;
			case 1:
				SPK_Soundout(D5, 50);
				break;
			case 2:
				SPK_Soundout(E5, 50);
				break;
			case 3:
				SPK_Soundout(F5, 50);
				break;
			case 4:
				SPK_Soundout(G5, 50);
				break;
			case 5:
				SPK_Soundout(A5, 50);
				break;
			case 6:
				SPK_Soundout(B5, 50);
				break;
			case 7:
				SPK_Soundout(C6, 50);
				break;
			}
			spk_note_num++;
			spk_note_num = spk_note_num % 8;
		}
	}
}
