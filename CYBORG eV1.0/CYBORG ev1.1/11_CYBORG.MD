# **📘 PAGE 2.5 — ROLE OF MARKERS (`#BGIN`, `#!#`, `end`)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **2.5 Overview**

Markers are the **structural backbone** of the Cyborg Language.  
They define:

- where execution begins  
- where execution ends  
- what content is real  
- what content is ignored  
- when C syntax completion is triggered  

Markers are **not optional**, **not decorative**, and **not flexible**.  
They are **law**.

This section is **normative**.

---

# **2.5.1 The Three Canonical Markers**

The Cyborg Language uses exactly **three** structural markers:

| Marker | Meaning | Required? |
|--------|---------|-----------|
| `#BGIN` / `begin` | Start of payload | **MUST** |
| `#!#` | Seal payload | **MUST** |
| `end` | Close transmission | **SHOULD** |

These markers define the **execution boundaries** of the language.

---

# **2.5.2 Marker 1 — `#BGIN` (or `begin`)**

### **Purpose**  
Open a payload block.

### **Syntax Options**
```vb
begin
```
or
```vb
#BGIN
```

### **Normative Rules**

- A payload **MUST** begin with `begin` or `#BGIN`.  
- Only one payload may be open at a time.  
- Nested payloads are forbidden.  
- No verbs may appear before the payload opens.  

### **IR Representation**
```cyborg
OPEN_PAYLOAD
```

### **C Effect**  
Begins the function body.

---

# **2.5.3 Marker 2 — `#!#` (Seal Marker)**

### **Purpose**  
Seal the payload and finalize the command set.

### **Syntax**
```vb
#!#
```

### **Normative Rules**

- A payload **MUST** be sealed.  
- Unsealed payloads **MUST NOT** be executed.  
- No content after `#!#` may be processed.  
- Sealing triggers C syntax completion.  

### **IR Representation**
```cyborg
SEAL
```

### **C Effect**  
Closes the function body and finalizes the translation unit.

---

# **2.5.4 Marker 3 — `end` (Transmission Terminator)**

### **Purpose**  
Indicate the end of the entire transmission.

### **Syntax**
```vb
end
```

### **Normative Rules**

- `end` **SHOULD** appear after the sealed payload.  
- `end` **MUST NOT** appear inside a payload.  
- `end` **MAY** be omitted if the environment auto‑terminates.  

### **IR Representation**
```cyborg
END_TRANSMISSION
```

### **C Effect**  
No direct effect — used for validation only.

---

# **2.5.5 Marker Interaction Rules**

### **Rule 1 — Markers MUST appear in order**
```
begin → verbs → #!# → end
```

### **Rule 2 — Markers MUST NOT overlap**
Invalid:
```vb
begin
#!#
#!#
```

### **Rule 3 — Markers MUST NOT be nested**
Invalid:
```vb
begin
begin
validate
#!#
#!#
```

### **Rule 4 — Markers define reality**
Anything outside the markers is ignored.

### **Rule 5 — Markers MUST NOT be inferred**
AI systems MUST NOT assume missing markers.

---

# **2.5.6 Valid Marker Example**

### **VB‑Style Cyborg**
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

# **2.5.7 Invalid Marker Examples**

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

### ❌ Nested Payloads
```vb
begin
begin
validate
#!#
#!#
```

### ❌ Seal Without Open
```vb
#!#
```

All MUST be rejected.

---

# **2.5.8 Summary**

Page 2.5 defines the **role of markers** in the Cyborg Language:

- `begin` / `#BGIN` opens reality  
- `#!#` seals reality  
- `end` terminates transmission  
- markers MUST appear in order  
- markers MUST NOT be nested  
- markers define the boundaries of truth  

Markers are the **ceremonial and structural law** of the language.

