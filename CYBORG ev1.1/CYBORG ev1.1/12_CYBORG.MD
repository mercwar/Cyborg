# **📘 PAGE 3.1 — MODULE STRUCTURE**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.1 Overview**

A **Cyborg Module** is the fundamental unit of structure in the AVIS Cyborg Language.  
It defines:

- the **target**  
- the **payload boundaries**  
- the **execution verbs**  
- the **ordering**  
- the **conversion context**  
- the **C output container**

A module is **not** a file, class, or namespace.  
It is a **ceremonial execution block** that transforms VB‑style commands into deterministic C.

This section is **normative**.

---

# **3.1.1 Required Components of a Module**

Every Cyborg Module MUST contain the following components in order:

1. **Target Declaration**  
2. **Payload Opening Marker**  
3. **Execution Verbs**  
4. **Payload Seal Marker**  
5. **Transmission Terminator (optional but recommended)**  

### **Canonical Structure**
```vb
set to <target>
begin
<verbs>
#!#
end
```

This is the **minimum valid module**.

---

# **3.1.2 Target Declaration**

### **Purpose**  
Defines the execution context.

### **Syntax**
```vb
set to you
set to file
set to layer
```

### **Normative Rules**

- MUST appear before `begin`.  
- MUST appear exactly once.  
- MUST map to a C parameter.  

### **IR**
```cyborg
TARGET = <context>
```

---

# **3.1.3 Payload Opening**

### **Syntax Options**
```vb
begin
```
or
```vb
#BGIN
```

### **Normative Rules**

- MUST appear after the target.  
- MUST appear before any verbs.  
- MUST NOT be nested.  

### **IR**
```cyborg
OPEN_PAYLOAD
```

---

# **3.1.4 Execution Block**

The execution block contains **only verbs**, in strict order.

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
- Verbs MUST map to C functions.  

### **Example**
```vb
begin
scan
validate
#!#
```

---

# **3.1.5 Payload Seal**

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

# **3.1.6 Transmission Terminator**

### **Syntax**
```vb
end
```

### **Normative Rules**

- SHOULD appear after `#!#`.  
- MUST NOT appear inside a payload.  
- MAY be omitted if the environment auto‑terminates.  

### **IR**
```cyborg
END_TRANSMISSION
```

---

# **3.1.7 Full Module Example**

### **VB‑Style Cyborg Module**
```vb
set to you
begin
scan
validate
#!#
end
```

### **Cyborg IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
SEAL
END_TRANSMISSION
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = scan_context(ctx);
    int r2 = validate_context(ctx);
    return (r1 || r2);
}
```

---

# **3.1.8 Invalid Module Examples**

### ❌ Missing Target
```vb
begin
validate
#!#
```

### ❌ Missing Seal
```vb
set to you
begin
validate
```

### ❌ Trailing Content
```vb
set to you
begin
validate
#!#
extra
```

### ❌ Nested Payloads
```vb
set to you
begin
begin
validate
#!#
#!#
```

All MUST be rejected.

---

# **3.1.9 Summary**

Page 3.1 defines the **module structure** of the Cyborg Language:

- target → open → verbs → seal → end  
- strict ordering  
- no nesting  
- no inference  
- deterministic mapping to C  

This structure is the foundation for all syntax rules in Page 3.

