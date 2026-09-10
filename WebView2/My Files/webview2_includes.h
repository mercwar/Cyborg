#ifndef WEBVIEW2_INCLUDES_H
#define WEBVIEW2_INCLUDES_H

/* ---------------------------------------------------------
   WebView2 include wrapper for BrowserX
   Clean, safe, and compatible with the new system.
--------------------------------------------------------- */

#define WIN32_LEAN_AND_MEAN
#define CINTERFACE
#define COBJMACROS

#include <windows.h>
#include <ole2.h>

/* The ONLY WebView2 header you use now */
#include "include/WebView2_v00.01.h"

//#include "include/WebView2_alt.h"
//#include "include/WebView2_c.h"
//#include "include/WebView2_capi.h"
//#include "include/WebView2_cbh.h"
//#include "include/WebView2_ctrl.h"
//#include "include/WebView2_cmn.h"
//#include "include/WebView2_exe.h"

/* All old experimental headers intentionally removed */

#endif /* WEBVIEW2_INCLUDES_H */


