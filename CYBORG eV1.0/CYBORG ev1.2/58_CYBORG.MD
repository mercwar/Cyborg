

# **📘 PAGE 8.1 — CONTEXT: CYBORGCONTEXT (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **8.1 Overview**

`CyborgContext` is the **primary context type** of the Cyborg Language.  
It is the target used when IR declares:

```
TARGET = AI
```

This context represents **AI‑semantic structures**, the internal data universe upon which the Five Verbs operate when the module is aimed at AI‑domain semantics.

This section is **normative**.

---

# **8.1.1 CyborgContext — Purpose**

`CyborgContext` exists to hold:

- AI‑domain semantic fields  
- structural data required by VALIDATE  
- observable data required by SCAN  
- mutable fields required by BUILD  
- semantic content required by GIVE  
- interpretive structures required by EXPLAIN  

It is the **semantic substrate** for AI‑targeted modules.

---

# **8.1.2 CyborgContext — Structural Requirements**

`CyborgContext` MUST:

- be a fixed‑size C struct  
- contain no pointers to external memory  
- contain no dynamic allocations  
- contain no function pointers  
- contain no OS handles  
- contain no external resources  

### **Meaning**  
`CyborgContext` is **pure data**, not behavior.

---

# **8.1.3 CyborgContext — Determinism Requirements**

The context MUST:

- contain only deterministic fields  
- contain no nondeterministic values  
- contain no timestamps  
- contain no random seeds  
- contain no environment‑derived data  

### **Meaning**  
The context is **mathematically stable**.

---

# **8.1.4 CyborgContext — Purity Requirements**

The context MUST NOT:

- perform I/O  
- allocate memory  
- free memory  
- reference external systems  
- contain mutable global state  

### **Meaning**  
The context is **passive**, not active.

---

# **8.1.5 CyborgContext — Mutation Rules**

Only `BUILD` may modify fields inside the context.

Mutation MUST be:

- deterministic  
- internal  
- bounded  
- non‑allocating  
- non‑external  

### **Forbidden**
- resizing arrays  
- allocating buffers  
- storing external pointers  
- creating dynamic structures  

### **Allowed**
- updating integers  
- setting flags  
- populating fixed arrays  
- computing derived values  

---

# **8.1.6 CyborgContext — Field Categories**

A canonical `CyborgContext` contains fields in these categories:

### **1. Structural Fields**
- required for VALIDATE  
- define the shape of the context  

### **2. Observational Fields**
- read by SCAN  
- reveal semantic structure  

### **3. Constructive Fields**
- written by BUILD  
- hold derived or assembled data  

### **4. Semantic Fields**
- consumed by GIVE  
- represent meaningful content  

### **5. Interpretive Fields**
- consumed by EXPLAIN  
- represent relationships and meaning  

Each category is **read‑only** except for BUILD’s constructive fields.

---

# **8.1.7 CyborgContext — Canonical C Definition (Abstract)**

The standard does **not** define exact field names,  
but it defines the **shape**:

```c
typedef struct CyborgContext {
    /* Structural Fields */
    int initialized;
    int version;

    /* Observational Fields */
    int scan_markers[16];

    /* Constructive Fields (BUILD may modify) */
    int build_flags;
    int derived_values[8];

    /* Semantic Fields */
    int meaning_units[32];

    /* Interpretive Fields */
    int explanation_links[16];
} CyborgContext;
```

### **Meaning**  
This is a **template**, not a mandate.  
Implementations must follow the **rules**, not the exact layout.

---

# **8.1.8 CyborgContext — Verb Compatibility**

### **VALIDATE**
- checks structural fields  
- confirms initialization  
- confirms invariants  

### **SCAN**
- reads observational fields  
- identifies semantic markers  

### **BUILD**
- populates constructive fields  
- computes derived values  

### **GIVE**
- extracts semantic fields  
- confirms semantic completeness  

### **EXPLAIN**
- interprets relationships  
- reads interpretive fields  

Each verb operates on **its own category**.

---

# **8.1.9 CyborgContext — Failure Behavior**

If the context is invalid:

- VALIDATE returns non‑zero  
- SCAN still runs  
- BUILD still runs  
- GIVE still runs  
- EXPLAIN still runs  
- no recovery occurs  
- no mutation rollback occurs  
- no logging occurs  

### **Meaning**  
Failure is **silent** and **non‑interrupting**.

---

# **8.1.10 CyborgContext — Lifecycle**

1. **Allocation**  
   - host allocates struct  
2. **Initialization**  
   - host sets structural fields  
3. **Execution**  
   - runtime passes context to verbs  
4. **Mutation**  
   - BUILD modifies constructive fields  
5. **Completion**  
   - runtime returns aggregated result  
6. **Destruction**  
   - host frees struct  

### **Meaning**  
The context exists only for the duration of execution.

---

# **8.1.11 Summary**

Page 8.1 defines **CyborgContext**:

- pure  
- deterministic  
- isolated  
- fixed‑size  
- non‑allocating  
- non‑external  
- BUILD‑mutable  
- verb‑compatible  
- target‑bound  

`CyborgContext` is the **AI semantic universe** of the Cyborg Language.
