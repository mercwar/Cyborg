

# **📘 PAGE 10.7 — C LAYER CONTROL‑FLOW RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.7 Overview**

The **Control‑Flow Rules** define what the generated C function may and may not do with respect to:

- branching  
- looping  
- conditional logic  
- early termination  
- flow manipulation  

The C Layer is not a program.  
It is a **mechanical execution schedule** derived from IR.  
Its control flow must be **perfectly linear**.

This section is **normative**.

---

# **10.7.1 Control Rule 1 — No Branching**

The C Layer MUST NOT contain:

- `if`  
- `else`  
- `switch`  
- `case`  
- conditional operators (`?:`)  

### **Meaning**  
Execution is **branchless**.

---

# **10.7.2 Control Rule 2 — No Loops**

The C Layer MUST NOT contain:

- `for`  
- `while`  
- `do`  
- recursion  
- iteration of any kind  

### **Meaning**  
Execution is **non‑iterative**.

---

# **10.7.3 Control Rule 3 — No Early Returns**

The C Layer MUST NOT:

- return early  
- exit based on a verb result  
- short‑circuit the OR chain  

### **Forbidden**
```c
if (r1) return r1;   // forbidden
```

### **Meaning**  
All verbs MUST run.

---

# **10.7.4 Control Rule 4 — No Goto or Jumps**

The C Layer MUST NOT contain:

- `goto`  
- labels  
- jumps  
- computed jumps  

### **Meaning**  
Execution is **strictly sequential**.

---

# **10.7.5 Control Rule 5 — No Exception Handling**

The C Layer MUST NOT contain:

- `try`  
- `catch`  
- `throw`  
- `longjmp`  
- `setjmp`  

### **Meaning**  
Execution is **non‑exceptional**.

---

# **10.7.6 Control Rule 6 — No Conditional Compilation**

The C Layer MUST NOT contain:

- `#ifdef`  
- `#ifndef`  
- `#if`  
- `#elif`  
- `#endif`  

### **Meaning**  
The payload is **platform‑invariant**.

---

# **10.7.7 Control Rule 7 — No Conditional Verb Invocation**

The C Layer MUST NOT:

- call verbs based on conditions  
- skip verbs based on context  
- reorder verbs based on logic  

### **Meaning**  
Verb invocation is **literal**.

---

# **10.7.8 Control Rule 8 — No Flow‑Dependent Behavior**

The C Layer MUST NOT:

- compute flags  
- track state  
- branch on memory  
- branch on context  
- branch on verb results  

### **Meaning**  
Control flow is **static**.

---

# **10.7.9 Control Rule 9 — Only One Control‑Flow Construct Allowed**

The only allowed control‑flow construct is:

```
return (r1 || r2 || ... || rn);
```

This is the **sole** control‑flow operation in the entire function.

### **Meaning**  
The payload ends with a **single deterministic verdict**.

---

# **10.7.10 Control Rule 10 — Control Flow Must Be Deterministic**

Given the same IR:

- the same control flow MUST be generated  
- on all platforms  
- with all compilers  
- with all optimization levels  

### **Meaning**  
Control flow is **mathematically reproducible**.

---

# **10.7.11 Canonical Example — Mixed Verbs**

### **IR**
```
TARGET = FILE
OPEN_PAYLOAD
EXEC_SCAN
EXEC_BUILD
EXEC_EXPLAIN
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgFile* ctx) {
    int r1 = scan_context(ctx);
    int r2 = build_context(ctx);
    int r3 = explain_context(ctx);
    return (r1 || r2 || r3);
}
```

### **Control‑Flow Interpretation**
- no branches  
- no loops  
- no early returns  
- no conditions  
- no jumps  
- single final return  

This is the **canonical control‑flow pattern**.

---

# **10.7.12 Summary**

Page 10.7 defines the **C Layer Control‑Flow Rules**:

- no branching  
- no loops  
- no early returns  
- no jumps  
- no exceptions  
- no conditional compilation  
- no conditional invocation  
- no flow‑dependent behavior  
- only one final return  
- deterministic control flow  

The C Layer is **perfectly linear**, **perfectly literal**, and **perfectly deterministic**.
