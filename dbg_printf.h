#ifndef DBG_PRINTF_H
#define DBG_PRINTF_H

#ifdef DEBUG
# include <stdio.h>
# define dbg_printf printf
#else
# define dbg_printf ignore_printf
void ignore_printf (char *string, ...)
{
  (void) string;
}
#endif

#endif
