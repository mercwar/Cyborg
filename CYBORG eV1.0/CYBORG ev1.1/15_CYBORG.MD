# **📘 PAGE 3.5 — VERBS**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.5 Overview**

Verbs are the **operational core** of the Cyborg Language.  
They are the *only* executable elements inside a payload block, and they define **exactly what actions occur** during module execution.

A verb in the Cyborg Language is:

- atomic  
- deterministic  
- non‑overloaded  
- non‑inferential  
- directly mapped to a C function  
- executed strictly in the order written  

This section is **normative**.

---

# **3.5.1 The Five Canonical Verbs**

The Cyborg Language defines exactly **five** verbs:

```
validate
scan
build
give
explain
```

No other verbs exist.  
No synonyms exist.  
No overloaded forms exist.

Each verb has:

- a **single meaning**  
- a **single IR opcode**  
- a **single C function signature**  

---

# **3.5.2 Verb Table (Normative)**

| Verb | Purpose | IR Opcode | C Function |
|------|---------|-----------|------------|
| **validate** | Check correctness, consistency, or integrity | `EXEC_VALIDATE` | `validate_context(ctx)` |
| **scan** | Inspect, parse, or traverse the target | `EXEC_SCAN` | `scan_context(ctx)` |
| **build** | Construct or assemble structures | `EXEC_BUILD` | `build_context(ctx)` |
| **give** | Return or emit information | `EXEC_GIVE` | `give_context(ctx)` |
| **explain** | Produce a descriptive or diagnostic output | `EXEC_EXPLAIN` | `explain_context(ctx)` |

Each verb is **strict**, **atomic**, and **non‑composable**.

---

# **3.5.3 Verb Syntax**

### **VB‑Style**
```vb
validate
scan
build
give
explain
```

### **Normative Rules**

- Verbs MUST appear inside an open payload.  
- Verbs MUST NOT appear before `begin`.  
- Verbs MUST NOT appear after `#!#`.  
- Verbs MUST NOT be inferred.  
- Verbs MUST NOT be reordered.  
- Verbs MUST map to C functions.  
- Verbs MUST NOT contain arguments.  

---

# **3.5.4 Verb Execution Order**

Execution order is **strict** and MUST be preserved.

### **VB‑Style**
```vb
begin
scan
validate
build
#!#
```

### **IR**
```cyborg
EXEC_SCAN
EXEC_VALIDATE
EXEC_BUILD
```

### **C Output**
```c
scan_context(ctx);
validate_context(ctx);
build_context(ctx);
```

Order is never changed.

---

# **3.5.5 Verb → IR Mapping**

### **VB‑Style**
```vb
validate
```

### **IR**
```cyborg
EXEC_VALIDATE
```

---

### **VB‑Style**
```vb
scan
```

### **IR**
```cyborg
EXEC_SCAN
```

---

### **VB‑Style**
```vb
build
```

### **IR**
```cyborg
EXEC_BUILD
```

---

### **VB‑Style**
```vb
give
```

### **IR**
```cyborg
EXEC_GIVE
```

---

### **VB‑Style**
```vb
explain
```

### **IR**
```cyborg
EXEC_EXPLAIN
```

---

# **3.5.6 Verb → C Mapping**

Each verb maps to a **single, deterministic C function**.

### **validate**
```c
int validate_context(CyborgContext* ctx);
```

### **scan**
```c
int scan_context(CyborgContext* ctx);
```

### **build**
```c
int build_context(CyborgContext* ctx);
```

### **give**
```c
int give_context(CyborgContext* ctx);
```

### **explain**
```c
int explain_context(CyborgContext* ctx);
```

These signatures MUST NOT vary.

---

# **3.5.7 Verb Restrictions**

The following are **forbidden**:

### ❌ Arguments
```vb
validate now   ' invalid
```

### ❌ Overloaded Forms
```vb
validate deep   ' invalid
```

### ❌ Combined Verbs
```vb
validate scan   ' invalid
```

### ❌ Inferred Verbs
```vb
' AI must not guess missing verbs
```

### ❌ Verbs Outside Payload
```vb
validate
begin
#!#
```

### ❌ Verbs After Seal
```vb
begin
validate
#!#
scan   ' invalid
```

---

# **3.5.8 Full Verb Example**

### **VB‑Style Cyborg**
```vb
set to you
begin
scan
validate
give
#!#
end
```

### **Cyborg IR**
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

---

# **3.5.9 Summary**

Page 3.5 defines the **verb system** of the Cyborg Language:

- exactly five verbs  
- no arguments  
- no overloads  
- strict ordering  
- deterministic IR mapping  
- deterministic C mapping  
- verbs only inside payloads  

Verbs are the **action layer** of the Cyborg Language.

