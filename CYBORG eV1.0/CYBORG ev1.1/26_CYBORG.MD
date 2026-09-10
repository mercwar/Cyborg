

# **📘 PAGE 4.6 — C FUNCTION SIGNATURES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.6 Overview**

This section defines the **formal, canonical, and immutable** C function signatures used by the Cyborg Language.  
These signatures are:

- fixed  
- deterministic  
- non‑overloaded  
- non‑inferential  
- directly bound to the IR target  
- the only valid entry points for generated C code  

This section is **normative**.

---

# **4.6.1 Signature Philosophy**

The Cyborg Language enforces three signature principles:

### **Principle 1 — One Module → One Function**  
Every Cyborg Module produces exactly **one** C function.

### **Principle 2 — Target Defines Type**  
The target declaration determines the function parameter type.

### **Principle 3 — No Variation**  
Signatures MUST NOT change based on context, metadata, or payload content.

---

# **4.6.2 Canonical Function Name**

All generated C functions MUST use the exact name:

```c
cyborg_payload
```

### **Forbidden Variants**
- `cy_payload`  
- `run_payload`  
- `execute_payload`  
- `cyborg_main`  
- `payload`  

The name is **fixed**.

---

# **4.6.3 Canonical Return Type**

All generated functions MUST return:

```c
int
```

### **Reason**
- all verb functions return `int`  
- OR‑aggregation requires integer semantics  
- determinism requires a single return type  

### **Forbidden**
- `void`  
- `bool`  
- `uint8_t`  
- `CyborgResult`  

---

# **4.6.4 Canonical Parameter Types**

The parameter type is determined **solely** by the target.

| Target | C Parameter Type |
|--------|------------------|
| `AI` | `CyborgContext* ctx` |
| `FILE` | `CyborgFile* file` |
| `LAYER` | `CyborgLayer* layer` |

### **Examples**

#### **IR**
```cyborg
TARGET = AI
```

#### **C Signature**
```c
int cyborg_payload(CyborgContext* ctx)
```

---

# **4.6.5 Full Signature Forms**

### **Target: AI**
```c
int cyborg_payload(CyborgContext* ctx)
```

### **Target: FILE**
```c
int cyborg_payload(CyborgFile* file)
```

### **Target: LAYER**
```c
int cyborg_payload(CyborgLayer* layer)
```

These are the **only** valid signatures.

---

# **4.6.6 Signature Invariance Rules**

The signature MUST NOT:

- include additional parameters  
- include default parameters  
- include variadic parameters  
- include const qualifiers  
- include restrict qualifiers  
- include inline modifiers  
- include static modifiers  
- include attributes  
- include comments  

### **Forbidden Examples**

```c
int cyborg_payload(CyborgContext* ctx, int mode)      // ❌ extra parameter
int cyborg_payload(const CyborgContext* ctx)          // ❌ const
static int cyborg_payload(CyborgContext* ctx)         // ❌ static
int cyborg_payload(CyborgContext* ctx, ...)           // ❌ variadic
```

All MUST be rejected.

---

# **4.6.7 Signature Placement Rules**

The function MUST:

- appear at global scope  
- not be nested  
- not be wrapped in macros  
- not be wrapped in namespaces  
- not be wrapped in classes  

### **Forbidden**
```c
namespace cyborg {
    int cyborg_payload(CyborgContext* ctx) { ... }   // ❌
}
```

---

# **4.6.8 Signature → IR Binding**

The signature is bound to the IR target.

### **IR**
```cyborg
TARGET = LAYER
```

### **C**
```c
int cyborg_payload(CyborgLayer* layer)
```

This binding is **mandatory** and **non‑inferential**.

---

# **4.6.9 Full Example**

### **VB‑Style**
```vb
set to file
begin
scan
validate
#!#
end
```

### **IR**
```cyborg
TARGET = FILE
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
SEAL
END_TRANSMISSION
```

### **C Output**
```c
int cyborg_payload(CyborgFile* file) {
    int r1 = scan_context(file);
    int r2 = validate_context(file);
    return (r1 || r2);
}
```

---

# **4.6.10 Summary**

Page 4.6 defines the **formal C function signature rules**:

- one function per module  
- fixed name: `cyborg_payload`  
- fixed return type: `int`  
- parameter type determined by target  
- no modifiers, no extras, no variation  
- global scope only  

The signature is the **entry point of execution** in the Cyborg Language.

