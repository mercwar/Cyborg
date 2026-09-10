# **📘 PAGE 3.7 — COMMENTS AND WHITESPACE RULES**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.7 Overview**

Comments and whitespace exist in the Cyborg Language **only for human readability**.  
They:

- MUST NOT affect execution  
- MUST NOT affect IR  
- MUST NOT affect C output  
- MUST NOT alter verb order  
- MUST NOT break markers  

Whitespace and comments are **non‑semantic**.  
They are allowed, but only within strict boundaries.

This section is **normative**.

---

# **3.7.1 Comment Syntax**

The Cyborg Language uses **VB‑style single‑line comments**:

```vb
' This is a comment
```

### **Normative Rules**

- Comments MAY appear before the payload.  
- Comments MAY appear inside the payload **only if they do not break structure**.  
- Comments MUST NOT appear between marker fragments.  
- Comments MUST NOT appear after the seal (`#!#`).  
- Comments MUST NOT alter execution.  
- Comments MUST NOT imply grouping or ordering.  

---

# **3.7.2 Valid Comment Placement**

### **Before Payload**
```vb
' This module validates the context
set to you
begin
validate
#!#
```

### **Inside Payload (Allowed)**
```vb
begin
scan      ' first pass
validate  ' second pass
#!#
```

### **After Transmission (Allowed)**
```vb
#!#
end
' done
```

---

# **3.7.3 Invalid Comment Placement**

### ❌ Between Marker Fragments
```vb
begin
' illegal
#!#
```

### ❌ After Seal
```vb
begin
validate
#!#
' forbidden
```

### ❌ Inside Payload in a Way That Breaks Structure
```vb
begin
' comment that implies grouping ❌
scan
validate
#!#
```

### ❌ Comments That Alter Meaning
```vb
begin
scan ' then validate and build ❌
validate
#!#
```

Comments MUST NOT imply additional verbs.

---

# **3.7.4 Whitespace Rules**

Whitespace is allowed but **non‑semantic**.

### **Allowed**
- blank lines  
- indentation  
- spacing around verbs  
- spacing around markers  

### **Forbidden**
- whitespace that changes meaning  
- whitespace that splits keywords  
- whitespace that creates ambiguity  

### **Valid**
```vb
begin

scan

validate

#!#
```

### **Invalid**
```vb
v a l i d a t e   ' ❌ forbidden
```

Whitespace MUST NOT fragment keywords.

---

# **3.7.5 Whitespace Normalization**

The Cyborg engine MUST:

- ignore blank lines  
- ignore indentation  
- ignore trailing spaces  
- normalize whitespace before IR generation  

The engine MUST NOT:

- infer meaning from whitespace  
- treat whitespace as grouping  
- treat whitespace as ordering  

---

# **3.7.6 Comments and Whitespace → IR Mapping**

### **VB‑Style**
```vb
set to you
' comment
begin

scan      ' pass 1

validate  ' pass 2

#!#
```

### **Cyborg IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
SEAL
```

Comments and whitespace do not appear in IR.

---

# **3.7.7 Comments and Whitespace → C Mapping**

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = scan_context(ctx);
    int r2 = validate_context(ctx);
    return (r1 || r2);
}
```

No comments or whitespace from the VB‑style input appear in the C output.

---

# **3.7.8 Forbidden Patterns Summary**

The following MUST be rejected:

### ❌ Comments after seal  
### ❌ Comments between marker fragments  
### ❌ Comments implying additional verbs  
### ❌ Comments altering order  
### ❌ Whitespace splitting keywords  
### ❌ Whitespace implying grouping  
### ❌ Whitespace implying structure  

All violate deterministic execution.

---

# **3.7.9 Summary**

Page 3.7 defines the **comment and whitespace rules** of the Cyborg Language:

- comments are allowed but non‑semantic  
- whitespace is allowed but non‑semantic  
- comments must not break markers  
- comments must not imply structure  
- whitespace must not fragment keywords  
- neither comments nor whitespace affect IR or C output  

Comments and whitespace exist **only for human readability**, never for execution.

