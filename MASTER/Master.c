#define __STDC_WANT_LIB_EXT1__ 1
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif
#include <wchar.h>
#include <stdio.h>
#include <locale.h> // For setlocale
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include <stdlib.h>
//#include <string.h>

#include "../include/master.h"

static wchar_t * gwcP;
static char * gacP;

 int countDigits(int n){
        if (n == 0) return 1;
        int count = 0;
        if (n < 0) n = -n; 
        while (n > 0) {
            n /= 10;
            count++;
        }
        return count;
}

char * NUM2STRB(HWND hwnd, long nint){
	setlocale(LC_ALL, "en_US.UTF-8"); // Set a suitable locale
	int dgt;dgt = countDigits(nint)+1;
	char * nstrp;char nstr[dgt];
	nstr[dgt ] = L'\0';nstrp = nstr;
	nstrp = (char *)malloc((dgt ) * sizeof(char));
	
	sprintf(nstrp, "%d", nint);
	char gacPB[dgt];gacPB[dgt ] = L'\0';gacP = gacPB;
	gacP = (char *)malloc((dgt ) * sizeof(char));
	gacP = nstrp;//convACT(hwnd, nstrp, dgt);

	return gacP;
}
char * NUM2STRA(HWND hwnd, int nint){
	setlocale(LC_ALL, "en_US.UTF-8"); // Set a suitable locale
	int dgt;dgt = countDigits(nint)+1;
	char * nstrp;char nstr[dgt];
	nstr[dgt ] = L'\0';nstrp = nstr;
	nstrp = (char *)malloc((dgt ) * sizeof(char));
	
	sprintf(nstrp, "%d", nint);
	char gacPB[dgt];gacPB[dgt ] = L'\0';gacP = gacPB;
	gacP = (char *)malloc((dgt ) * sizeof(char));
	gacP = nstrp;//convACT(hwnd, nstrp, dgt);

	return gacP;
}

wchar_t * NUM2STR(HWND hwnd, int nint){
	setlocale(LC_ALL, "en_US.UTF-8"); // Set a suitable locale
	int dgt;	dgt = countDigits(nint);
	char * nstrp;	char nstr[dgt];
	nstrp = nstr;	sprintf(nstrp, "%d", nint);
	gwcP = convWCT(hwnd, nstrp, dgt);
	return gwcP;
}
wchar_t * convWCT(HWND hwnd,char * STR,int LSTR){ 
	setlocale(LC_ALL, "en_US.UTF-8"); // Set a suitable locale
	wchar_t * wcP;
	wchar_t wcB[LSTR];
	wcP = wcB;
	size_t convertedChars;

	int err = mbstowcs_s(&convertedChars, wcP, LSTR, STR, LSTR);

	if (err == 0) {
	printf("Successfully converted. Converted %zu wide characters.\n", convertedChars);
	wprintf(L"Wide string: %ls\n", wcP);
	//MessageBoxW(hwnd, wcP, L"Converted wcP", 0x00000000L);
	} else {
	printf("Error code: %d\n", err);
	}

	int buffer_size;
	buffer_size = LSTR ;
	wchar_t my_buffer[buffer_size];
	wcsncpy(my_buffer, wcP, buffer_size);
	FREEWT(wcP);
	wcP = NULL;
	return (pbuff( hwnd,STR));
}
wchar_t * pbuff(HWND hwnd,char * STR) {

	setlocale(LC_ALL, "en_US.UTF-8"); // Set a suitable locale
	const char * multiByteString = STR;
	wchar_t * wideStringBuffer = NULL;
	size_t requiredSizeInWords = 0;
	int sz_str;
	sz_str = strlen(multiByteString) ;
	errno_t err;

	err = mbstowcs_s(&requiredSizeInWords, NULL, 0, multiByteString, sz_str);

	if (err != 0) {
	//perror("Failed to determine required buffer size");
	return L"EXIT_FAILURE 1";
	}

	printf("Required buffer size (in wchar_t units): %zu\n", requiredSizeInWords);

	wideStringBuffer = (wchar_t *)malloc(requiredSizeInWords + 1 * sizeof(wchar_t));

	if (wideStringBuffer == NULL) {
	//perror("Failed to allocate memory");
	return L"EXIT_FAILURE 2";
	}

	size_t convertedCharsCount = 0;
	err = mbstowcs_s(&convertedCharsCount, wideStringBuffer, requiredSizeInWords, multiByteString, sz_str);

	if (err != 0) {
	// perror("Failed to convert multibyte string to wide string");
	return L"EXIT_FAILURE 3";
	}
	//printf("Converted wide string: %ls\n", wideStringBuffer);
	//printf("Number of characters converted (including null terminator): %zu\n", convertedCharsCount);

	size_t buffer_size;
	buffer_size = sz_str + 1;
	wchar_t gwcPb[buffer_size];
	gwcP = gwcPb;
	gwcP = (wchar_t *)malloc((requiredSizeInWords + 1) * sizeof(wchar_t));
	wcsncpy(gwcP, wideStringBuffer, buffer_size);
	gwcP[buffer_size] = L'\0';
	//MessageBoxW(hwnd, gwcP, L"Converted gwcP", 0x00000000L);
	free(wideStringBuffer);
	wideStringBuffer = NULL; // Good practice to set pointer to NULL after freeing

    return (gwcP);
}
void FREEWT(wchar_t * wcP){
	wcP=NULL;free(wcP);wcP=NULL;
}
