#include <windows.h>
#include <stdio.h>
#include <stdlib.h> // For mbstowcs_s
#include <wchar.h>  // For wchar_t, wcslen
wchar_t *   NUM2STR(HWND,int);
char * NUM2STRA(HWND , int );
char * NUM2STRB(HWND , long);
 int countDigits(int);
wchar_t * convWCT(HWND,char *,int );
void FREEWT(wchar_t *);
wchar_t * pbuff(HWND hwnd,char * STR );
