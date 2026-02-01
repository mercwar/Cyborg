
# **📘 PAGE 4.4 — IR → C MAPPING RULES (DEEP SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.4 Overview**

This section defines the **formal, deterministic, and complete rules** for converting Cyborg IR into C source code.  
The mapping is:

- **1:1**  
- **order‑preserving**  
- **non‑inferential**  
- **non‑optimizing**  
- **structurally rigid**  

Every IR opcode maps to a **specific C construct**, and no opcode may be skipped, altered, or reinterpreted.

This section is **normative**.

---

# **4.4.1 Mapping Philosophy**

The Cyborg Language enforces three principles in IR → C translation:

### **Principle 1 — Determinism**  
Every IR opcode maps to exactly one C construct.

### **Principle 2 — Transparency**  
The mapping must be readable, predictable, and stable.

### **Principle 3 — Non‑Inference**  
The C generator MUST NOT:

- add missing logic  
- reorder logic  
- optimize logic  
- infer intent  

The C output is a **literal transcription** of the IR.

---

# **4.4.2 C Output Skeleton**

All generated C code follows this canonical structure:

```c
int cyborg_payload(<TARGET_TYPE>* ctx) {
    <BODY>
}
```

Where:

- `<TARGET_TYPE>` is determined by the target  
- `<BODY>` is a linear sequence of verb calls  
- return value is the OR‑aggregation of all verb results  

---

# **4.4.3 Target → C Parameter Mapping**

| IR Target | C Parameter Type |
|-----------|------------------|
| `AI` | `CyborgContext* ctx` |
| `FILE` | `CyborgFile* file` |
| `LAYER` | `CyborgLayer* layer` |

### **Example**
```cyborg
TARGET = AI
```

→

```c
CyborgContext* ctx
```

---

# **4.4.4 OPEN_PAYLOAD → C Function Body Start**

### **IR**
```cyborg
OPEN_PAYLOAD
```

### **C Output**
```c
{
```

This begins the function body.

---

# **4.4.5 EXEC_* Opcodes → C Function Calls**

Each execution opcode maps to a **single C function call**.

| IR Opcode | C Function |
|-----------|------------|
| `EXEC_VALIDATE` | `validate_context(ctx)` |
| `EXEC_SCAN` | `scan_context(ctx)` |
| `EXEC_BUILD` | `build_context(ctx)` |
| `EXEC_GIVE` | `give_context(ctx)` |
| `EXEC_EXPLAIN` | `explain_context(ctx)` |

### **Mapping Rule**
Each call MUST:

- be assigned to a temporary variable  
- be OR‑aggregated into the return value  
- preserve order  

### **Example**
```cyborg
EXEC_SCAN
EXEC_VALIDATE
```

→

```c
int r1 = scan_context(ctx);
int r2 = validate_context(ctx);
return (r1 || r2);
```

---

# **4.4.6 SEAL → C Function Body Close**

### **IR**
```cyborg
SEAL
```

### **C Output**
```c
}
```

This closes the function body.

---

# **4.4.7 END_TRANSMISSION → No C Output**

The termination opcode is **semantic**, not syntactic.

### **IR**
```cyborg
END_TRANSMISSION
```

### **C Output**
*(no output)*

It exists only for validation.

---

# **4.4.8 Full Mapping Example**

### **VB‑Style**
```vb
set to you
begin
scan
validate
give
#!#
end
```

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
EXEC_GIVE
SEAL
END_TRANSMISSION
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = scan_context(ctx);
    int r2 = validate_context(ctx);
    int r3 = give_context(ctx);
    return (r1 || r2 || r3);
}
```

This is the **canonical, deterministic mapping**.

---

# **4.4.9 Forbidden C Transformations**

The C generator MUST NOT:

### ❌ Reorder calls  
### ❌ Inline calls  
### ❌ Remove calls  
### ❌ Add calls  
### ❌ Combine calls  
### ❌ Parallelize calls  
### ❌ Add conditions  
### ❌ Add loops  
### ❌ Add error handling  
### ❌ Add comments  
### ❌ Add optimizations  

The C output MUST be a **pure transcription** of the IR.

---

# **4.4.10 Summary**

Page 4.4 defines the **deep mapping rules** from IR to C:

- strict 1:1 opcode mapping  
- deterministic function signatures  
- linear execution  
- OR‑aggregated return value  
- no inference  
- no optimization  
- no deviation  

The IR becomes C with **absolute fidelity**.

