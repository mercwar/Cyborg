
# **📘 PAGE 7.0 — CYBORG VERB SYSTEM (OVERVIEW)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **7.0 Overview**

The **Cyborg Verb System** is the semantic engine of the entire language.  
Where the C Layer is execution, and the Runtime Layer is environment, the Verb System is **meaning**.

A verb is:

- a pure semantic operation  
- externally implemented  
- statically bound  
- context‑bound  
- deterministic  
- non‑interactive  
- non‑inferential  

Verbs define *what a module does*.  
The C Layer defines *how it is executed*.  
The Runtime Layer defines *where it is executed*.

This section introduces the Verb System and prepares for the deep specifications that follow.

---

# **7.0.1 The Five Canonical Verbs**

The Cyborg Language defines exactly **five** verbs:

1. **VALIDATE**  
2. **SCAN**  
3. **BUILD**  
4. **GIVE**  
5. **EXPLAIN**

These verbs form the **complete semantic universe** of the language.

There are no others.  
There will never be others.  
The verb set is **closed**.

---

# **7.0.2 Verb Execution Model**

Each verb:

- is a standalone semantic unit  
- takes exactly one context parameter  
- returns exactly one integer  
- performs exactly one conceptual action  
- has no side effects (except BUILD)  
- is deterministic  
- is pure  
- is isolated  

### **Meaning**  
Verbs are **atomic semantic operations**.

---

# **7.0.3 Verb Ordering**

The IR determines the order of verb execution.

The Verb System itself:

- does not impose ordering  
- does not infer ordering  
- does not optimize ordering  
- does not validate ordering  

### **Meaning**  
Order is a property of IR, not verbs.

---

# **7.0.4 Verb Purity**

All verbs MUST be pure except `BUILD`.

### **Pure Verbs**
- VALIDATE  
- SCAN  
- GIVE  
- EXPLAIN  

### **Impure Verb**
- BUILD (may modify context fields)

No other verb may modify context.

---

# **7.0.5 Verb Determinism**

Each verb MUST:

- produce the same output for the same input  
- never depend on external state  
- never depend on timing  
- never depend on randomness  
- never depend on environment variables  
- never depend on global state  

### **Meaning**  
Verb semantics are **mathematically reproducible**.

---

# **7.0.6 Verb Isolation**

Verbs MUST NOT:

- call each other  
- share state  
- communicate indirectly  
- rely on execution order  
- mutate global variables  
- access external resources  

### **Meaning**  
Each verb is a **semantic island**.

---

# **7.0.7 Verb Binding**

Verbs MUST be:

- statically linked  
- uniquely implemented  
- target‑specific  
- non‑overridable  
- non‑substitutable  

### **Meaning**  
Verb semantics are **immutable**.

---

# **7.0.8 Verb Return Semantics**

Each verb returns:

- `0` → success  
- non‑zero → failure  

The C Layer aggregates these results with OR.

### **Meaning**  
Verb results are **numeric truth values**.

---

# **7.0.9 Verb Context Rules**

Each verb receives exactly one parameter:

- `CyborgContext*`  
- `CyborgFile*`  
- `CyborgLayer*`  

depending on IR target.

Verbs MUST NOT:

- reinterpret the context  
- cast the context  
- modify the context (except BUILD)  
- infer missing fields  

### **Meaning**  
Verbs operate strictly within their target domain.

---

# **7.0.10 Verb System Summary**

The Verb System is:

- closed  
- deterministic  
- pure  
- isolated  
- context‑bound  
- statically linked  
- semantically atomic  

These five verbs form the **semantic foundation** of the Cyborg Language.
