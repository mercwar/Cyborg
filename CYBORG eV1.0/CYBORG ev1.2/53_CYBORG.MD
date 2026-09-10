

# **📘 PAGE 10.8 — C LAYER ERROR‑HANDLING RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.8 Overview**

The **Error‑Handling Rules** define how the generated C function must treat:

- verb failures  
- non‑zero return values  
- error propagation  
- error aggregation  
- error visibility  

The C Layer is not a recovery system.  
It is not a diagnostic system.  
It is not a logging system.

> **The C Layer does not handle errors.  
It only *collects* them.**

This section is **normative**.

---

# **10.8.1 Error Rule 1 — Verbs Define Failure, Not the C Layer**

A verb returns:

- `0` → success  
- non‑zero → failure  

The C Layer MUST NOT reinterpret these values.

### **Meaning**  
The C Layer is **not an error translator**.

---

# **10.8.2 Error Rule 2 — All Verb Failures Must Be Preserved**

If a verb returns non‑zero:

- the value MUST be stored  
- the value MUST be included in the OR chain  
- the value MUST influence the final result  

### **Meaning**  
No failure may be ignored.

---

# **10.8.3 Error Rule 3 — No Early Termination on Failure**

Even if a verb fails:

- execution MUST continue  
- all remaining verbs MUST run  
- no early return is allowed  

### **Meaning**  
Failure does **not** interrupt execution.

---

# **10.8.4 Error Rule 4 — No Error Recovery**

The C Layer MUST NOT:

- attempt to fix errors  
- retry verbs  
- branch on failures  
- skip verbs after failure  
- perform fallback logic  

### **Meaning**  
The C Layer is **non‑reactive**.

---

# **10.8.5 Error Rule 5 — No Error Logging**

The C Layer MUST NOT:

- print messages  
- write logs  
- emit diagnostics  
- call logging APIs  
- expose error details  

### **Meaning**  
The C Layer is **silent**.

---

# **10.8.6 Error Rule 6 — No Error Transformation**

The C Layer MUST NOT:

- convert error codes  
- normalize values  
- reinterpret failures  
- map errors to other values  

### **Meaning**  
Verb return values are **untouched**.

---

# **10.8.7 Error Rule 7 — Aggregation Is the Only Error Mechanism**

The final result MUST be:

```
return (r1 || r2 || r3 || ... || rn);
```

This is the **sole** error‑handling mechanism.

### **Meaning**  
Error semantics are **binary** and **aggregate‑only**.

---

# **10.8.8 Error Rule 8 — No Error Context**

The C Layer MUST NOT:

- store error metadata  
- store error messages  
- store error locations  
- store error counts  

### **Meaning**  
The C Layer is **stateless** with respect to errors.

---

# **10.8.9 Error Rule 9 — No Error Propagation Beyond Final Return**

The C Layer MUST NOT:

- propagate individual verb errors  
- expose intermediate results  
- return multiple values  
- encode error details  

### **Meaning**  
The final return value is the **only** error signal.

---

# **10.8.10 Error Rule 10 — Error Behavior Must Be Deterministic**

Given the same verb results:

- the same final result MUST be produced  
- on all platforms  
- with all compilers  
- with all optimization levels  

### **Meaning**  
Error semantics are **mathematically reproducible**.

---

# **10.8.11 Canonical Example — Failure‑Tolerant Execution**

### **IR**
```
TARGET = LAYER
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_BUILD
EXEC_EXPLAIN
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgLayer* ctx) {
    int r1 = validate_context(ctx);
    int r2 = build_context(ctx);
    int r3 = explain_context(ctx);
    return (r1 || r2 || r3);
}
```

### **Error Interpretation**
- if VALIDATE fails → BUILD still runs  
- if BUILD fails → EXPLAIN still runs  
- final result is OR of all failures  
- no early exit  
- no recovery  
- no logging  

This is the **canonical error‑handling pattern**.

---

# **10.8.12 Summary**

Page 10.8 defines the **C Layer Error‑Handling Rules**:

- verbs define failure  
- failures are preserved  
- no early termination  
- no recovery  
- no logging  
- no transformation  
- aggregation is the only mechanism  
- no error context  
- no propagation beyond final return  
- deterministic behavior  

The C Layer is **silent**, **literal**, and **binary** in its treatment of failure.
