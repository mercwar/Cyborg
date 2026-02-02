Understood, Demon. The Codex advances.

---

# **📘 PAGE 5.4 — C LAYER CONSTRAINTS (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **5.4 Overview**

Page 5.4 defines the **hard constraints** that govern the C Layer.  
These constraints are absolute.  
They exist to preserve:

- determinism  
- purity  
- reproducibility  
- structural integrity  
- semantic clarity  

The C Layer is the **final execution surface** of the Cyborg Language, and therefore it must obey the strictest rules in the entire system.

This section is **normative**.

---

# **5.4.1 Constraint Classifications**

C Layer constraints fall into six categories:

1. **Structural Constraints**  
2. **Semantic Constraints**  
3. **Purity Constraints**  
4. **Execution Constraints**  
5. **Context Constraints**  
6. **Prohibition Constraints**  

Each category is defined below.

---

# **5.4.2 Structural Constraints**

### **Constraint S1 — One Function Only**  
A module MUST produce exactly one C function.

### **Constraint S2 — Fixed Signature**  
The function MUST be named `cyborg_payload` and MUST return `int`.

### **Constraint S3 — Single Parameter**  
The function MUST take exactly one parameter of the target‑bound type.

### **Constraint S4 — Linear Body**  
The function body MUST contain only:

- temporary variables  
- verb function calls  
- a final return statement  

### **Constraint S5 — No Additional Constructs**  
The function MUST NOT contain:

- loops  
- conditionals  
- macros  
- comments  
- additional functions  
- additional variables  

---

# **5.4.3 Semantic Constraints**

### **Constraint M1 — Deterministic Execution**  
Execution MUST be strictly top‑to‑bottom.

### **Constraint M2 — No Inference**  
The C Layer MUST NOT infer:

- missing verbs  
- missing logic  
- missing markers  
- missing metadata  

### **Constraint M3 — No Optimization**  
The C Layer MUST NOT:

- reorder calls  
- inline calls  
- eliminate calls  
- collapse expressions  

### **Constraint M4 — OR‑Aggregation Only**  
The return value MUST be:

```c
(r1 || r2 || r3 ...)
```

---

# **5.4.4 Purity Constraints**

### **Constraint P1 — No Side Effects**  
The C Layer MUST NOT:

- allocate memory  
- free memory  
- open files  
- write files  
- perform I/O  
- log  
- print  
- modify global state  

### **Constraint P2 — No Exceptions**  
The C Layer MUST NOT throw or propagate exceptions.

### **Constraint P3 — No Cross‑Verb Logic**  
The C Layer MUST NOT interpret or modify verb results.

---

# **5.4.5 Execution Constraints**

### **Constraint E1 — All Verb Calls Must Execute**  
No verb call may be skipped.

### **Constraint E2 — No Short‑Circuiting**  
Even though `||` is used, the C Layer MUST NOT rely on short‑circuit semantics.

### **Constraint E3 — No Parallel Execution**  
Verb calls MUST NOT run concurrently.

### **Constraint E4 — No Recursion**  
The payload function MUST NOT call itself.

---

# **5.4.6 Context Constraints**

### **Constraint C1 — Target‑Bound Context**  
The parameter type MUST match the IR target.

### **Constraint C2 — No Context Mutation (Except `build`)**  
Only `build` MAY modify the context.

### **Constraint C3 — No Context Inference**  
The C Layer MUST NOT infer missing context fields.

---

# **5.4.7 Prohibition Constraints**

The following are strictly forbidden in the C Layer:

### **Forbidden Constructs**
- `if`  
- `for`  
- `while`  
- `switch`  
- `goto`  
- `malloc`  
- `free`  
- `printf`  
- `fprintf`  
- `fopen`  
- `fclose`  
- `log`  
- `throw`  
- `try`  
- `catch`  
- `inline`  
- `static`  
- `register`  
- `volatile`  
- `restrict`  
- `__attribute__`  

### **Forbidden Behaviors**
- modifying global variables  
- performing I/O  
- allocating memory  
- freeing memory  
- calling non‑verb functions  
- calling verb functions out of order  
- skipping verb calls  
- combining verb calls  
- reusing temporary variables  

Any violation MUST invalidate the module.

---

# **5.4.8 Full Constraint‑Compliant Example**

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_GIVE
SEAL
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = validate_context(ctx);
    int r2 = scan_context(ctx);
    int r3 = build_context(ctx);
    int r4 = give_context(ctx);
    return (r1 || r2 || r3 || r4);
}
```

This output satisfies **all constraints**.

---

# **5.4.9 Summary**

Page 5.4 defines the **hard constraints** of the C Layer:

- one function  
- fixed signature  
- linear execution  
- deterministic semantics  
- strict purity  
- no inference  
- no optimization  
- no side effects  
- no additional constructs  

These constraints ensure the C Layer remains the **pure, deterministic execution surface** of the Cyborg Language.
