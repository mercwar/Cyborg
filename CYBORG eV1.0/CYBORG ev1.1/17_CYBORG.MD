# **📘 PAGE 3.6 — VERB ORDERING RULES**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.6 Overview**

Verb ordering is one of the **strictest and most unforgiving** components of the Cyborg Language.  
Because verbs map directly to deterministic IR opcodes and C function calls, **their order defines the execution order**, and therefore:

- MUST NOT change  
- MUST NOT be inferred  
- MUST NOT be optimized  
- MUST NOT be rearranged  
- MUST NOT be grouped automatically  

The order written by the user is the **only valid order**.

This section is **normative**.

---

# **3.6.1 Ordering Is Absolute**

The Cyborg Language enforces **strict sequential execution**.

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

The order MUST be preserved exactly.

---

# **3.6.2 No Reordering Allowed**

The engine MUST NOT:

- reorder verbs  
- group verbs  
- optimize verb order  
- parallelize verbs  
- infer missing verbs  
- collapse similar verbs  

### **Forbidden Example**
```vb
begin
validate
scan
#!#
```

The engine MUST NOT reorder this to:

```
scan → validate
```

Even if it seems “logical,” “efficient,” or “cleaner,”  
**the written order is law**.

---

# **3.6.3 No Implicit Ordering**

The engine MUST NOT:

- assume a default order  
- assume a recommended order  
- assume a semantic order  

### **Forbidden**
```vb
begin
validate
#!#
```

The engine MUST NOT assume:

```
scan → validate
```

Only the user defines order.

---

# **3.6.4 No Parallel Execution**

Even if two verbs are independent, they MUST NOT be executed in parallel.

### **Forbidden**
```vb
begin
scan
validate
#!#
```

The engine MUST NOT treat this as:

```
scan || validate
```

Execution is always **serial**.

---

# **3.6.5 No Conditional Ordering**

The Cyborg Language does not support:

- conditional verbs  
- branching  
- loops  
- optional execution paths  

### **Forbidden**
```vb
begin
if ready then validate
#!#
```

No conditional constructs exist.

---

# **3.6.6 No Grouped Verbs**

Verbs MUST appear one per line.

### **Forbidden**
```vb
begin
scan validate
#!#
```

### **Forbidden**
```vb
begin
scan, validate
#!#
```

### **Forbidden**
```vb
begin
scan + validate
#!#
```

Each verb MUST stand alone.

---

# **3.6.7 Comments Must Not Break Ordering**

Comments MAY appear, but MUST NOT:

- appear between marker fragments  
- appear after the seal  
- alter execution order  
- imply grouping  

### **Valid**
```vb
begin
scan      ' first pass
validate  ' second pass
#!#
```

### **Invalid**
```vb
begin
' comment that implies grouping ❌
scan
validate
#!#
```

---

# **3.6.8 Ordering Violations (Normative)**

The following MUST be rejected:

### ❌ Reordered Verbs  
### ❌ Grouped Verbs  
### ❌ Combined Verbs  
### ❌ Inferred Verbs  
### ❌ Missing Verbs  
### ❌ Conditional Verbs  
### ❌ Parallel Verbs  
### ❌ Verbs Outside Payload  
### ❌ Verbs After Seal  

All violate deterministic execution.

---

# **3.6.9 Full Valid Example**

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

Order preserved.  
Order enforced.  
Order is law.

---

# **3.6.10 Summary**

Page 3.6 establishes the **strict ordering rules** for verbs:

- order MUST be preserved  
- no reordering  
- no grouping  
- no inference  
- no parallelism  
- no conditional execution  
- one verb per line  
- comments must not break structure  

Verb order is the **execution spine** of the Cyborg Language.

