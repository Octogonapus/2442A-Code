#ifndef ROBOTCVERSIONCHECK_H_INCLUDED
#define ROBOTCVERSIONCHECK_H_INCLUDED

#ifndef kRobotCVersionNumeric
#include "FirmwareVersion.h"
#endif
#if kRobotCVersionNumeric < 351
#error "RobotC Version 3.51 or newer is required"
#endif

#endif
