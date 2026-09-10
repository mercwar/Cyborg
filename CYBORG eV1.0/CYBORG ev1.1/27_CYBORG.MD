

# **📘 PAGE 4.7 — VERB FUNCTION SIGNATURES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.7 Overview**

This section defines the **formal, canonical C function signatures** for all verb operations in the Cyborg Language.  
These signatures are:

- fixed  
- deterministic  
- non‑overloaded  
- non‑inferential  
- globally consistent  
- the only valid implementations of verb semantics  

Every verb in the Cyborg Language maps to **exactly one** C function with a fixed signature.

This section is **normative**.

---

# **4.7.1 Verb Function Philosophy**

The Cyborg Language enforces three principles for verb functions:

### **Principle 1 — One Verb → One Function**  
Each verb corresponds to exactly one C function.

### **Principle 2 — Uniform Signature**  
All verb functions share the same signature pattern.

### **Principle 3 — No Variation**  
Signatures MUST NOT change based on target, metadata, or payload content.

---

# **4.7.2 Canonical Verb Function Signature Pattern**

All verb functions MUST follow this exact signature form:

```c
int <verb>_context(<TARGET_TYPE>* ctx);
```

Where:

- `<verb>` is one of the five canonical verbs  
- `<TARGET_TYPE>` is determined by the module target  

### **Forbidden Variants**
- additional parameters  
- default parameters  
- variadic parameters  
- const qualifiers  
- static qualifiers  
- inline qualifiers  
- attributes  
- comments  

---

# **4.7.3 Canonical Verb Functions**

The Cyborg Language defines exactly **five** verb functions.

### **validate**
```c
int validate_context(<TARGET_TYPE>* ctx);
```

### **scan**
```c
int scan_context(<TARGET_TYPE>* ctx);
```

### **build**
```c
int build_context(<TARGET_TYPE>* ctx);
```

### **give**
```c
int give_context(<TARGET_TYPE>* ctx);
```

### **explain**
```c
int explain_context(<TARGET_TYPE>* ctx);
```

These are the **only** valid verb functions.

---

# **4.7.4 Target Type Binding**

The `<TARGET_TYPE>` is determined solely by the IR target.

| IR Target | C Type |
|-----------|--------|
| `AI` | `CyborgContext* ctx` |
| `FILE` | `CyborgFile* file` |
| `LAYER` | `CyborgLayer* layer` |

### **Example**

#### **IR**
```cyborg
TARGET = LAYER
```

#### **Verb Function**
```c
int scan_context(CyborgLayer* layer);
```

---

# **4.7.5 Signature Invariance Rules**

Verb function signatures MUST NOT:

- include extra parameters  
- include optional parameters  
- include variadic parameters  
- include const qualifiers  
- include restrict qualifiers  
- include inline/static modifiers  
- include attributes  
- include comments  
- include return types other than `int`  

### **Forbidden Examples**

```c
int scan_context(CyborgContext* ctx, int mode);      // ❌ extra parameter
void validate_context(CyborgContext* ctx);           // ❌ wrong return type
static int build_context(CyborgContext* ctx);        // ❌ static
int explain_context(const CyborgContext* ctx);       // ❌ const
```

All MUST be rejected.

---

# **4.7.6 Verb Function Placement Rules**

Verb functions MUST:

- appear at global scope  
- not be nested  
- not be wrapped in macros  
- not be wrapped in namespaces  
- not be wrapped in classes  

### **Forbidden**
```c
namespace cyborg {
    int scan_context(CyborgContext* ctx);   // ❌
}
```

---

# **4.7.7 Verb Function Behavior Rules**

Verb functions MUST:

- return an `int`  
- perform a deterministic operation  
- not modify global state  
- not allocate memory  
- not throw exceptions  
- not perform I/O  
- not log  
- not recurse  
- not call other verb functions  

Verb functions MUST be **pure**.

---

# **4.7.8 Full Example (Target: AI)**

### **VB‑Style**
```vb
set to you
begin
scan
validate
#!#
end
```

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
SEAL
END_TRANSMISSION
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = scan_context(ctx);
    int r2 = validate_context(ctx);
    return (r1 || r2);
}
```

### **Verb Functions**
```c
int scan_context(CyborgContext* ctx);
int validate_context(CyborgContext* ctx);
```

---

# **4.7.9 Full Example (Target: FILE)**

### **Verb Functions**
```c
int scan_context(CyborgFile* file);
int validate_context(CyborgFile* file);
int build_context(CyborgFile* file);
int give_context(CyborgFile* file);
int explain_context(CyborgFile* file);
```

These signatures MUST NOT vary.

---

# **4.7.10 Summary**

Page 4.7 defines the **formal verb function signatures**:

- one function per verb  
- fixed naming pattern  
- fixed return type  
- target‑dependent parameter type  
- no modifiers, no extras, no variation  
- pure, deterministic behavior  

These functions are the **atomic execution units** of the Cyborg Language.

