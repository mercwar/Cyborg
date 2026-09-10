# **📘 PAGE 3.4 — PAYLOAD BLOCKS**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.4 Overview**

A **payload block** is the *active execution chamber* of the Cyborg Language.  
It is where:

- verbs execute  
- order is enforced  
- IR is generated  
- C output is constructed  
- boundaries are honored  

The payload is the **heart** of a Cyborg Module.  
Everything outside it is context; everything inside it is execution.

This section is **normative**.

---

# **3.4.1 What a Payload Block Is**

A payload block is the region of code between:

```
begin / #BGIN
    ...
#!#
```

It contains **only verbs**, in strict order, with optional comments that do not break structure.

### **Canonical Form**
```vb
begin
<verbs>
#!#
```

---

# **3.4.2 What a Payload Block Is NOT**

A payload block is **not**:

- a general-purpose code block  
- a place for declarations  
- a place for metadata  
- a place for nested structures  
- a place for inference  
- a place for optional syntax  

It is a **sealed execution chamber**.

---

# **3.4.3 Payload Opening**

### **Syntax Options**
```vb
begin
```
or
```vb
#BGIN
```

### **Normative Rules**

- MUST appear after the target declaration.  
- MUST appear before any verbs.  
- MUST NOT be nested.  
- MUST NOT appear more than once.  

### **IR**
```cyborg
OPEN_PAYLOAD
```

---

# **3.4.4 Payload Body**

The payload body contains **only verbs**, in the order written.

### **Allowed Verbs**
```
validate
scan
build
give
explain
```

### **Normative Rules**

- Verbs MUST appear inside an open payload.  
- Verbs MUST NOT appear before `begin`.  
- Verbs MUST NOT appear after `#!#`.  
- Verbs MUST NOT be inferred.  
- Verbs MUST NOT be reordered.  
- Verbs MUST map to C functions.  

### **Example**
```vb
begin
scan
validate
#!#
```

---

# **3.4.5 Payload Sealing**

### **Syntax**
```vb
#!#
```

### **Normative Rules**

- MUST appear exactly once.  
- MUST close the payload.  
- MUST NOT be followed by executable content.  
- MUST trigger C syntax completion.  

### **IR**
```cyborg
SEAL
```

---

# **3.4.6 Payload Execution Order**

Execution order is **strict** and MUST NOT be altered.

### **VB‑Style**
```vb
begin
scan
validate
#!#
```

### **IR**
```cyborg
EXEC_SCAN
EXEC_VALIDATE
```

### **C Output**
```c
scan_context(ctx);
validate_context(ctx);
```

Order is preserved exactly.

---

# **3.4.7 Comments Inside Payloads**

Comments MAY appear inside payloads **only if they do not break structure**.

### **Valid**
```vb
begin
scan      ' first pass
validate  ' second pass
#!#
```

### **Invalid**
```vb
begin
' comment between marker fragments ❌
#!#
```

Comments MUST NOT:

- appear between marker fragments  
- appear after the seal  
- alter execution  

---

# **3.4.8 Forbidden Payload Patterns**

### ❌ Nested Payloads
```vb
begin
begin
validate
#!#
#!#
```

### ❌ Missing Seal
```vb
begin
validate
```

### ❌ Trailing Content
```vb
begin
validate
#!#
extra
```

### ❌ Declarations Inside Payload
```vb
begin
meta "illegal"
validate
#!#
```

### ❌ Multiple Seals
```vb
begin
validate
#!#
#!#
```

All MUST be rejected.

---

# **3.4.9 Full Valid Payload Example**

### **VB‑Style Cyborg**
```vb
set to you
begin
scan
validate
build
#!#
end
```

### **Cyborg IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
EXEC_BUILD
SEAL
END_TRANSMISSION
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = scan_context(ctx);
    int r2 = validate_context(ctx);
    int r3 = build_context(ctx);
    return (r1 || r2 || r3);
}
```

---

# **3.4.10 Summary**

Page 3.4 defines the **payload block**, the core execution chamber of the Cyborg Language:

- payloads are marker‑bound  
- payloads contain only verbs  
- payloads must be sealed  
- payloads must not be nested  
- payloads must not contain declarations  
- payloads produce deterministic IR and C output  

The payload is where **ceremony becomes execution**.

