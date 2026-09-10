////#ifndef WEBVIEW2_C_H
////#define WEBVIEW2_C_H

////#define CINTERFACE
////#define COBJMACROS

////#include <windows.h>
////#include <objidl.h>    /* IStream */
////#include <oleauto.h>   /* VARIANT */

/////* ---------------------------------------------------------
   ////Basic COM / WebView2 typedefs
////--------------------------------------------------------- */

////#ifndef __IUnknown_FWD_DEFINED__
////#define __IUnknown_FWD_DEFINED__
////struct IUnknown;
////typedef struct IUnknown IUnknown;
////#endif

////#ifndef __IUnknown_INTERFACE_DEFINED__
////#define __IUnknown_INTERFACE_DEFINED__

////typedef struct IUnknownVtbl {
    ////HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ////IUnknown *This,
        ////REFIID riid,
        ////void **ppvObject);

    ////ULONG (STDMETHODCALLTYPE *AddRef)(IUnknown *This);
    ////ULONG (STDMETHODCALLTYPE *Release)(IUnknown *This);
////} IUnknownVtbl;

////struct IUnknown {
    ////const IUnknownVtbl *lpVtbl;
////};

////#endif /* __IUnknown_INTERFACE_DEFINED__ */

/////* Event token */
////typedef struct EventRegistrationToken {
    ////__int64 value;
////} EventRegistrationToken;

/////* Minimal substitutes */
////typedef int COREWEBVIEW2_MOVE_FOCUS_REASON;
////typedef int COREWEBVIEW2_CAPTURE_PREVIEW_IMAGE_FORMAT;
////typedef int COREWEBVIEW2_WEB_RESOURCE_CONTEXT;

////typedef struct COREWEBVIEW2_COLOR {
    ////BYTE A, R, G, B;
////} COREWEBVIEW2_COLOR;

/////* ---------------------------------------------------------
   ////Forward declarations
////--------------------------------------------------------- */
////struct ICoreWebView2;
////typedef struct ICoreWebView2 ICoreWebView2;

////struct ICoreWebView2Settings;
////typedef struct ICoreWebView2Settings ICoreWebView2Settings;

////struct ICoreWebView2Environment;
////typedef struct ICoreWebView2Environment ICoreWebView2Environment;

////struct ICoreWebView2Controller;
////typedef struct ICoreWebView2Controller ICoreWebView2Controller;

////struct ICoreWebView2Controller2;
////typedef struct ICoreWebView2Controller2 ICoreWebView2Controller2;

////struct ICoreWebView2EnvironmentOptions;
////typedef struct ICoreWebView2EnvironmentOptions ICoreWebView2EnvironmentOptions;

/////* Event handlers */
////struct ICoreWebView2NavigationCompletedEventHandler;
////typedef struct ICoreWebView2NavigationCompletedEventHandler ICoreWebView2NavigationCompletedEventHandler;

////struct ICoreWebView2NavigationCompletedEventArgs;
////typedef struct ICoreWebView2NavigationCompletedEventArgs ICoreWebView2NavigationCompletedEventArgs;

/////* Completion handlers */
////struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler;
////typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler;

////struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler;
////typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler ICoreWebView2CreateCoreWebView2ControllerCompletedHandler;

/////* ---------------------------------------------------------
   ////GUID externs
////--------------------------------------------------------- */
////#ifdef __cplusplus
////extern "C" {
////#endif

////extern const GUID IID_ICoreWebView2Environment;
////extern const GUID IID_ICoreWebView2Controller;
////extern const GUID IID_ICoreWebView2;
////extern const GUID IID_ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler;
////extern const GUID IID_ICoreWebView2CreateCoreWebView2ControllerCompletedHandler;

////#ifdef __cplusplus
////}
////#endif

/////* ---------------------------------------------------------
   ////Example interface definition (Settings)
////--------------------------------------------------------- */
////typedef struct ICoreWebView2SettingsVtbl {
    ////HRESULT (STDMETHODCALLTYPE *QueryInterface)(ICoreWebView2Settings *This, REFIID riid, void **ppvObject);
    ////ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Settings *This);
    ////ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Settings *This);
////} ICoreWebView2SettingsVtbl;

////struct ICoreWebView2Settings {
    ////const ICoreWebView2SettingsVtbl *lpVtbl;
////};

/////* ---------------------------------------------------------
   ////EnvironmentOptions
////--------------------------------------------------------- */
////typedef struct ICoreWebView2EnvironmentOptionsVtbl {
    ////HRESULT (STDMETHODCALLTYPE *QueryInterface)(ICoreWebView2EnvironmentOptions *This, REFIID riid, void **ppvObject);
    ////ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2EnvironmentOptions *This);
    ////ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2EnvironmentOptions *This);
////} ICoreWebView2EnvironmentOptionsVtbl;

////struct ICoreWebView2EnvironmentOptions {
    ////const ICoreWebView2EnvironmentOptionsVtbl *lpVtbl;
////};

/////* ---------------------------------------------------------
   ////Environment
////--------------------------------------------------------- */
////typedef struct ICoreWebView2EnvironmentVtbl {
    ////HRESULT (STDMETHODCALLTYPE *QueryInterface)(ICoreWebView2Environment *This, REFIID riid, void **ppvObject);
    ////ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Environment *This);
    ////ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Environment *This);
    ////HRESULT (STDMETHODCALLTYPE *CreateCoreWebView2Controller)(ICoreWebView2Environment *This, HWND parentWindow, ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *handler);
////} ICoreWebView2EnvironmentVtbl;

////struct ICoreWebView2Environment {
    ////const ICoreWebView2EnvironmentVtbl *lpVtbl;
////};

/////* ---------------------------------------------------------
   ////Controller
////--------------------------------------------------------- */
////typedef struct ICoreWebView2ControllerVtbl {
    ////HRESULT (STDMETHODCALLTYPE *QueryInterface)(ICoreWebView2Controller *This, REFIID riid, void **ppvObject);
    ////ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2Controller *This);
    ////ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2Controller *This);
    ////HRESULT (STDMETHODCALLTYPE *get_CoreWebView2)(ICoreWebView2Controller *This, ICoreWebView2 **coreWebView2);
////} ICoreWebView2ControllerVtbl;

////struct ICoreWebView2Controller {
    ////const ICoreWebView2ControllerVtbl *lpVtbl;
////};

/////* ---------------------------------------------------------
   ////CoreWebView2
////--------------------------------------------------------- */
////typedef struct ICoreWebView2Vtbl {
    ////HRESULT (STDMETHODCALLTYPE *QueryInterface)(ICoreWebView2 *This, REFIID riid, void **ppvObject);
    ////ULONG (STDMETHODCALLTYPE *AddRef)(ICoreWebView2 *This);
    ////ULONG (STDMETHODCALLTYPE *Release)(ICoreWebView2 *This);
    ////HRESULT (STDMETHODCALLTYPE *Navigate)(ICoreWebView2 *This, LPCWSTR uri);
    ////HRESULT (STDMETHODCALLTYPE *add_NavigationCompleted)(ICoreWebView2 *This, ICoreWebView2NavigationCompletedEventHandler *eventHandler, EventRegistrationToken *token);
////} ICoreWebView2Vtbl;

////struct ICoreWebView2 {
    ////const ICoreWebView2Vtbl *lpVtbl;
////};

////#endif /* WEBVIEW2_C_H */
