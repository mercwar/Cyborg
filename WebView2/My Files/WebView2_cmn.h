#include <windows.h>
#include <ole2.h>
#include "WebView2.h"

/* ============================================================
   COM BASE
   ============================================================ */

typedef struct {
    LONG refCount;
} COM_Base;

static ULONG STDMETHODCALLTYPE Base_AddRef(COM_Base *base)
{
    return InterlockedIncrement(&base->refCount);
}

static ULONG STDMETHODCALLTYPE Base_Release(COM_Base *base)
{
    LONG ref = InterlockedDecrement(&base->refCount);
    if (ref == 0) {
        CoTaskMemFree(base);
    }
    return ref;
}
