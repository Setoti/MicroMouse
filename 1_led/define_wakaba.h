#ifndef __DEFINE_WAKABA_H__
#define __DEFINE_WAKABA_H__

#include "iodefine.h"

// reg define
#define LED_RED    PORT1.PODR.BIT.B7
#define LED_GREEN  PORT2.PODR.BIT.B7
#define LED_BLUE   PORTE.PODR.BIT.B3

// others
#define LED_ON   0
#define LED_OFF  1

#endif /* __DEFINE_WAKABA_H__ */
