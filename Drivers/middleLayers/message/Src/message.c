#include "xprintf.h"
#include <stdarg.h>

#define message(type,fmt, ...) _msg(type,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

const char *HalStatus_m[] = {
  "HAL_OK",
  "HAL_ERROR",
  "HAL_BUSY",
  "HAL_TIMEOUT"
};

  
static
void _xprintf(char *fmt,...);

static
char buff[1024];


void MW_printf(const char* fmt,...){
    va_list arp;
    va_start(arp, fmt);
    xvprintf(fmt, arp);
    va_end(arp);
}

void _msg(const char* type,
	  const char* file,
	  const char* func,
	  int line,
	  const char* fmt,
	  ...){
  _xprintf("%-10s %-10s %-3d %-8s ",file,func,line,type);

  {
    va_list arp;
    va_start(arp, fmt);
    xvprintf(fmt, arp);
    va_end(arp);
  }

  _xprintf("\n");
}

void flush(void){
  if(outptr!=0){
    MW_Puts(buff,outptr-buff); 
  }
  outptr=buff;
}

static
void _xprintf(char *fmt,...){
  va_list arp;
  va_start(arp, fmt);
  xvprintf(fmt, arp);
  va_end(arp);
}
