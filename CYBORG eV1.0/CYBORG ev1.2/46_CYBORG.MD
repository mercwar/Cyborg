

# **📘 PAGE 10.1 — C LAYER FUNCTION SIGNATURE RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.1 Overview**

This page defines the **mandatory function signature** generated for every Cyborg Module.  
The signature is:

- deterministic  
- target‑bound  
- context‑bound  
- pure  
- non‑allocating  
- non‑inferential  
- C89/C90 compliant  

This section is **normative**.

---

# **10.1.1 Signature Rule 1 — One Function Per Module**

Every IR module MUST generate exactly **one** C function:

```
int cyborg_payload(<CONTEXT_TYPE>* ctx);
```

There are no overloads.  
There are no variants.  
There are no auxiliary entry points.

### **Meaning**  
The module has **one and only one** executable entry.

---

# **10.1.2 Signature Rule 2 — Function Name Is Fixed**

The function name MUST be:

```
cyborg_payload
```

It MUST NOT vary based on:

- module name  
- file name  
- target  
- verbs  
- configuration  

### **Meaning**  
The entry point is **universal**.

---

# **10.1.3 Signature Rule 3 — Return Type Is Fixed**

The return type MUST be:

```
int
```

It MUST NOT be:

- `void`  
- `bool`  
- `enum`  
- `struct`  
- `typedef`  

### **Meaning**  
The return value is a **binary truth value**.

---

# **10.1.4 Signature Rule 4 — Parameter Count Is Fixed**

The function MUST take exactly **one** parameter.

### **Forbidden**
- multiple parameters  
- zero parameters  
- variadic parameters  

### **Meaning**  
The function is **context‑bound**.

---

# **10.1.5 Signature Rule 5 — Parameter Type Is Target‑Dependent**

The parameter MUST be a pointer to the context type determined by the IR target:

| IR Target | C Parameter Type |
|----------|------------------|
| `AI`     | `CyborgContext*` |
| `FILE`   | `CyborgFile*`    |
| `LAYER`  | `CyborgLayer*`   |

### **Meaning**  
The IR target determines the **semantic universe** of the function.

---

# **10.1.6 Signature Rule 6 — Parameter Name Is Fixed**

The parameter name MUST be:

```
ctx
```

It MUST NOT vary.

### **Meaning**  
Naming is **canonical**.

---

# **10.1.7 Signature Rule 7 — No Additional Qualifiers**

The function MUST NOT include:

- `static`  
- `inline`  
- `extern`  
- `const`  
- `volatile`  
- `restrict`  
- compiler extensions  

### **Meaning**  
The signature is **pure C89/C90**.

---

# **10.1.8 Signature Rule 8 — No Attributes or Annotations**

The function MUST NOT include:

- attributes  
- pragmas  
- metadata  
- macros  
- decorators  

### **Meaning**  
The signature is **unadorned**.

---

# **10.1.9 Signature Rule 9 — No Overloading or Namespacing**

The function MUST NOT:

- be overloaded  
- be namespaced  
- be wrapped in classes  
- be wrapped in structs  
- be wrapped in modules  

### **Meaning**  
The function exists in the **global namespace**.

---

# **10.1.10 Signature Rule 10 — Signature Must Be Deterministic**

Given the same IR target:

- the same signature MUST be generated  
- on all platforms  
- with all compilers  
- with all optimization levels  

### **Meaning**  
The signature is **mathematically reproducible**.

---

# **10.1.11 Canonical Signature Examples**

### **AI Target**
```c
int cyborg_payload(CyborgContext* ctx);
```

### **FILE Target**
```c
int cyborg_payload(CyborgFile* ctx);
```

### **LAYER Target**
```c
int cyborg_payload(CyborgLayer* ctx);
```

These are the **only three valid signatures** in the entire language.

---

# **10.1.12 Summary**

Page 10.1 defines the **C Layer Function Signature Rules**:

- one function per module  
- fixed name  
- fixed return type  
- fixed parameter count  
- target‑dependent parameter type  
- fixed parameter name  
- no qualifiers  
- no attributes  
- no overloading  
- deterministic generation  

The signature is the **immutable gateway** between IR and execution.
