

# **📘 PAGE 10.5 — C LAYER CONTEXT HANDLING RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.5 Overview**

The **Context Handling Rules** define how the generated C function must treat the context pointer passed into it.  
These rules ensure:

- purity  
- determinism  
- non‑mutation (except by BUILD)  
- non‑ownership  
- non‑allocation  
- non‑destruction  
- non‑interference  

The context is the **semantic substrate** of the module.  
The C Layer must treat it with **absolute neutrality**.

This section is **normative**.

---

# **10.5.1 Context Rule 1 — Context Is Provided by the Caller**

The generated C function MUST NOT:

- allocate the context  
- initialize the context  
- free the context  
- own the context  

The context is **caller‑owned**.

### **Meaning**  
The C Layer is not responsible for lifecycle management.

---

# **10.5.2 Context Rule 2 — Context Must Be Passed by Pointer**

The function signature MUST be:

```
int cyborg_payload(<CONTEXT_TYPE>* ctx);
```

The context MUST NOT be:

- passed by value  
- passed by reference wrapper  
- passed by handle  
- passed by opaque type  

### **Meaning**  
The context is a **direct pointer** to a fixed struct.

---

# **10.5.3 Context Rule 3 — Context Type Is Determined by IR Target**

The IR target determines the parameter type:

| IR Target | Context Type |
|----------|--------------|
| `AI`     | `CyborgContext*` |
| `FILE`   | `CyborgFile*`    |
| `LAYER`  | `CyborgLayer*`   |

### **Meaning**  
The IR binds the semantic universe.

---

# **10.5.4 Context Rule 4 — Context Must Not Be Modified by the C Layer**

The C Layer MUST NOT:

- write to context fields  
- mutate context state  
- modify structural fields  
- modify semantic fields  
- modify interpretive fields  

### **Exception**  
Mutation performed **inside BUILD** is allowed — but BUILD is a verb, not part of the C Layer.

### **Meaning**  
The C Layer is **pure dispatch**, not logic.

---

# **10.5.5 Context Rule 5 — Context Must Not Be Validated by the C Layer**

The C Layer MUST NOT:

- check for null  
- check for initialization  
- check for version  
- check for structural integrity  

### **Meaning**  
VALIDATE is the verb responsible for validation — not the C Layer.

---

# **10.5.6 Context Rule 6 — Context Must Not Be Inspected**

The C Layer MUST NOT:

- read context fields  
- branch based on context values  
- compute based on context state  
- perform logic involving context internals  

### **Meaning**  
The C Layer is **context‑agnostic**.

---

# **10.5.7 Context Rule 7 — Context Must Not Be Copied**

The C Layer MUST NOT:

- create a local copy  
- clone the context  
- duplicate memory  
- allocate buffers for it  

### **Meaning**  
The context is **singular and unreplicated**.

---

# **10.5.8 Context Rule 8 — Context Must Not Be Destroyed**

The C Layer MUST NOT:

- free the context  
- release memory  
- call cleanup functions  
- perform teardown  

### **Meaning**  
Context destruction is **caller‑owned**.

---

# **10.5.9 Context Rule 9 — Context Must Be Passed Unmodified to Every Verb**

Every verb call MUST be:

```
<verb>_context(ctx)
```

The same pointer.  
The same object.  
The same semantic universe.

### **Meaning**  
The context is **shared across all verbs**.

---

# **10.5.10 Context Rule 10 — Context Must Be Treated as Opaque**

The C Layer MUST treat the context as:

- opaque  
- uninterpreted  
- unexamined  
- unmodified  

### **Meaning**  
Only verbs may interpret or mutate context.

---

# **10.5.11 Canonical Example — Mixed Verbs**

### **IR**
```
TARGET = FILE
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_BUILD
EXEC_EXPLAIN
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgFile* ctx) {
    int r1 = validate_context(ctx);
    int r2 = build_context(ctx);
    int r3 = explain_context(ctx);
    return (r1 || r2 || r3);
}
```

### **Meaning**
The context is:

- passed unchanged  
- passed unexamined  
- passed unmodified  
- passed to every verb  

This is the **canonical context handling pattern**.

---

# **10.5.12 Summary**

Page 10.5 defines the **C Layer Context Handling Rules**:

- context is caller‑owned  
- passed by pointer  
- target‑determined  
- never modified by the C Layer  
- never validated by the C Layer  
- never inspected  
- never copied  
- never destroyed  
- passed unchanged to every verb  
- treated as opaque  

The context is the **semantic universe**, and the C Layer must treat it with **absolute neutrality**.
