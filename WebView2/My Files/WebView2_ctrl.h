typedef struct {
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler iface;
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl *lpVtbl;
    COM_Base base;
    ICoreWebView2Controller **outController;
} ControllerHandler;

static HRESULT STDMETHODCALLTYPE Ctrl_QI(
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This,
    REFIID riid,
    void **ppv)
{
    if (!ppv) return E_POINTER;
    *ppv = This;
    Base_AddRef(&((ControllerHandler*)This)->base);
    return S_OK;
}

static ULONG STDMETHODCALLTYPE Ctrl_AddRef(
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This)
{
    return Base_AddRef(&((ControllerHandler*)This)->base);
}

static ULONG STDMETHODCALLTYPE Ctrl_Release(
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This)
{
    return Base_Release(&((ControllerHandler*)This)->base);
}

static HRESULT STDMETHODCALLTYPE Ctrl_Invoke(
    ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *This,
    HRESULT result,
    ICoreWebView2Controller *controller)
{
    ControllerHandler *self = (ControllerHandler*)This;
    if (SUCCEEDED(result) && self->outController) {
        *self->outController = controller;
        controller->lpVtbl->AddRef(controller);
    }
    return S_OK;
}

static ICoreWebView2CreateCoreWebView2ControllerCompletedHandlerVtbl Ctrl_Vtbl = {
    Ctrl_QI,
    Ctrl_AddRef,
    Ctrl_Release,
    Ctrl_Invoke
};

ControllerHandler* CreateControllerHandler(
    ICoreWebView2Controller **outController)
{
    ControllerHandler *h =
        (ControllerHandler*)CoTaskMemAlloc(sizeof(ControllerHandler));
    if (!h) return NULL;
    h->iface.lpVtbl = &Ctrl_Vtbl;
    h->base.refCount = 1;
    h->outController = outController;
    return h;
}
