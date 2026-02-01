

# **📘 PAGE 4.2 — IR GENERATION RULES (DEEP SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.2 Overview**

This section defines the **deep, formal, machine‑level rules** governing how VB‑style Cyborg syntax is transformed into Cyborg IR.  
These rules ensure:

- deterministic translation  
- zero inference  
- strict structural integrity  
- absolute ordering  
- reproducible C output  

IR generation is **mechanical**, **non‑interpretive**, and **non‑negotiable**.

This section is **normative**.

---

# **4.2.1 The IR Generation Pipeline**

IR generation proceeds through **five mandatory phases**:

```
[1] Pre‑Scan (Structural Validation)
[2] Target Binding
[3] Payload Boundary Resolution
[4] Verb Linearization
[5] IR Assembly
```

Each phase MUST complete successfully before the next begins.

---

# **4.2.2 Phase 1 — Pre‑Scan (Structural Validation)**

Before any IR is generated, the engine MUST validate:

- exactly one target exists  
- exactly one payload opening exists  
- exactly one seal exists  
- markers appear in correct order  
- no nested payloads exist  
- no trailing content exists  
- no unknown verbs exist  
- no declarations appear inside payload  

If any violation is detected, IR generation MUST halt.

### **Output of Phase 1**
```
STRUCTURE_OK
```

If not OK → **fatal error**.

---

# **4.2.3 Phase 2 — Target Binding**

The engine extracts the target declaration:

```vb
set to you
```

and converts it to:

```cyborg
TARGET = AI
```

### **Rules**

- MUST occur before payload opening  
- MUST occur exactly once  
- MUST map to a valid context  
- MUST be the first IR opcode  

If missing → **fatal error**.

---

# **4.2.4 Phase 3 — Payload Boundary Resolution**

The engine identifies:

- the line containing `begin` or `#BGIN`  
- the line containing `#!#`  

These define the **execution envelope**.

### **Rules**

- boundaries MUST NOT overlap  
- boundaries MUST NOT be nested  
- boundaries MUST NOT be fragmented  
- boundaries MUST NOT be decorated  

If invalid → **fatal error**.

### **IR Output**
```cyborg
OPEN_PAYLOAD
```

---

# **4.2.5 Phase 4 — Verb Linearization**

Inside the payload, the engine extracts **only verbs**, in the order written.

### **Valid Verbs**
```
validate
scan
build
give
explain
```

### **Rules**

- MUST appear only inside payload  
- MUST appear one per line  
- MUST NOT contain arguments  
- MUST NOT be combined  
- MUST NOT be inferred  
- MUST NOT be reordered  

### **Linearization Example**

#### **VB‑Style**
```vb
begin
scan
validate
build
#!#
```

#### **Linearized Verb List**
```
[ scan, validate, build ]
```

#### **IR Opcodes**
```cyborg
EXEC_SCAN
EXEC_VALIDATE
EXEC_BUILD
```

---

# **4.2.6 Phase 5 — IR Assembly**

The engine assembles the final IR sequence:

```
TARGET
OPEN_PAYLOAD
EXEC_*
SEAL
END_TRANSMISSION (optional)
```

### **Example**

#### **VB‑Style**
```vb
set to file
begin
scan
validate
#!#
end
```

#### **IR**
```cyborg
TARGET = FILE
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
SEAL
END_TRANSMISSION
```

This IR MUST be complete, linear, and deterministic.

---

# **4.2.7 IR Generation Failure Conditions**

IR generation MUST halt if any of the following occur:

### **Target Errors**
- missing target  
- multiple targets  
- target inside payload  

### **Marker Errors**
- missing begin  
- missing seal  
- nested payloads  
- trailing content  

### **Verb Errors**
- unknown verb  
- verb outside payload  
- verb after seal  
- verb with arguments  
- grouped verbs  

### **Structural Errors**
- metadata inside payload  
- comments breaking markers  
- whitespace splitting keywords  

Any violation → **fatal error**.

---

# **4.2.8 IR Determinism Rules**

The IR MUST be:

- **order‑preserving**  
- **structure‑preserving**  
- **non‑inferential**  
- **non‑optimizing**  
- **non‑branching**  
- **non‑parallel**  

The IR MUST NOT:

- reorder verbs  
- collapse verbs  
- infer missing verbs  
- infer missing markers  
- generate additional opcodes  

The IR is a **pure transcription**, not a compiler.

---

# **4.2.9 IR Canonical Example (Full)**

### **VB‑Style**
```vb
set to layer
meta "desc: test"
begin
scan
validate
give
#!#
end
```

### **IR**
```cyborg
TARGET = LAYER
META("desc: test")
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
EXEC_GIVE
SEAL
END_TRANSMISSION
```

This is the **canonical IR form**.

---

# **4.2.10 Summary**

Page 4.2 defines the **deep IR generation rules**:

- 5‑phase pipeline  
- strict structural validation  
- deterministic target binding  
- strict payload boundary resolution  
- linear verb extraction  
- deterministic IR assembly  
- zero inference  
- zero optimization  
- zero ambiguity  

The IR is the **machine‑truth representation** of the Cyborg Language.

