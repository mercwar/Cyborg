

# **📘 PAGE 10.2 — C LAYER VERB INVOCATION RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.2 Overview**

This page defines the **mandatory rules** governing how the C Layer invokes verbs.  
These rules ensure that:

- every verb call is deterministic  
- every verb call is literal  
- every verb call is pure  
- every verb call is non‑optimizing  
- every verb call is non‑inferential  
- every verb call is executed exactly as declared in IR  

This section is **normative**.

---

# **10.2.1 Invocation Rule 1 — One C Call Per EXEC Line**

Each IR line of the form:

```
EXEC_<VERB>
```

MUST generate exactly one C call:

```
<verb>_context(ctx)
```

### **Meaning**  
IR → C mapping is **one‑to‑one**, never collapsed or merged.

---

# **10.2.2 Invocation Rule 2 — Verb Name Mapping Is Fixed**

The mapping from IR verb to C function is:

| IR Verb        | C Function Call            |
|----------------|----------------------------|
| `EXEC_VALIDATE` | `validate_context(ctx)`    |
| `EXEC_SCAN`     | `scan_context(ctx)`        |
| `EXEC_BUILD`    | `build_context(ctx)`       |
| `EXEC_GIVE`     | `give_context(ctx)`        |
| `EXEC_EXPLAIN`  | `explain_context(ctx)`     |

### **Meaning**  
Verb names are **canonical** and **immutable**.

---

# **10.2.3 Invocation Rule 3 — Verbs Receive Exactly One Argument**

Every verb MUST be invoked with exactly one argument:

```
ctx
```

No additional arguments.  
No parameters.  
No configuration.

### **Meaning**  
Verb invocation is **pure and parameterless**.

---

# **10.2.4 Invocation Rule 4 — Verbs Return int**

Every verb MUST return:

```
int
```

Where:

- `0` = success  
- non‑zero = failure  

### **Meaning**  
Verb results are **binary truth values**.

---

# **10.2.5 Invocation Rule 5 — Verb Results Must Be Captured**

Each verb call MUST assign its return value to a unique local variable:

```
int r1 = validate_context(ctx);
int r2 = scan_context(ctx);
...
```

### **Meaning**  
Every verb result is **explicitly preserved**.

---

# **10.2.6 Invocation Rule 6 — Verb Results Must Be OR‑Aggregated**

The final return value MUST be:

```
return (r1 || r2 || r3 || ... || rn);
```

### **Meaning**  
Aggregation is **logical OR**, never sum, never AND, never ignored.

---

# **10.2.7 Invocation Rule 7 — Verb Order Must Match IR Order**

If the IR says:

```
EXEC_GIVE
EXEC_VALIDATE
EXEC_EXPLAIN
```

The C Layer MUST generate:

```c
int r1 = give_context(ctx);
int r2 = validate_context(ctx);
int r3 = explain_context(ctx);
```

### **Meaning**  
Order is **semantic**, not cosmetic.

---

# **10.2.8 Invocation Rule 8 — No Reordering or Optimization**

The C Layer MUST NOT:

- reorder verb calls  
- collapse repeated verbs  
- skip verbs  
- infer missing verbs  
- optimize execution  

### **Meaning**  
The C Layer is **literal**.

---

# **10.2.9 Invocation Rule 9 — No Early Termination**

Even if a verb returns non‑zero:

- execution MUST continue  
- all remaining verbs MUST run  

### **Meaning**  
Execution is **non‑short‑circuiting**.

---

# **10.2.10 Invocation Rule 10 — No Side Effects**

Verb invocation MUST NOT:

- allocate memory  
- free memory  
- perform I/O  
- call external APIs  
- modify global state  
- use static state  

### **Meaning**  
Verb invocation is **pure mechanical dispatch**.

---

# **10.2.11 Canonical Example — Mixed Verbs**

### **IR**
```
TARGET = FILE
OPEN_PAYLOAD
EXEC_GIVE
EXEC_VALIDATE
EXEC_BUILD
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgFile* ctx) {
    int r1 = give_context(ctx);
    int r2 = validate_context(ctx);
    int r3 = build_context(ctx);
    return (r1 || r2 || r3);
}
```

### **Meaning**  
Order preserved.  
Purity preserved.  
Determinism preserved.

---

# **10.2.12 Summary**

Page 10.2 defines the **C Layer Verb Invocation Rules**:

- one C call per EXEC line  
- fixed verb name mapping  
- single argument: `ctx`  
- verbs return int  
- results captured explicitly  
- OR‑aggregation  
- strict order preservation  
- no optimization  
- no early termination  
- no side effects  

These rules ensure that verb invocation is **literal, pure, and deterministic**.
