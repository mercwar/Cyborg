
# **📘 PAGE 7.8 — VERB PURITY RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **7.8 Overview**

The **Verb Purity Rules** define the strict behavioral boundaries that every verb must obey.  
These rules ensure that verbs:

- never cause side effects  
- never interact with external systems  
- never allocate memory  
- never mutate state (except BUILD)  
- never break determinism  
- never violate isolation  

Purity is not a guideline.  
Purity is **law**.

This section is **normative**.

---

# **7.8.1 Purity Principle 1 — No Side Effects**

All verbs MUST NOT:

- perform I/O  
- print  
- log  
- write to files  
- write to network  
- modify global variables  
- modify static variables  
- modify external systems  

### **Meaning**  
Verbs operate in a **sealed semantic chamber**.

---

# **7.8.2 Purity Principle 2 — No Memory Allocation**

Verbs MUST NOT:

- allocate memory  
- free memory  
- resize memory  
- create dynamic structures  
- use malloc, calloc, realloc, free  
- use new/delete  

### **Meaning**  
All memory is fixed and provided by the Runtime Layer.

---

# **7.8.3 Purity Principle 3 — No External Calls**

Verbs MUST NOT call:

- system APIs  
- OS functions  
- external libraries  
- network APIs  
- file system APIs  
- hardware interfaces  

### **Meaning**  
Verbs are **self‑contained**.

---

# **7.8.4 Purity Principle 4 — No Global State**

Verbs MUST NOT:

- read global variables  
- write global variables  
- rely on static state  
- rely on thread‑local state  
- rely on environment variables  

### **Meaning**  
Verbs cannot “see” outside the context.

---

# **7.8.5 Purity Principle 5 — No Concurrency**

Verbs MUST NOT:

- spawn threads  
- join threads  
- run async tasks  
- use parallelism  
- rely on thread scheduling  

### **Meaning**  
Verb execution is **single‑threaded**.

---

# **7.8.6 Purity Principle 6 — No Exceptions**

Verbs MUST NOT:

- throw exceptions  
- catch exceptions  
- use longjmp/setjmp  
- use structured exception handling  

### **Meaning**  
Verb execution is **linear and uninterrupted**.

---

# **7.8.7 Purity Principle 7 — No Cross‑Verb Communication**

Verbs MUST NOT:

- call other verbs  
- encode messages for other verbs  
- rely on execution order  
- share state  
- use the context as a message bus  

### **Meaning**  
Verbs are **semantic islands**.

---

# **7.8.8 Purity Principle 8 — BUILD Is the Only Mutator**

Only `BUILD` may:

- modify context fields  
- populate missing values  
- compute derived values  
- restructure internal semantic blocks  

All other verbs MUST treat the context as read‑only.

### **Meaning**  
Mutation is **strictly bounded**.

---

# **7.8.9 Purity Principle 9 — No Inference**

Verbs MUST NOT:

- infer missing fields  
- guess intended meaning  
- repair invalid structures  
- fill in absent data  

### **Meaning**  
Verbs operate only on **what exists**, not what “should” exist.

---

# **7.8.10 Purity Principle 10 — Deterministic Purity**

Purity MUST be:

- complete  
- consistent  
- platform‑invariant  
- compiler‑invariant  
- optimization‑invariant  

### **Meaning**  
Purity is **absolute**.

---

# **7.8.11 Full Purity Example**

### **IR**
```cyborg
TARGET = AI
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
int cyborg_payload(CyborgContext* ctx) {
    int r1 = validate_context(ctx);
    int r2 = scan_context(ctx);
    int r3 = build_context(ctx);
    int r4 = give_context(ctx);
    int r5 = explain_context(ctx);
    return (r1 || r2 || r3 || r4 || r5);
}
```

### **Purity Interpretation**
- VALIDATE: pure  
- SCAN: pure  
- BUILD: deterministic mutation  
- GIVE: pure  
- EXPLAIN: pure  

No side effects.  
No external calls.  
No memory allocation.  
No global state.  
No inference.  
No communication.  
No exceptions.

This is the **canonical purity chain**.

---

# **7.8.12 Summary**

Page 7.8 defines the **Verb Purity Rules**:

- no side effects  
- no memory allocation  
- no external calls  
- no global state  
- no concurrency  
- no exceptions  
- no cross‑verb communication  
- BUILD is the only mutator  
- no inference  
- purity is deterministic and universal  

These rules ensure that the Five Verbs remain **pure, isolated, and ceremonially invariant**.
