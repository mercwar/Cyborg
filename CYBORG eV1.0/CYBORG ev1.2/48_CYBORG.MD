
# **📘 PAGE 10.3 — C LAYER AGGREGATION RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **10.3 Overview**

The **Aggregation Rules** define how the C Layer combines the return values of all invoked verbs into a single final result.

Aggregation is:

- deterministic  
- literal  
- non‑short‑circuiting  
- non‑optimizing  
- non‑inferential  
- binary  

This section is **normative**.

---

# **10.3.1 Aggregation Rule 1 — Every Verb Produces an int**

Each verb returns:

- `0` → success  
- non‑zero → failure  

No other return types are allowed.

### **Meaning**  
Verb results are **binary truth values**.

---

# **10.3.2 Aggregation Rule 2 — Every Verb Result Must Be Captured**

Each verb call MUST assign its return value to a unique local variable:

```c
int r1 = validate_context(ctx);
int r2 = scan_context(ctx);
int r3 = build_context(ctx);
```

### **Meaning**  
No verb result may be discarded.

---

# **10.3.3 Aggregation Rule 3 — Aggregation Uses Logical OR**

The final result MUST be:

```
return (r1 || r2 || r3 || ... || rn);
```

### **Meaning**  
If *any* verb fails, the module fails.

---

# **10.3.4 Aggregation Rule 4 — Aggregation Order Matches Verb Order**

The OR chain MUST preserve the order of verb execution:

```
return (r1 || r2 || r3);
```

NOT:

```
return (r3 || r1 || r2);
```

NOT:

```
return (r1 || r3);   // missing r2 — forbidden
```

### **Meaning**  
Aggregation is **structurally faithful** to IR.

---

# **10.3.5 Aggregation Rule 5 — No Short‑Circuiting**

Even though OR *could* short‑circuit in C, the runtime semantics require:

- all verbs MUST run  
- all results MUST be captured  
- aggregation MUST include all results  

### **Meaning**  
Execution is **complete**, not conditional.

---

# **10.3.6 Aggregation Rule 6 — No Optimization**

The C Layer MUST NOT:

- collapse OR chains  
- reorder OR chains  
- remove redundant ORs  
- simplify expressions  

### **Forbidden**
```
return (r1 | r2 | r3);   // bitwise OR — forbidden
return r1 || r2;         // missing r3 — forbidden
return !!(r1 + r2 + r3); // arithmetic — forbidden
```

### **Meaning**  
Aggregation is **literal**, not optimized.

---

# **10.3.7 Aggregation Rule 7 — No Early Return**

The C Layer MUST NOT:

- return early  
- branch  
- conditionally skip aggregation  

### **Forbidden**
```c
if (r1) return r1;   // forbidden
```

### **Meaning**  
Aggregation is **branchless**.

---

# **10.3.8 Aggregation Rule 8 — Aggregation Is Deterministic**

Given the same verb results:

- the same OR chain MUST produce the same final value  
- on all platforms  
- with all compilers  
- with all optimization levels  

### **Meaning**  
Aggregation is **mathematically reproducible**.

---

# **10.3.9 Aggregation Rule 9 — Aggregation Is Pure**

Aggregation MUST NOT:

- allocate memory  
- perform I/O  
- call external APIs  
- modify global state  
- depend on environment  

### **Meaning**  
Aggregation is **pure computation**.

---

# **10.3.10 Aggregation Rule 10 — Aggregation Is the Final Step**

After aggregation:

- no further computation occurs  
- no cleanup occurs  
- no mutation occurs  
- no additional verbs run  

### **Meaning**  
Aggregation is the **terminal semantic act**.

---

# **10.3.11 Canonical Aggregation Example**

### **IR**
```
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
SEAL
```

### **Generated C**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = validate_context(ctx);
    int r2 = scan_context(ctx);
    int r3 = build_context(ctx);
    return (r1 || r2 || r3);
}
```

### **Meaning**
This is the **canonical aggregation pattern**.

---

# **10.3.12 Summary**

Page 10.3 defines the **C Layer Aggregation Rules**:

- every verb returns int  
- every result is captured  
- aggregation uses logical OR  
- order is preserved  
- no short‑circuiting  
- no optimization  
- no early return  
- deterministic  
- pure  
- terminal  

Aggregation is the **final verdict** of the Cyborg Module.
