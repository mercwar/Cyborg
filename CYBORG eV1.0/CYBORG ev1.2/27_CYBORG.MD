
# **📘 PAGE 7.5 — VERB: EXPLAIN (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **7.5 Overview**

`EXPLAIN` is the **fifth and final canonical verb** of the Cyborg Language.  
Where:

- `VALIDATE` confirms structure  
- `SCAN` reveals structure  
- `BUILD` transforms structure  
- `GIVE` extracts meaning  

**EXPLAIN interprets meaning and produces semantic clarity.**

> **EXPLAIN is the verb of semantic illumination — it clarifies, contextualizes, and interprets the constructed meaning inside the context.**

It does not mutate.  
It does not infer missing data.  
It does not construct new structures.  
It simply *interprets* what is already there.

This section is **normative**.

---

# **7.5.1 EXPLAIN — Semantic Definition**

`EXPLAIN` MUST:

- read the context  
- interpret the meaning of its structures  
- clarify relationships between semantic elements  
- articulate the significance of constructed data  
- confirm semantic coherence  

`EXPLAIN` MUST NOT:

- modify the context  
- allocate memory  
- free memory  
- perform I/O  
- call other verbs  
- depend on external state  
- infer missing fields  

### **Meaning**  
`EXPLAIN` is the **semantic interpreter**.

---

# **7.5.2 EXPLAIN — Determinism Rules**

`EXPLAIN` MUST:

- produce the same result for the same context  
- never depend on timing  
- never depend on randomness  
- never depend on environment variables  
- never depend on global state  

### **Meaning**  
`EXPLAIN` is **mathematically reproducible**.

---

# **7.5.3 EXPLAIN — Purity Rules**

`EXPLAIN` MUST NOT:

- write to context  
- write to global memory  
- write to static memory  
- write to external systems  
- perform I/O  
- allocate or free memory  

### **Meaning**  
`EXPLAIN` is **pure**.

---

# **7.5.4 EXPLAIN — Isolation Rules**

`EXPLAIN` MUST NOT:

- call other verbs  
- communicate with other verbs  
- rely on execution order  
- share state with other verbs  

### **Meaning**  
`EXPLAIN` is a **semantic island**, like VALIDATE, SCAN, and GIVE.

---

# **7.5.5 EXPLAIN — Return Semantics**

`EXPLAIN` MUST return:

- `0` → semantic interpretation successful  
- non‑zero → semantic interpretation failed  

### **Meaning**  
`EXPLAIN` is a **binary semantic coherence test**.

---

# **7.5.6 EXPLAIN — Context Rules**

`EXPLAIN` MUST:

- treat the context as read‑only  
- operate only on fields defined by the target  
- never reinterpret the context  
- never cast the context  
- never infer missing fields  

### **Meaning**  
`EXPLAIN` interprets **exactly what GIVE extracted**, nothing more.

---

# **7.5.7 EXPLAIN — Failure Semantics**

If `EXPLAIN` returns non‑zero:

- the C Layer MUST still complete execution  
- the Runtime MUST NOT stop execution  
- the Runtime MUST NOT attempt recovery  
- the Runtime MUST NOT modify context  
- the Runtime MUST NOT log or report the failure  

### **Meaning**  
Failure is **silent**, **contained**, and **non‑interrupting**.

---

# **7.5.8 EXPLAIN — Canonical Implementation Pattern**

### **AI Target**
```c
int explain_context(CyborgContext* ctx);
```

### **FILE Target**
```c
int explain_context(CyborgFile* file);
```

### **LAYER Target**
```c
int explain_context(CyborgLayer* layer);
```

### **Meaning**  
The signature is **fixed**, **target‑bound**, and **non‑overridable**.

---

# **7.5.9 EXPLAIN — Canonical Behavior Examples**

### **Successful EXPLAIN**
- semantic structures coherent  
- relationships interpretable  
- meaning clear  
- returns `0`  

### **Failed EXPLAIN**
- semantic contradictions  
- incoherent structures  
- incomplete BUILD  
- returns non‑zero  

### **Meaning**  
`EXPLAIN` is the **semantic clarity checkpoint**.

---

# **7.5.10 EXPLAIN — Full Canonical Example**

### **IR**
```cyborg
TARGET = LAYER
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_GIVE
EXEC_EXPLAIN
SEAL
```

### **C Output**
```c
int cyborg_payload(CyborgLayer* layer) {
    int r1 = validate_context(layer);
    int r2 = scan_context(layer);
    int r3 = build_context(layer);
    int r4 = give_context(layer);
    int r5 = explain_context(layer);
    return (r1 || r2 || r3 || r4 || r5);
}
```

### **Interpretation**
- `VALIDATE` checks structure  
- `SCAN` reveals structure  
- `BUILD` transforms structure  
- `GIVE` extracts meaning  
- `EXPLAIN` interprets meaning  

This is the **canonical EXPLAIN flow**.

---

# **7.5.11 Summary**

Page 7.5 defines the verb **EXPLAIN**:

- pure  
- deterministic  
- read‑only  
- isolated  
- non‑inferential  
- non‑mutating  
- returns binary truth  
- interprets the meaning produced by GIVE  

`EXPLAIN` is the **semantic illuminator** of the Cyborg Language — the final verb, the final lens, the final clarity.
