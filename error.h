/**
 * @file   error.h
 * @Author Nicolas Jeker (n.jeker@gmx.net)
 * @date   March 2014
 * @brief  Error handling
 *
 */

#ifndef _ERROR_H_
#define _ERROR_H_

// Defines:
//#define assert(cond) _assert(cond, __LINE__, __FILE__)

// Include standard libraries
#include "board_config.h"

// Global variables/types

typedef enum {
	ERR_NONE = 0,
	ERR_LOOPDELAY,

	ERR_UNKNOWN,
	ERR_MAX
} Error_t;

// Function prototypes
PrintError(Error_t* error);
//void _assert (char cond, unsigned int lineno, far const rom char* filename);

// _ERROR_H_
#endif