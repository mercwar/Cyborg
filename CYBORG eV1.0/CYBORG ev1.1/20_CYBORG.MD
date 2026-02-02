# **📘 PAGE 4.1 — IR OPCODES (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.1 Overview**

This section defines the **formal, canonical, and complete specification** of all Cyborg IR opcodes.  
These opcodes are the **only valid internal instructions** the Cyborg Language may generate.  
They are:

- atomic  
- deterministic  
- non‑overloaded  
- non‑inferential  
- strictly ordered  
- directly mapped to C  

This section is **normative**.

---

# **4.1.1 IR Opcode Categories**

IR opcodes fall into five categories:

1. **Target Binding Opcodes**  
2. **Structural Opcodes**  
3. **Execution Opcodes**  
4. **Sealing Opcodes**  
5. **Termination Opcodes**

Each category is defined below.

---

# **4.1.2 Target Binding Opcodes**

### **Opcode**
```cyborg
TARGET = <context>
```

### **Valid Contexts**
```
AI
FILE
LAYER
```

### **Source**
```vb
set to you
set to file
set to layer
```

### **Normative Rules**

- MUST appear exactly once.  
- MUST be the first opcode.  
- MUST map to a C parameter.  
- MUST NOT be inferred.  

---

# **4.1.3 Structural Opcodes**

### **Payload Opening**
```cyborg
OPEN_PAYLOAD
```

### **Source**
```vb
begin
```
or
```vb
#BGIN
```

### **Normative Rules**

- MUST appear exactly once.  
- MUST appear after TARGET.  
- MUST NOT be nested.  
- MUST NOT be repeated.  

---

# **4.1.4 Execution Opcodes**

These opcodes correspond directly to the five canonical verbs.

| VB Verb | IR Opcode | Meaning |
|---------|-----------|---------|
| `validate` | `EXEC_VALIDATE` | Perform validation |
| `scan` | `EXEC_SCAN` | Perform scanning |
| `build` | `EXEC_BUILD` | Perform construction |
| `give` | `EXEC_GIVE` | Emit or return information |
| `explain` | `EXEC_EXPLAIN` | Produce diagnostic output |

### **Normative Rules**

- MUST appear only inside an open payload.  
- MUST appear in the order written.  
- MUST NOT be inferred.  
- MUST NOT be reordered.  
- MUST NOT be combined.  
- MUST NOT accept arguments.  

---

# **4.1.5 Sealing Opcode**

### **Opcode**
```cyborg
SEAL
```

### **Source**
```vb
#!#
```

### **Normative Rules**

- MUST appear exactly once.  
- MUST close the payload.  
- MUST NOT be followed by executable content.  
- MUST trigger C syntax completion.  

---

# **4.1.6 Termination Opcode**

### **Opcode**
```cyborg
END_TRANSMISSION
```

### **Source**
```vb
end
```

### **Normative Rules**

- SHOULD appear after SEAL.  
- MUST NOT appear inside payload.  
- MAY be omitted if environment auto‑terminates.  

---

# **4.1.7 Full Opcode Table (Normative)**

| Opcode | Category | Source | Required |
|--------|----------|---------|----------|
| `TARGET = <context>` | Target Binding | `set to <target>` | **MUST** |
| `OPEN_PAYLOAD` | Structural | `begin` / `#BGIN` | **MUST** |
| `EXEC_VALIDATE` | Execution | `validate` | Optional |
| `EXEC_SCAN` | Execution | `scan` | Optional |
| `EXEC_BUILD` | Execution | `build` | Optional |
| `EXEC_GIVE` | Execution | `give` | Optional |
| `EXEC_EXPLAIN` | Execution | `explain` | Optional |
| `SEAL` | Sealing | `#!#` | **MUST** |
| `END_TRANSMISSION` | Termination | `end` | **SHOULD** |

---

# **4.1.8 IR Opcode Ordering Rules**

The IR MUST follow this exact order:

```
TARGET
OPEN_PAYLOAD
EXEC_* (0 or more)
SEAL
END_TRANSMISSION (optional)
```

### **Forbidden Orders**

- EXEC_* before OPEN_PAYLOAD  
- TARGET after OPEN_PAYLOAD  
- SEAL before EXEC_*  
- END_TRANSMISSION inside payload  
- Multiple TARGET opcodes  
- Multiple SEAL opcodes  

All MUST be rejected.

---

# **4.1.9 IR Example (Full)**

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

---

# **4.1.10 Summary**

Page 4.1 defines the **formal IR opcode specification**:

- nine total opcodes  
- five execution opcodes  
- strict ordering  
- no inference  
- no variation  
- deterministic mapping to C  

The IR is the **canonical internal truth** of the Cyborg Language.

