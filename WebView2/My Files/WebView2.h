#pragma once
/* ============================================================
   WebView2.h
   Pure ANSI C (C89/C90) WebView2 COM API
   Classic COM (lpVtbl) – Pelles C compatible

   DESIGN GOALS
   ------------
   • NO WinRT
   • NO C++ / templates
   • NO EventToken.h
   • NO rpc.h / rpcndr.h
   • NO MIDL / IDL-generated constructs
   • ABI-faithful to Microsoft WebView2
   • Single, self-contained header

   This header intentionally mirrors the *logical* WebView2 COM
   surface used for:
     - Environment creation
     - Controller creation
     - Navigation
     - Document title / source
     - Settings
     - Script execution
     - Navigation completed events

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
typedef struct ICoreWebView2Settings ICoreWebView2Settings;

typedef struct ICoreWebView2NavigationCompletedEventHandler
    ICoreWebView2NavigationCompletedEventHandler;
typedef struct ICoreWebView2NavigationCompletedEventArgs
    ICoreWebView2NavigationCompletedEventArgs;

typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler;
typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler;
typedef struct ICoreWebView2ExecuteScriptCompletedHandler
    ICoreWebView2ExecuteScriptCompletedHandler;

/* ============================================================
   COMMON COM BASE
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
    LONG r = InterlockedDecrement(&base->refCount);
    if (r == 0) {
        CoTaskMemFree(base);
    }
    return r;
}

/* ============================================================
   ENUMS
   ============================================================ */

typedef enum COREWEBVIEW2_NAVIGATION_KIND {
    COREWEBVIEW2_NAVIGATION_KIND_NEW_DOCUMENT = 0,
    COREWEBVIEW2_NAVIGATION_KIND_BACK        = 1,
    COREWEBVIEW2_NAVIGATION_KIND_FORWARD     = 2,
    COREWEBVIEW2_NAVIGATION_KIND_RELOAD      = 3
} COREWEBVIEW2_NAVIGATION_KIND;

/* ============================================================
   ICoreWebView2Settings
   ============================================================ */

typedef struct ICoreWebView2SettingsVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Settings*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Settings*);
    ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Settings*);

    HRESULT (STDMETHODCALLTYPE *get_IsScriptEnabled)(
        ICoreWebView2Settings*, BOOL*);
    HRESULT (STDMETHODCALLTYPE *put_IsScriptEnabled)(
        ICoreWebView2Settings*, BOOL);

    HRESULT (STDMETHODCALLTYPE *get_IsWebMessageEnabled)(
        ICoreWebView2Settings*, BOOL*);
    HRESULT (STDMETHODCALLTYPE *put_IsWebMessageEnabled)(
        ICoreWebView2Settings*, BOOL);
} ICoreWebView2SettingsVtbl;

struct ICoreWebView2Settings {
    ICoreWebView2SettingsVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2  (MAIN WEBVIEW INTERFACE)
   ============================================================ */

typedef struct ICoreWebView2Vtbl {
    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2*);
    ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2*);

    /* Navigation */
    HRESULT (STDMETHODCALLTYPE *Navigate)(
        ICoreWebView2*, LPCWSTR);
    HRESULT (STDMETHODCALLTYPE *NavigateToString)(
        ICoreWebView2*, LPCWSTR);

    /* Script */
    HRESULT (STDMETHODCALLTYPE *ExecuteScript)(
        ICoreWebView2*, LPCWSTR, IUnknown*);

    /* History / control */
    HRESULT (STDMETHODCALLTYPE *Reload)(ICoreWebView2*);
    HRESULT (STDMETHODCALLTYPE *Stop)(ICoreWebView2*);
    HRESULT (STDMETHODCALLTYPE *GoBack)(ICoreWebView2*);
    HRESULT (STDMETHODCALLTYPE *GoForward)(ICoreWebView2*);

    /* IMPORTANT PROPERTIES (THIS IS WHAT COPILOT COMPLAINED ABOUT) */
    HRESULT (STDMETHODCALLTYPE *get_DocumentTitle)(
        ICoreWebView2*, LPWSTR*);
    HRESULT (STDMETHODCALLTYPE *get_Source)(
        ICoreWebView2*, LPWSTR*);

    /* Settings */
    HRESULT (STDMETHODCALLTYPE *get_Settings)(
        ICoreWebView2*, ICoreWebView2Settings**);

    /* Events */
    HRESULT (STDMETHODCALLTYPE *add_NavigationCompleted)(
        ICoreWebView2*,
        ICoreWebView2NavigationCompletedEventHandler*,
        DWORD*);
    HRESULT (STDMETHODCALLTYPE *remove_NavigationCompleted)(
        ICoreWebView2*, DWORD);

} ICoreWebView2Vtbl;

