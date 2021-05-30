#ifndef __DEFINE_WAKABA_H__
#define __DEFINE_WAKABA_H__

#include "iodefine.h"

// reg define
#define LED_RED    PORT1.PODR.BIT.B7
#define LED_GREEN  PORT2.PODR.BIT.B7
#define LED_BLUE   PORTE.PODR.BIT.B3

#define PUSH_SW    PORT3.PIDR.BIT.B5


#endif /* __DEFINE_WAKABA_H__ */
