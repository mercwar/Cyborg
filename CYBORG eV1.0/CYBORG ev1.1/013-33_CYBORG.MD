# **📘 PAGE 3.2 — DECLARATIONS**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.2 Overview**

Declarations define the **static, structural, and contextual elements** of a Cyborg Module.  
They are not actions — they are **facts** the module asserts before execution begins.

Declarations include:

- target declarations  
- metadata declarations  
- comment declarations  
- optional descriptive headers  

Declarations MUST appear **before** the payload opens and MUST NOT appear inside the payload unless explicitly allowed.

This section is **normative**.

---

# **3.2.1 Target Declarations**

The **target declaration** is the most important declaration in the Cyborg Language.  
It defines *what* the verbs will operate on.

### **Syntax**
```vb
set to you
set to file
set to layer
```

### **Normative Rules**

- MUST appear exactly once.  
- MUST appear before `begin` / `#BGIN`.  
- MUST NOT appear inside the payload.  
- MUST map to a C parameter.  

### **IR Representation**
```cyborg
TARGET = <context>
```

### **C Output**
```c
CyborgContext* ctx
```

---

# **3.2.2 Metadata Declarations (Optional)**

Metadata declarations provide **non‑executable information** about the module.

### **Syntax**
```vb
meta "description: validates the context"
meta "author: user"
meta "version: 1.0"
```

### **Normative Rules**

- MAY appear before `begin`.  
- MUST NOT appear inside the payload.  
- MUST NOT affect execution.  
- MUST NOT affect C output.  

### **IR Representation**
```cyborg
META("description: validates the context")
```

Metadata is **informative**, not executable.

---

# **3.2.3 Comment Declarations**

Comments provide human‑readable notes.

### **Syntax**
```vb
' This validates the context
```

### **Normative Rules**

- MAY appear anywhere outside the payload.  
- MAY appear inside the payload **only if they do not break verb ordering**.  
- MUST NOT alter execution.  
- MUST NOT alter IR.  
- MUST NOT alter C output.  

### **Example**
```vb
set to you
' This payload validates the context
begin
validate   ' run validation
#!#
```

Comments are ignored by the engine.

---

# **3.2.4 Declaration Ordering Rules**

Declarations MUST follow this order:

```
1. Target declaration
2. Metadata declarations (optional)
3. Comments (optional)
4. Payload opening
```

### **Valid Example**
```vb
set to you
meta "description: test"
' comment
begin
validate
#!#
```

### **Invalid Example**
```vb
begin
set to you   ' ❌ target after payload open
validate
#!#
```

---

# **3.2.5 Forbidden Declaration Patterns**

### ❌ Declarations inside sealed payloads
```vb
begin
validate
meta "illegal"
#!#
```

### ❌ Multiple targets
```vb
set to you
set to file   ' ❌ forbidden
begin
validate
#!#
```

### ❌ Metadata after payload open
```vb
set to you
begin
meta "late"   ' ❌ forbidden
validate
#!#
```

### ❌ Comments that break markers
```vb
begin
' comment between #!# fragments ❌
#!#
```

---

# **3.2.6 Declaration → IR → C Mapping**

### **VB‑Style**
```vb
set to you
meta "description: validation"
begin
validate
#!#
```

### **Cyborg IR**
```cyborg
TARGET = AI
META("description: validation")
OPEN_PAYLOAD
EXEC_VALIDATE
SEAL
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    return validate_context(ctx);
}
```

Metadata is ignored by the C layer.

---

# **3.2.7 Summary**

Page 3.2 defines the **declaration system** of the Cyborg Language:

- targets are mandatory  
- metadata is optional  
- comments are optional  
- declarations MUST precede payload opening  
- declarations MUST NOT appear inside sealed payloads  
- declarations MUST NOT affect execution  
- declarations MUST NOT affect C output  

Declarations establish the **context**, not the **behavior**.

