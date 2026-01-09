/* ============================================================
   WebView2 Callback Handler Interfaces
   PURE C / Classic COM
   ============================================================ */

/* ============================================================
   ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler
   ============================================================ */

typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler;

typedef struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl {

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This,
        REFIID riid,
        void **ppvObject
    );

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This
    );

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This
    );

    /* Handler */
    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler *This,
        HRESULT result,
        ICoreWebView2Environment *environment
    );

} ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl;

struct ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler {
    ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandlerVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2CreateCoreWebView2ControllerCompletedHandler
   ============================================================ */

typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler;

typedef struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl {

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This,
        REFIID riid,
        void **ppvObject
    );

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This
    );

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This
    );

    /* Handler */
    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This,
        HRESULT result,
        ICoreWebView2Controller *controller
    );

} ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl;

struct ICoreWebView2CreateCoreWebView2ControllerCompletedHandler {
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl *lpVtbl;
};

/* ============================================================
   ICoreWebView2ExecuteScriptCompletedHandler
   ============================================================ */

typedef struct ICoreWebView2ExecuteScriptCompletedHandler
    ICoreWebView2ExecuteScriptCompletedHandler;

typedef struct ICoreWebView2ExecuteScriptCompletedHandlerVtbl {

    /* IUnknown */
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ICoreWebView2ExecuteScriptCompletedHandler *This,
        REFIID riid,
        void **ppvObject
    );

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ICoreWebView2ExecuteScriptCompletedHandler *This
    );

    ULONG (STDMETHODCALLTYPE *Release)(
        ICoreWebView2ExecuteScriptCompletedHandler *This
    );

    /* Handler */
    HRESULT (STDMETHODCALLTYPE *Invoke)(
        ICoreWebView2ExecuteScriptCompletedHandler *This,
        HRESULT errorCode,
        LPCWSTR resultObjectAsJson
    );

} ICoreWebView2ExecuteScriptCompletedHandlerVtbl;

struct ICoreWebView2ExecuteScriptCompletedHandler {
    ICoreWebView2ExecuteScriptCompletedHandlerVtbl *lpVtbl;
};
