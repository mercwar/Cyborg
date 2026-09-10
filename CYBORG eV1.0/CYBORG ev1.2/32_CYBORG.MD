
# **📘 PAGE 8.0 — CYBORG CONTEXT SYSTEM (OVERVIEW)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **8.0 Overview**

The **Cyborg Context System** defines the structure, rules, and semantics of the objects that verbs operate on.

A *context* is:

- the **sole input** to the Cyborg Module  
- the **sole semantic universe** verbs may observe  
- the **sole mutable structure** (BUILD only)  
- the **sole carrier** of meaning  
- the **sole boundary** of execution  

There is no global state.  
There is no external state.  
There is no environment.  
There is only **context**.

This section introduces the Context System and prepares for the deep specifications that follow.

---

# **8.0.1 The Three Canonical Context Types**

The Cyborg Language defines exactly **three** context types:

1. **CyborgContext**  
2. **CyborgFile**  
3. **CyborgLayer**

These three types form the **complete context universe**.

There are no others.  
There will never be others.  
The context set is **closed**.

---

# **8.0.2 Context Purpose**

Each context type serves a distinct semantic purpose:

| Context Type      | Purpose |
|-------------------|---------|
| **CyborgContext** | AI‑targeted semantic structures |
| **CyborgFile**    | file‑targeted semantic structures |
| **CyborgLayer**   | runtime‑layer semantic structures |

Each context type is:

- structurally distinct  
- semantically distinct  
- target‑bound  
- verb‑compatible  

---

# **8.0.3 Context as the Sole Semantic Universe**

Verbs may only:

- read fields from the context  
- (BUILD only) write fields inside the context  

Verbs may **not**:

- allocate memory  
- free memory  
- create new structures  
- reference external memory  
- store pointers to external systems  

### **Meaning**  
The context is the **entire world** of the Cyborg Module.

---

# **8.0.4 Context Isolation**

The context MUST be:

- private  
- exclusive  
- non‑shared  
- non‑aliased  
- non‑referenced externally  

### **Meaning**  
The context is a **sealed semantic chamber**.

---

# **8.0.5 Context Determinism**

The context MUST:

- contain only deterministic fields  
- contain no pointers to external memory  
- contain no dynamic allocations  
- contain no nondeterministic values  

### **Meaning**  
The context is **mathematically stable**.

---

# **8.0.6 Context Purity**

The context MUST NOT:

- perform I/O  
- contain function pointers  
- contain external handles  
- contain OS resources  
- contain dynamic memory  

### **Meaning**  
The context is **pure data**, not behavior.

---

# **8.0.7 Context Mutation Rules**

Only `BUILD` may mutate context fields.

All other verbs MUST treat the context as read‑only.

Mutation MUST be:

- deterministic  
- internal  
- bounded  
- non‑allocating  
- non‑external  

### **Meaning**  
Mutation is **strictly controlled**.

---

# **8.0.8 Context Lifecycle**

The lifecycle of a context is:

1. **Allocation** (host)  
2. **Initialization** (host)  
3. **Execution** (runtime)  
4. **Mutation** (BUILD only)  
5. **Completion** (runtime)  
6. **Destruction** (host)  

### **Meaning**  
The context lives only for the duration of execution.

---

# **8.0.9 Context and IR**

The IR determines:

- which context type is used  
- which verbs operate on it  
- in what order  

The context system does **not**:

- infer IR  
- validate IR  
- modify IR  

### **Meaning**  
Context is **target‑bound**, not IR‑aware.

---

# **8.0.10 Context System Summary**

The Context System is:

- closed  
- deterministic  
- pure  
- isolated  
- target‑bound  
- mutation‑bounded  
- semantically complete  

These three context types form the **foundation** of all Cyborg semantics.
