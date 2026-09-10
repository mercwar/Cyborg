
# **📘 PAGE 9.6 — IR CANONICAL EXAMPLES (MASTER SET)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **9.6 Overview**

This page provides the **complete, authoritative example set** for Cyborg IR:

- minimal IR  
- single‑verb IR  
- multi‑verb IR  
- repeated‑verb IR  
- mixed‑order IR  
- full‑chain IR  
- failure‑tolerant IR  
- deterministic IR  
- purity‑compliant IR  

These examples define the **reference truth** for all IR implementations.

This section is **normative**.

---

# **9.6.1 Minimal IR Example**

```
TARGET = AI
OPEN_PAYLOAD
SEAL
```

### **Meaning**
A module with no verbs.  
Executes nothing.  
Returns success (`0`).

---

# **9.6.2 Single‑Verb IR Example**

```
TARGET = FILE
OPEN_PAYLOAD
EXEC_VALIDATE
SEAL
```

### **Meaning**
Runs only VALIDATE on a `CyborgFile`.

---

# **9.6.3 Two‑Verb IR Example**

```
TARGET = LAYER
OPEN_PAYLOAD
EXEC_SCAN
EXEC_BUILD
SEAL
```

### **Meaning**
SCAN → BUILD  
No inference.  
No optimization.

---

# **9.6.4 Full Verb Chain Example**

```
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_GIVE
EXEC_EXPLAIN
SEAL
```

### **Meaning**
The complete semantic lifecycle.

---

# **9.6.5 Repeated Verb Example**

```
TARGET = FILE
OPEN_PAYLOAD
EXEC_BUILD
EXEC_BUILD
EXEC_BUILD
SEAL
```

### **Meaning**
Repeated verbs are allowed.  
Runtime MUST NOT collapse or optimize them.

---

# **9.6.6 Mixed Ordering Example**

```
TARGET = AI
OPEN_PAYLOAD
EXEC_GIVE
EXEC_VALIDATE
EXEC_EXPLAIN
SEAL
```

### **Meaning**
Order is preserved exactly as written.  
Semantics do not change.

---

# **9.6.7 Failure‑Tolerant IR Example**

```
TARGET = LAYER
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_BUILD
EXEC_GIVE
SEAL
```

### **Meaning**
Even if VALIDATE fails:  
BUILD still runs.  
GIVE still runs.  
Execution never stops early.

---

# **9.6.8 Deterministic IR Example**

```
TARGET = FILE
OPEN_PAYLOAD
EXEC_SCAN
EXEC_GIVE
SEAL
```

### **Meaning**
Same IR → same C code → same execution → same result.

---

# **9.6.9 Purity‑Compliant IR Example**

```
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
SEAL
```

### **Meaning**
No parameters.  
No metadata.  
No dynamic constructs.  
Pure declaration.

---

# **9.6.10 Canonical IR → C Example**

### **IR**
```
TARGET = FILE
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgFile* file) {
    int r1 = validate_context(file);
    int r2 = scan_context(file);
    int r3 = build_context(file);
    return (r1 || r2 || r3);
}
```

### **Meaning**
IR → C is a **pure, deterministic mapping**.

---

# **9.6.11 Canonical IR With No BUILD**

```
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_GIVE
EXEC_EXPLAIN
SEAL
```

### **Meaning**
GIVE and EXPLAIN MUST NOT assume BUILD ran.  
They operate on whatever exists.

---

# **9.6.12 Canonical IR With Only BUILD**

```
TARGET = LAYER
OPEN_PAYLOAD
EXEC_BUILD
SEAL
```

### **Meaning**
BUILD mutates context.  
No other verbs run.

---

# **9.6.13 Canonical IR With Zero Verbs**

```
TARGET = FILE
OPEN_PAYLOAD
SEAL
```

### **Meaning**
Valid.  
Does nothing.  
Returns success.

---

# **9.6.14 Summary**

Page 9.6 defines the **master canonical IR example set**:

- minimal IR  
- single‑verb IR  
- multi‑verb IR  
- repeated verbs  
- mixed ordering  
- full chain  
- deterministic IR  
- purity‑compliant IR  
- IR → C mapping  

This library is the **reference truth** for all IR usage in the Cyborg Language.
