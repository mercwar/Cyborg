
# **📘 PAGE 7.3 — VERB: BUILD (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **7.3 Overview**

`BUILD` is the **third canonical verb** of the Cyborg Language and the **only impure verb** in the entire system.

Where:

- `VALIDATE` confirms structure  
- `SCAN` reveals structure  

**BUILD transforms structure.**

> **BUILD is the sole verb allowed to modify the context.**

It is the engine of construction, mutation, and semantic evolution.

This section is **normative**.

---

# **7.3.1 BUILD — Semantic Definition**

`BUILD` MUST:

- modify fields inside the context  
- construct new semantic structures  
- populate missing values  
- assemble derived data  
- prepare the context for downstream verbs  

`BUILD` MUST NOT:

- change the context’s type  
- change the context’s size  
- allocate dynamic memory  
- free memory  
- perform I/O  
- call other verbs  
- depend on external state  

### **Meaning**  
`BUILD` is the **context constructor**, not a general‑purpose mutator.

---

# **7.3.2 BUILD — Determinism Rules**

`BUILD` MUST:

- produce the same modifications for the same input  
- never depend on timing  
- never depend on randomness  
- never depend on environment variables  
- never depend on global state  

### **Meaning**  
Even though it mutates, `BUILD` is **deterministic**.

---

# **7.3.3 BUILD — Purity Exception**

`BUILD` is the **only verb** allowed to:

- write to context fields  
- modify internal state  
- populate missing values  
- restructure internal semantic data  

### **Forbidden for BUILD**
- allocating memory  
- freeing memory  
- performing I/O  
- modifying global variables  
- modifying static variables  

### **Allowed for BUILD**
- modifying fields *inside the context object only*

---

# **7.3.4 BUILD — Isolation Rules**

`BUILD` MUST NOT:

- call other verbs  
- communicate with other verbs  
- rely on execution order  
- share state with other verbs  

### **Meaning**  
Even though it mutates, `BUILD` is still a **semantic island**.

---

# **7.3.5 BUILD — Return Semantics**

`BUILD` MUST return:

- `0` → build successful  
- non‑zero → build detected a semantic issue  

### **Meaning**  
`BUILD` is a **binary construction test**.

---

# **7.3.6 BUILD — Context Mutation Rules**

`BUILD` MAY:

- write to fields  
- update counters  
- populate arrays  
- set flags  
- compute derived values  
- restructure internal semantic blocks  

`BUILD` MUST NOT:

- change the context’s type  
- change the context’s size  
- allocate memory  
- free memory  
- create external references  
- store pointers to external memory  

### **Meaning**  
Mutation is **bounded** and **internal**.

---

# **7.3.7 BUILD — Failure Semantics**

If `BUILD` returns non‑zero:

- the C Layer MUST still execute all remaining verbs  
- the Runtime MUST NOT stop execution  
- the Runtime MUST NOT attempt recovery  
- the Runtime MUST NOT undo mutations  
- the Runtime MUST NOT log or report the failure  

### **Meaning**  
Failure is **silent**, **contained**, and **non‑interrupting**.

---

# **7.3.8 BUILD — Canonical Implementation Pattern**

### **AI Target**
```c
int build_context(CyborgContext* ctx);
```

### **FILE Target**
```c
int build_context(CyborgFile* file);
```

### **LAYER Target**
```c
int build_context(CyborgLayer* layer);
```

### **Meaning**  
The signature is **fixed**, **target‑bound**, and **non‑overridable**.

---

# **7.3.9 BUILD — Canonical Behavior Examples**

### **Successful Build**
- fields populated  
- structures assembled  
- derived values computed  
- returns `0`  

### **Failed Build**
- missing required data  
- structural contradictions  
- semantic impossibilities  
- returns non‑zero  

### **Meaning**  
`BUILD` is the **constructor** of the Cyborg Language.

---

# **7.3.10 BUILD — Full Canonical Example**

### **IR**
```cyborg
TARGET = FILE
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_GIVE
SEAL
```

### **C Output**
```c
int cyborg_payload(CyborgFile* file) {
    int r1 = validate_context(file);
    int r2 = scan_context(file);
    int r3 = build_context(file);
    int r4 = give_context(file);
    return (r1 || r2 || r3 || r4);
}
```

### **Interpretation**
- `VALIDATE` checks structure  
- `SCAN` reveals structure  
- `BUILD` transforms structure  
- `GIVE` consumes the transformed structure  

This is the **canonical BUILD flow**.

---

# **7.3.11 Summary**

Page 7.3 defines the verb **BUILD**:

- the only impure verb  
- deterministic mutation  
- internal‑only modification  
- no external effects  
- no memory allocation  
- no I/O  
- no inference  
- no cross‑verb communication  
- returns binary truth  

`BUILD` is the **constructor and transformer** of the Cyborg Language.
