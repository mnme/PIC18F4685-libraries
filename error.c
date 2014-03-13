/**
 * @file   error.c
 * @Author Nicolas Jeker (n.jeker@gmx.net)
 * @date   March 2014
 * @brief  Error handling
 *
 */

// Includes

#include "error.h"

// Global functions


const static char* Errors[] = {
	"Success",
	"Loopdelay stuck",
	"Unknown Error",
	""
};

PrintError(Error_t* error)
{
	printf("\f%s", Errors[(int)error]);
}