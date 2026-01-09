#pragma once

/* ============================================================
   WebView2 – PURE C COM HEADER
   BrowserX Minimal ABI
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

/* ============================================================
   ICoreWebView2
   ============================================================ */

typedef struct ICoreWebView2Vtbl {

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2 *This, REFIID riid, void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2 *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2 *This);

    /* BrowserX required */
    HRESULT (STDMETHODCALLTYPE *Navigate)(
        ICoreWebView2 *This, LPCWSTR uri);

    HRESULT (STDMETHODCALLTYPE *NavigateToString)(
        ICoreWebView2 *This, LPCWSTR html);

    HRESULT (STDMETHODCALLTYPE *ExecuteScript)(
        ICoreWebView2 *This,
        LPCWSTR script,
        IUnknown *handler);

    HRESULT (STDMETHODCALLTYPE *Reload)(
        ICoreWebView2 *This);

    HRESULT (STDMETHODCALLTYPE *Stop)(
        ICoreWebView2 *This);

    HRESULT (STDMETHODCALLTYPE *GoBack)(
        ICoreWebView2 *This);

    HRESULT (STDMETHODCALLTYPE *GoForward)(
        ICoreWebView2 *This);

} ICoreWebView2Vtbl;

struct ICoreWebView2 {
    ICoreWebView2Vtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2Controller
   ============================================================ */

typedef struct ICoreWebView2ControllerVtbl {

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Controller *This, REFIID riid, void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2Controller *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2Controller *This);

    /* BrowserX required */
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

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2EnvironmentOptions *This, REFIID riid, void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2EnvironmentOptions *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2EnvironmentOptions *This);

    /* Optional but useful */
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

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Environment *This, REFIID riid, void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2Environment *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2Environment *This);

    /* REQUIRED */
    HRESULT (STDMETHODCALLTYPE *CreateCoreWebView2Controller)(
        ICoreWebView2Environment *This,
        HWND parentWindow,
        IUnknown *handler);

} ICoreWebView2EnvironmentVtbl;

struct ICoreWebView2Environment {
    ICoreWebView2EnvironmentVtbl *lpVtbl;
};

/* ============================================================
   GLOBAL ENTRY POINT (THIS IS CRITICAL)
   ============================================================ */

HRESULT STDMETHODCALLTYPE CreateCoreWebView2EnvironmentWithOptions(
    LPCWSTR browserExecutableFolder,
    LPCWSTR userDataFolder,
    ICoreWebView2EnvironmentOptions *environmentOptions,
    IUnknown *environmentCreatedHandler);

#ifdef __cplusplus
}
#endif
