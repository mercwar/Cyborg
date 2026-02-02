# **📘 PAGE 3.9 — ERROR CONDITIONS AND DIAGNOSTICS**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.9 Overview**

Error handling in the Cyborg Language is **binary and absolute**:

- A module is either **valid**  
- or **invalid**  

There is **no partial validity**, no recovery, no inference, and no fallback behavior.

This section defines:

- all error conditions  
- how errors are detected  
- how errors MUST be reported  
- how the engine MUST behave when errors occur  

This section is **normative**.

---

# **3.9.1 Error Philosophy**

The Cyborg Language treats errors as **structural violations**, not runtime events.

### **Principles**

- Errors MUST be detected immediately.  
- Errors MUST halt execution.  
- Errors MUST NOT be corrected automatically.  
- Errors MUST NOT be inferred away.  
- Errors MUST NOT be softened or interpreted.  

### **Reason**

Determinism requires **strict rejection** of invalid constructs.

---

# **3.9.2 Categories of Errors**

All errors fall into one of five categories:

1. **Targeting Errors**  
2. **Marker Errors**  
3. **Verb Errors**  
4. **Ordering Errors**  
5. **Structural Errors**  

Each category is defined below.

---

# **3.9.3 Targeting Errors**

### **Error 1 — Missing Target**
```vb
begin
validate
#!#
```

### **Error 2 — Multiple Targets**
```vb
set to you
set to file
begin
validate
#!#
```

### **Error 3 — Target Inside Payload**
```vb
begin
set to you
validate
#!#
```

### **Error 4 — Target After Seal**
```vb
set to you
begin
validate
#!#
set to file
```

All MUST be rejected.

---

# **3.9.4 Marker Errors**

### **Error 1 — Missing `begin`**
### **Error 2 — Missing `#!#`**
### **Error 3 — Nested Payloads**
### **Error 4 — Multiple Opens**
### **Error 5 — Multiple Seals**
### **Error 6 — Trailing Content**
### **Error 7 — Marker Fragmentation**
### **Error 8 — Marker Decoration**

Examples:

```vb
begin
validate
#!#
extra   ' ❌ trailing content
```

```vb
# B G I N   ' ❌ fragmented
```

```vb
***#!#***   ' ❌ decorated
```

All MUST be rejected.

---

# **3.9.5 Verb Errors**

### **Error 1 — Verb Outside Payload**
```vb
validate
begin
#!#
```

### **Error 2 — Verb After Seal**
```vb
begin
validate
#!#
scan   ' ❌
```

### **Error 3 — Unknown Verb**
```vb
begin
optimize   ' ❌ invalid verb
#!#
```

### **Error 4 — Verb With Arguments**
```vb
validate now   ' ❌
```

### **Error 5 — Combined Verbs**
```vb
scan validate   ' ❌
```

All MUST be rejected.

---

# **3.9.6 Ordering Errors**

### **Error 1 — Reordered Verbs by AI**
AI MUST NOT reorder verbs.

### **Error 2 — Grouped Verbs**
```vb
scan, validate   ' ❌
```

### **Error 3 — Parallel Verbs**
```vb
scan || validate   ' ❌
```

### **Error 4 — Conditional Verbs**
```vb
if ready then validate   ' ❌
```

All MUST be rejected.

---

# **3.9.7 Structural Errors**

### **Error 1 — Declarations Inside Payload**
```vb
begin
meta "illegal"
validate
#!#
```

### **Error 2 — Comments Breaking Markers**
```vb
begin
' illegal
#!#
```

### **Error 3 — Whitespace Splitting Keywords**
```vb
v a l i d a t e   ' ❌
```

### **Error 4 — Payload Inside Payload**
```vb
begin
begin
validate
#!#
#!#
```

All MUST be rejected.

---

# **3.9.8 Diagnostic Output Requirements**

When an error occurs, the engine MUST:

- halt immediately  
- report the error category  
- report the specific violation  
- report the line where the violation occurred  
- MUST NOT attempt correction  
- MUST NOT infer intent  
- MUST NOT continue execution  

### **Example Diagnostic**
```
ERROR: Marker violation — trailing content after seal.
Line 5: "extra"
Execution halted.
```

### **Example Diagnostic**
```
ERROR: Target missing.
No valid execution context found.
Execution halted.
```

Diagnostics MUST be:

- clear  
- direct  
- non‑negotiable  
- non‑interpretive  

---

# **3.9.9 Error Severity**

All errors are **fatal**.

There are no warnings.  
There are no recoverable states.  
There is no “best effort” mode.

If a module violates the rules, it is **invalid**.

---

# **3.9.10 Summary**

Page 3.9 defines the **error and diagnostic system** of the Cyborg Language:

- errors are structural  
- errors are fatal  
- errors halt execution  
- errors MUST NOT be corrected  
- errors MUST NOT be inferred away  
- diagnostics MUST be explicit and direct  

This ensures the language remains **deterministic, strict, and ceremonial**.

