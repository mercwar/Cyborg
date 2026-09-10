# **📘 PAGE 3.8 — MARKER RULES (ADVANCED)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **3.8 Overview**

This section expands the marker system into its **advanced, formalized rule set**.  
Markers are the **structural law** of the Cyborg Language.  
They define:

- where execution begins  
- where execution ends  
- what is real  
- what is ignored  
- what is allowed  
- what is forbidden  

Markers are **non‑optional**, **non‑inferential**, and **non‑negotiable**.

This section is **normative**.

---

# **3.8.1 The Three Structural Markers (Reaffirmed)**

| Marker | Purpose | Required |
|--------|---------|----------|
| `begin` / `#BGIN` | Open payload | **MUST** |
| `#!#` | Seal payload | **MUST** |
| `end` | Terminate transmission | **SHOULD** |

These markers define the **execution chamber**.

---

# **3.8.2 Marker Law: The Four Absolutes**

The Cyborg Language enforces four absolute rules regarding markers:

### **Absolute 1 — Markers Define Reality**
Only content between `begin` and `#!#` exists.

### **Absolute 2 — Markers Must Not Be Inferred**
AI systems MUST NOT guess missing markers.

### **Absolute 3 — Markers Must Not Be Nested**
Payloads cannot contain payloads.

### **Absolute 4 — Markers Must Not Be Repeated**
Each marker appears exactly once per module.

These rules ensure **deterministic execution**.

---

# **3.8.3 Marker Boundary Model**

The Cyborg Language uses a **hard boundary model**:

```
OUTSIDE → NON-EXECUTABLE
INSIDE  → EXECUTABLE
SEALED  → UNTOUCHABLE
```

### **Outside Payload**
- declarations allowed  
- comments allowed  
- no verbs allowed  

### **Inside Payload**
- verbs allowed  
- comments allowed (non‑breaking)  
- no declarations allowed  

### **After Seal**
- nothing allowed  
- everything ignored  

---

# **3.8.4 Marker Integrity Rules**

### **Rule 1 — The Payload Must Begin Cleanly**
No content may precede `begin` except declarations and comments.

### **Rule 2 — The Payload Must End Cleanly**
No content may follow `#!#` except `end` and comments.

### **Rule 3 — Markers Must Be Alone on Their Line**
Valid:
```vb
begin
```

Invalid:
```vb
begin validate   ' ❌ forbidden
```

### **Rule 4 — Markers Must Not Be Fragmented**
Forbidden:
```vb
# B G I N   ' ❌ whitespace splitting
```

### **Rule 5 — Markers Must Not Be Decorated**
Forbidden:
```vb
***begin***   ' ❌ invalid
```

Markers must appear **exactly** as defined.

---

# **3.8.5 Marker Precedence**

Markers override:

- whitespace  
- comments  
- metadata  
- formatting  
- indentation  

Markers do **not** override:

- targeting rules  
- verb ordering rules  
- sealing rules  

Markers define **structure**, not **behavior**.

---

# **3.8.6 Marker Error Conditions**

The following MUST cause immediate rejection:

### ❌ Missing `begin`
### ❌ Missing `#!#`
### ❌ Multiple `begin` markers
### ❌ Multiple `#!#` markers
### ❌ Nested payloads
### ❌ Trailing content after seal
### ❌ Declarations inside payload
### ❌ Comments between marker fragments
### ❌ Marker typos or variants
### ❌ Marker decoration or whitespace fragmentation

These errors are **fatal**.

---

# **3.8.7 Advanced Marker Examples**

### **Valid**
```vb
set to you
begin
scan
validate
#!#
end
```

### **Valid (with comments)**
```vb
set to file
' scanning file
begin
scan      ' pass 1
validate  ' pass 2
#!#
end
```

### **Invalid — Trailing Content**
```vb
begin
validate
#!#
extra   ' ❌ forbidden
```

### **Invalid — Nested Payload**
```vb
begin
begin   ' ❌ forbidden
validate
#!#
#!#
```

### **Invalid — Marker Fragmentation**
```vb
# B G I N   ' ❌ forbidden
```

---

# **3.8.8 Marker → IR Mapping**

### **VB‑Style**
```vb
begin
validate
#!#
```

### **IR**
```cyborg
OPEN_PAYLOAD
EXEC_VALIDATE
SEAL
```

Markers define the **execution envelope**.

---

# **3.8.9 Marker → C Mapping**

Markers do not appear in C output.  
They define **structure**, not **syntax**.

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    return validate_context(ctx);
}
```

---

# **3.8.10 Summary**

Page 3.8 defines the **advanced marker rules**:

- markers define reality  
- markers must not be inferred  
- markers must not be nested  
- markers must not be repeated  
- markers must be exact  
- markers enforce deterministic execution  
- markers override formatting but not logic  

Markers are the **ceremonial skeleton** of the Cyborg Language.

