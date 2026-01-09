#pragma once
/* ============================================================
   WebView2_CAPI.h
   Unified Pure-C WebView2 COM API
   ANSI C (C89/C90) – Pelles C Compatible
   ============================================================ */

#include <windows.h>
#include <ole2.h>
#include <Unknwn.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================
   FORWARD DECLARATIONS
   ============================================================ */

typedef struct ICoreWebView2 ICoreWebView2;
typedef struct ICoreWebView2Controller ICoreWebView2Controller;
typedef struct ICoreWebView2Environment ICoreWebView2Environment;
typedef struct ICoreWebView2EnvironmentOptions ICoreWebView2EnvironmentOptions;

typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler;

typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler;

typedef struct ICoreWebView2ExecuteScriptCompletedHandler
    ICoreWebView2ExecuteScriptCompletedHandler;

/* ============================================================
   COMMON COM BASE (REFCOUNTING)
   ============================================================ */

typedef struct {
    LONG refCount;
} COM_Base;

static ULONG STDMETHODCALLTYPE COM_Base_AddRef(COM_Base *base)
{
    return InterlockedIncrement(&base->refCount);
}

static ULONG STDMETHODCALLTYPE COM_Base_Release(COM_Base *base)
{
    LONG ref = InterlockedDecrement(&base->refCount);
    if (ref == 0) {
        CoTaskMemFree(base);
    }
    return ref;
}

/* ============================================================
   ICoreWebView2
   ============================================================ */

typedef struct ICoreWebView2Vtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2 *This, REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2 *This);
    ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2 *This);

    HRESULT (STDMETHODCALLTYPE *Navigate)(
        ICoreWebView2 *This, LPCWSTR uri);

    HRESULT (STDMETHODCALLTYPE *NavigateToString)(
        ICoreWebView2 *This, LPCWSTR htmlContent);

    HRESULT (STDMETHODCALLTYPE *ExecuteScript)(
        ICoreWebView2 *This,
        LPCWSTR javaScript,
        IUnknown *handler);

    HRESULT (STDMETHODCALLTYPE *Reload)(ICoreWebView2 *This);
    HRESULT (STDMETHODCALLTYPE *Stop)(ICoreWebView2 *This);
    HRESULT (STDMETHODCALLTYPE *GoBack)(ICoreWebView2 *This);
    HRESULT (STDMETHODCALLTYPE *GoForward)(ICoreWebView2 *This);

} ICoreWebView2Vtbl;

struct ICoreWebView2 {
    ICoreWebView2Vtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2Controller
   ============================================================ */

typedef struct ICoreWebView2ControllerVtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Controller *This, REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Controller *This);
    ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Controller *This);

    HRESULT (STDMETHODCALLTYPE *get_IsVisible)(
        ICoreWebView2Controller *This, BOOL *value);
    HRESULT (STDMETHODCALLTYPE *put_IsVisible)(
        ICoreWebView2Controller *This, BOOL value);

    HRESULT (STDMETHODCALLTYPE *get_Bounds)(
        ICoreWebView2Controller *This, RECT *bounds);
    HRESULT (STDMETHODCALLTYPE *put_Bounds)(
        ICoreWebView2Controller *This, RECT bounds);

    HRESULT (STDMETHODCALLTYPE *get_CoreWebView2)(
        ICoreWebView2Controller *This,
        ICoreWebView2 **coreWebView2);

} ICoreWebView2ControllerVtbl;

struct ICoreWebView2Controller {
    ICoreWebView2ControllerVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2EnvironmentOptions
   ============================================================ */

typedef struct ICoreWebView2EnvironmentOptionsVtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2EnvironmentOptions *This, REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2EnvironmentOptions *This);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2EnvironmentOptions *This);

    HRESULT (STDMETHODCALLTYPE *get_AdditionalBrowserArguments)(
        ICoreWebView2EnvironmentOptions *This, LPWSTR *value);
    HRESULT (STDMETHODCALLTYPE *put_AdditionalBrowserArguments)(
        ICoreWebView2EnvironmentOptions *This, LPCWSTR value);

    HRESULT (STDMETHODCALLTYPE *get_Language)(
        ICoreWebView2EnvironmentOptions *This, LPWSTR *value);
    HRESULT (STDMETHODCALLTYPE *put_Language)(
        ICoreWebView2EnvironmentOptions *This, LPCWSTR value);

} ICoreWebView2EnvironmentOptionsVtbl;

struct ICoreWebView2EnvironmentOptions {
    ICoreWebView2EnvironmentOptionsVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2Environment
   ============================================================ */

typedef struct ICoreWebView2EnvironmentVtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Environment *This, REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Environment *This);
    ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Environment *This);

    HRESULT (STDMETHODCALLTYPE *CreateCoreWebView2Controller)(
        ICoreWebView2Environment *This,
        HWND parentWindow,
        IUnknown *handler);

} ICoreWebView2EnvironmentVtbl;

struct ICoreWebView2Environment {
    ICoreWebView2EnvironmentVtbl *lpVtbl;
};

/* ============================================================
   CALLBACK HANDLER INTERFACES
   ============================================================ */

typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This,
        REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This,
        HRESULT result,
        ICoreWebView2Environment *environment);

} ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl;

struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler {
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl *lpVtbl;
};

typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This,
        REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This,
        HRESULT result,
        ICoreWebView2Controller *controller);

} ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl;

struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler {
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl *lpVtbl;
};

typedef struct ICoreWebView2ExecuteScriptCompletedHandlerVtbl {

    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2ExecuteScriptCompletedHandler *This,
        REFIID riid, void **ppvObject);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2ExecuteScriptCompletedHandler *This);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2ExecuteScriptCompletedHandler *This);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2ExecuteScriptCompletedHandler *This,
        HRESULT errorCode,
        LPCWSTR resultObjectAsJson);

} ICoreWebView2ExecuteScriptCompletedHandlerVtbl;

struct ICoreWebView2ExecuteScriptCompletedHandler {
    ICoreWebView2ExecuteScriptCompletedHandlerVtbl *lpVtbl;
};

/* ============================================================
   CONCRETE HANDLER STRUCTS
   ============================================================ */

typedef struct {
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler iface;
    COM_Base base;
    ICoreWebView2Environment **outEnv;
} WebView2_EnvHandler;

typedef struct {
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler iface;
    COM_Base base;
    ICoreWebView2Controller **outController;
} WebView2_ControllerHandler;

typedef struct {
    ICoreWebView2ExecuteScriptCompletedHandler iface;
    COM_Base base;
    LPWSTR *outResult;
} WebView2_ScriptHandler;

/* ============================================================
   GLOBAL CREATION ENTRY POINT
   ============================================================ */

HRESULT STDMETHODCALLTYPE CreateCoreWebView2EnvironmentWithOptions(
    LPCWSTR browserExecutableFolder,
    LPCWSTR userDataFolder,
    ICoreWebView2EnvironmentOptions *environmentOptions,
    IUnknown *environmentCreatedHandler);

#ifdef __cplusplus
}
#endif
