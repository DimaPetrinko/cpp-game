#pragma once

#include <stdint.h>

typedef uint8_t ReturnCode;

#define RETURN_CODE_RUNNING 0xfe
#define RETURN_CODE_NOT_INITIALIZED 0xff
#define RETURN_CODE_EXIT 0x00
#define RETURN_CODE_ERROR 0x01
#define RETURN_CODE_2 0x02
#define RETURN_CODE_3 0x03

#define CallAndReturn(f, c) f; if (c != RETURN_CODE_RUNNING) return
#define CallAndReturnCustom(f, c, t) f; if (c != t) return
#define CallAndBreak(f, c) f; if (c != RETURN_CODE_RUNNING) break
#define CheckAndReturn(c) if (c != RETURN_CODE_RUNNING) return
#define CheckAndReturnCustom(c, t) if (c != t) return
#define CheckAndBreak(c) if (c != RETURN_CODE_RUNNING) break