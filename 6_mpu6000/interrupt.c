#pragma section P PIntPRG

/*** Function Declaration ***/
static void CMT0_CMI0(void);  // CMT0 CMI0

volatile unsigned char g_flag;

// CMT0 CMI0v
// Check the status of the switch
#pragma interrupt (CMT0_CMI0(vect=28))
void CMT0_CMI0(void){
	g_flag=1;
}
