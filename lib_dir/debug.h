#include "comUART.h"

//#define DEBUG

#ifdef DEBUG
comUART com;
#define DEBUG_PRINT(x) com.sendMessage(x) // ou par RS-232
#else
#define DEBUG_PRINT(x) do {} while (0) // code mort
#endif


