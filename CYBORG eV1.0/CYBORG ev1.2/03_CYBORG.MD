

# **📘 PAGE 5.1 — C LAYER STRUCTURE (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **5.1 Overview**

This section defines the **formal, canonical structure** of the Cyborg C Layer.  
Where Page 5.0 introduced the C Layer conceptually, Page 5.1 establishes the **exact structural rules** that every generated C artifact MUST follow.

The C Layer is:

- rigid  
- minimal  
- deterministic  
- non‑inferential  
- non‑optimizing  
- strictly derived from IR  

This section is **normative**.

---

# **5.1.1 C Layer Structural Principles**

The C Layer is governed by four structural principles:

### **Principle 1 — One Module → One Function**  
Every Cyborg Module produces exactly one C function.

### **Principle 2 — Linear Execution**  
The function body is a straight, top‑to‑bottom sequence of verb calls.

### **Principle 3 — No Structural Variation**  
No additional constructs may appear.

### **Principle 4 — Deterministic Return**  
The return value is always the OR‑aggregation of verb results.

---

# **5.1.2 Canonical C Layer Layout**

Every C output MUST follow this exact layout:

```
[1] Function Signature
[2] Opening Brace
[3] Temporary Variables + Verb Calls
[4] Return Aggregation
[5] Closing Brace
```

Nothing else is permitted.

---

# **5.1.3 Section 1 — Function Signature**

The signature MUST follow the rules defined in Page 4.6.

### **Canonical Form**
```c
int cyborg_payload(<TARGET_TYPE>* ctx)
```

Where `<TARGET_TYPE>` is:

- `CyborgContext` for AI  
- `CyborgFile` for FILE  
- `CyborgLayer` for LAYER  

### **Forbidden**
- multiple parameters  
- const qualifiers  
- static qualifiers  
- inline qualifiers  
- attributes  
- comments  

---

# **5.1.4 Section 2 — Opening Brace**

The function body MUST begin with:

```c
{
```

No indentation rules are enforced, but no additional content may appear before the brace.

---

# **5.1.5 Section 3 — Temporary Variables + Verb Calls**

Each EXEC_* opcode MUST produce:

1. a temporary variable  
2. a direct call to the verb function  
3. assignment of the result  

### **Canonical Pattern**
```c
int r1 = scan_context(ctx);
int r2 = validate_context(ctx);
```

### **Rules**

- variables MUST be named sequentially (`r1`, `r2`, `r3`, …)  
- variables MUST NOT be reused  
- calls MUST NOT be reordered  
- calls MUST NOT be combined  
- calls MUST NOT be wrapped in conditions  
- calls MUST NOT be wrapped in loops  
- calls MUST NOT be optimized  

This section is the **execution spine** of the C Layer.

---

# **5.1.6 Section 4 — Return Aggregation**

The return statement MUST aggregate all temporary variables using the OR operator.

### **Canonical Form**
```c
return (r1 || r2 || r3);
```

### **Rules**

- MUST include all variables  
- MUST preserve order  
- MUST use `||`  
- MUST be a single expression  
- MUST NOT contain parentheses around individual variables  
- MUST NOT contain additional logic  

### **Forbidden**
```c
return r1;                 // ❌ ignores others
return (r2 || r1);         // ❌ reorders
return (r1 && r2);         // ❌ wrong operator
return (r1 | r2);          // ❌ bitwise operator
```

---

# **5.1.7 Section 5 — Closing Brace**

The function MUST end with:

```c
}
```

No trailing content is permitted.

---

# **5.1.8 Full Canonical Example**

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
EXEC_GIVE
SEAL
END_TRANSMISSION
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = scan_context(ctx);
    int r2 = validate_context(ctx);
    int r3 = give_context(ctx);
    return (r1 || r2 || r3);
}
```

This is the **exact, immutable structure** of the C Layer.

---

# **5.1.9 Forbidden Structural Variations**

The following MUST be rejected:

### ❌ Additional functions  
### ❌ Additional parameters  
### ❌ Additional variables  
### ❌ Missing variables  
### ❌ Reordered variables  
### ❌ Combined calls  
### ❌ Conditional logic  
### ❌ Loops  
### ❌ Macros  
### ❌ Comments  
### ❌ Logging  
### ❌ Memory allocation  
### ❌ Exception handling  
### ❌ Parallel execution  

Any deviation breaks determinism.

---

# **5.1.10 Summary**

Page 5.1 defines the **formal structure** of the C Layer:

- one function  
- fixed signature  
- linear verb calls  
- sequential temporary variables  
- OR‑aggregated return  
- no additional constructs  

This structure is the **immutable skeleton** of the Cyborg execution model.
