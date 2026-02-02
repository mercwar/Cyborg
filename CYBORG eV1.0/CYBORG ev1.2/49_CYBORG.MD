

# **📘 PAGE 10.4 — C LAYER LOCAL VARIABLE RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.4 Overview**

Local variables inside the generated C function are:

- deterministic  
- fixed‑pattern  
- non‑optimizing  
- non‑inferential  
- non‑reusable  
- non‑foldable  
- non‑reorderable  

They exist solely to capture verb return values in a **literal**, **one‑to‑one**, **order‑preserving** manner.

This section is **normative**.

---

# **10.4.1 Local Rule 1 — One Variable Per Verb**

Each EXEC line MUST generate exactly one local variable:

```
int r1 = validate_context(ctx);
int r2 = scan_context(ctx);
int r3 = build_context(ctx);
```

### **Meaning**  
No variable may capture more than one verb result.

---

# **10.4.2 Local Rule 2 — Variables Must Be Sequentially Numbered**

Variables MUST be named:

```
r1, r2, r3, ..., rn
```

Numbering MUST:

- start at 1  
- increment by 1  
- never skip numbers  
- never reuse numbers  

### **Meaning**  
Variable naming is **strictly linear**.

---

# **10.4.3 Local Rule 3 — Variables Must Be Declared in Execution Order**

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
Variable order mirrors verb order exactly.

---

# **10.4.4 Local Rule 4 — Variables Must Not Be Reused**

Even if two verbs are identical:

```
EXEC_BUILD
EXEC_BUILD
```

The C Layer MUST generate:

```c
int r1 = build_context(ctx);
int r2 = build_context(ctx);
```

### **Meaning**  
Repetition is **literal**, never optimized.

---

# **10.4.5 Local Rule 5 — Variables Must Not Be Declared in Bulk**

The following is **forbidden**:

```c
int r1, r2, r3;
```

Variables MUST be declared individually:

```c
int r1 = ...;
int r2 = ...;
int r3 = ...;
```

### **Meaning**  
Each variable is a **distinct semantic event**.

---

# **10.4.6 Local Rule 6 — Variables Must Not Be Initialized Separately**

Forbidden:

```c
int r1;
r1 = validate_context(ctx);
```

Required:

```c
int r1 = validate_context(ctx);
```

### **Meaning**  
Declaration and initialization are **atomic**.

---

# **10.4.7 Local Rule 7 — Variables Must Not Be Modified**

After initialization:

- no reassignment  
- no mutation  
- no arithmetic  
- no logical operations  

### **Meaning**  
Variables are **write‑once**.

---

# **10.4.8 Local Rule 8 — Variables Must Not Be Used for Anything Else**

Variables MUST NOT:

- store intermediate values  
- store temporary computations  
- store flags  
- store counters  
- store state  

### **Meaning**  
Variables exist **only** to capture verb results.

---

# **10.4.9 Local Rule 9 — Variables Must Not Be Optimized Away**

Even if a compiler *could* remove them:

- the generated C MUST include them  
- the structure MUST remain intact  

### **Meaning**  
The C Layer is **non‑optimizing by design**.

---

# **10.4.10 Local Rule 10 — Variables Must Be Local to the Function**

Variables MUST NOT be:

- global  
- static  
- extern  
- volatile  
- shared  

### **Meaning**  
Variables are **pure stack‑local**, ephemeral, and isolated.

---

# **10.4.11 Canonical Example — Mixed Verbs**

### **IR**
```
TARGET = LAYER
OPEN_PAYLOAD
EXEC_SCAN
EXEC_BUILD
EXEC_EXPLAIN
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgLayer* ctx) {
    int r1 = scan_context(ctx);
    int r2 = build_context(ctx);
    int r3 = explain_context(ctx);
    return (r1 || r2 || r3);
}
```

### **Meaning**  
Local variable structure is **canonical and immutable**.

---

# **10.4.12 Summary**

Page 10.4 defines the **C Layer Local Variable Rules**:

- one variable per verb  
- sequential numbering  
- order‑preserving  
- no reuse  
- no bulk declarations  
- atomic initialization  
- no mutation  
- no alternate uses  
- no optimization  
- pure stack‑local  

Local variables are the **structural backbone** of the C Layer’s deterministic execution.