struct ICoreWebView2 {
    ICoreWebView2Vtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2Controller
   ============================================================ */

typedef struct ICoreWebView2ControllerVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Controller*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Controller*);
    ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Controller*);

    HRESULT (STDMETHODCALLTYPE *get_IsVisible)(
        ICoreWebView2Controller*, BOOL*);
    HRESULT (STDMETHODCALLTYPE *put_IsVisible)(
        ICoreWebView2Controller*, BOOL);

    HRESULT (STDMETHODCALLTYPE *get_Bounds)(
        ICoreWebView2Controller*, RECT*);
    HRESULT (STDMETHODCALLTYPE *put_Bounds)(
        ICoreWebView2Controller*, RECT);

    HRESULT (STDMETHODCALLTYPE *get_CoreWebView2)(
        ICoreWebView2Controller*, ICoreWebView2**);
} ICoreWebView2ControllerVtbl;

struct ICoreWebView2Controller {
    ICoreWebView2ControllerVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2EnvironmentOptions
   ============================================================ */

typedef struct ICoreWebView2EnvironmentOptionsVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2EnvironmentOptions*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2EnvironmentOptions*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2EnvironmentOptions*);

    HRESULT (STDMETHODCALLTYPE *get_AdditionalBrowserArguments)(
        ICoreWebView2EnvironmentOptions*, LPWSTR*);
    HRESULT (STDMETHODCALLTYPE *put_AdditionalBrowserArguments)(
        ICoreWebView2EnvironmentOptions*, LPCWSTR);

    HRESULT (STDMETHODCALLTYPE *get_Language)(
        ICoreWebView2EnvironmentOptions*, LPWSTR*);
    HRESULT (STDMETHODCALLTYPE *put_Language)(
        ICoreWebView2EnvironmentOptions*, LPCWSTR);
} ICoreWebView2EnvironmentOptionsVtbl;

struct ICoreWebView2EnvironmentOptions {
    ICoreWebView2EnvironmentOptionsVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2Environment
   ============================================================ */

typedef struct ICoreWebView2EnvironmentVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2Environment*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2Environment*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2Environment*);

    HRESULT (STDMETHODCALLTYPE *CreateCoreWebView2Controller)(
        ICoreWebView2Environment*, HWND, IUnknown*);
} ICoreWebView2EnvironmentVtbl;

struct ICoreWebView2Environment {
    ICoreWebView2EnvironmentVtbl *lpVtbl;
};

/* ============================================================
   NAVIGATION COMPLETED EVENT
   ============================================================ */

typedef struct ICoreWebView2NavigationCompletedEventArgsVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2NavigationCompletedEventArgs*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2NavigationCompletedEventArgs*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2NavigationCompletedEventArgs*);

    HRESULT (STDMETHODCALLTYPE *get_IsSuccess)(
        ICoreWebView2NavigationCompletedEventArgs*, BOOL*);
    HRESULT (STDMETHODCALLTYPE *get_NavigationId)(
        ICoreWebView2NavigationCompletedEventArgs*, UINT64*);
} ICoreWebView2NavigationCompletedEventArgsVtbl;

struct ICoreWebView2NavigationCompletedEventArgs {
    ICoreWebView2NavigationCompletedEventArgsVtbl *lpVtbl;
};

typedef struct ICoreWebView2NavigationCompletedEventHandlerVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2NavigationCompletedEventHandler*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2NavigationCompletedEventHandler*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2NavigationCompletedEventHandler*);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2NavigationCompletedEventHandler*,
        ICoreWebView2*,
        ICoreWebView2NavigationCompletedEventArgs*);
} ICoreWebView2NavigationCompletedEventHandlerVtbl;

struct ICoreWebView2NavigationCompletedEventHandler {
    ICoreWebView2NavigationCompletedEventHandlerVtbl *lpVtbl;
};

/* ============================================================
   ASYNC COMPLETION HANDLERS
   ============================================================ */

typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler*,
        REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler*);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler*,
        HRESULT,
        ICoreWebView2Environment*);
} ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl;

struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler {
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl *lpVtbl;
};

typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler*,
        REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler*);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler*,
        HRESULT,
        ICoreWebView2Controller*);
} ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl;

struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler {
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl *lpVtbl;
};

typedef struct ICoreWebView2ExecuteScriptCompletedHandlerVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2ExecuteScriptCompletedHandler*, REFIID, void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2ExecuteScriptCompletedHandler*);
    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2ExecuteScriptCompletedHandler*);

    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2ExecuteScriptCompletedHandler*,
        HRESULT,
        LPCWSTR);
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
} EnvironmentCompletedHandler;

typedef struct {
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler iface;
    COM_Base base;
    ICoreWebView2Controller **outController;
} ControllerCompletedHandler;

typedef struct {
    ICoreWebView2ExecuteScriptCompletedHandler iface;
    COM_Base base;
    LPWSTR *outResult;
} ScriptCompletedHandler;

/* ============================================================
   GLOBAL ENTRY POINT
   ============================================================ */

HRESULT STDMETHODCALLTYPE CreateCoreWebView2EnvironmentWithOptions(
    LPCWSTR browserExecutableFolder,
    LPCWSTR userDataFolder,
    ICoreWebView2EnvironmentOptions *environmentOptions,
    IUnknown *environmentCreatedHandler);

#ifdef __cplusplus
}
#endif
