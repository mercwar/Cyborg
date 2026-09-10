typedef struct {
    ICoreWebView2ExecuteScriptCompletedHandler iface;
    ICoreWebView2ExecuteScriptCompletedHandlerVtbl *lpVtbl;
    COM_Base base;
    LPWSTR *outResult;
} ScriptHandler;

static HRESULT STDMETHODCALLTYPE Script_QI(
    ICoreWebView2ExecuteScriptCompletedHandler *This,
    REFIID riid,
    void **ppv)
{
    if (!ppv) return E_POINTER;
    *ppv = This;
    Base_AddRef(&((ScriptHandler*)This)->base);
    return S_OK;
}

static ULONG STDMETHODCALLTYPE Script_AddRef(
    ICoreWebView2ExecuteScriptCompletedHandler *This)
{
    return Base_AddRef(&((ScriptHandler*)This)->base);
}

static ULONG STDMETHODCALLTYPE Script_Release(
    ICoreWebView2ExecuteScriptCompletedHandler *This)
{
    return Base_Release(&((ScriptHandler*)This)->base);
}

static HRESULT STDMETHODCALLTYPE Script_Invoke(
    ICoreWebView2ExecuteScriptCompletedHandler *This,
    HRESULT errorCode,
    LPCWSTR resultObjectAsJson)
{
    ScriptHandler *self = (ScriptHandler*)This;
    if (SUCCEEDED(errorCode) && self->outResult && resultObjectAsJson) {
        size_t len = (wcslen(resultObjectAsJson) + 1) * sizeof(WCHAR);
        *self->outResult = (LPWSTR)CoTaskMemAlloc(len);
        memcpy(*self->outResult, resultObjectAsJson, len);
    }
    return S_OK;
}

static ICoreWebView2ExecuteScriptCompletedHandlerVtbl Script_Vtbl = {
    Script_QI,
    Script_AddRef,
    Script_Release,
    Script_Invoke
};

ScriptHandler* CreateScriptHandler(LPWSTR *outResult)
{
    ScriptHandler *h =
        (ScriptHandler*)CoTaskMemAlloc(sizeof(ScriptHandler));
    if (!h) return NULL;
    h->iface.lpVtbl = &Script_Vtbl;
    h->base.refCount = 1;
    h->outResult = outResult;
    return h;
}
