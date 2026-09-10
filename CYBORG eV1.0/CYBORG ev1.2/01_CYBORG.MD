

# **📘 PAGE 4.9 — IR CANONICAL EXAMPLES (MASTER SET)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.9 Overview**

This section provides the **complete, authoritative library** of canonical IR examples.  
These examples demonstrate:

- valid structures  
- invalid structures  
- boundary conditions  
- multi‑verb payloads  
- minimal payloads  
- metadata interactions  
- comment interactions  
- target variations  

This section is **normative** and serves as the **reference corpus** for all IR implementations.

---

# **4.9.1 Canonical Example — Minimal Valid Module**

### **VB‑Style**
```vb
set to you
begin
validate
#!#
end
```

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
SEAL
END_TRANSMISSION
```

---

# **4.9.2 Canonical Example — Multi‑Verb Module**

### **VB‑Style**
```vb
set to file
begin
scan
validate
build
give
#!#
end
```

### **IR**
```cyborg
TARGET = FILE
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
EXEC_BUILD
EXEC_GIVE
SEAL
END_TRANSMISSION
```

---

# **4.9.3 Canonical Example — With Metadata**

### **VB‑Style**
```vb
set to layer
meta "description: test module"
begin
scan
#!#
end
```

### **IR**
```cyborg
TARGET = LAYER
META("description: test module")
OPEN_PAYLOAD
EXEC_SCAN
SEAL
END_TRANSMISSION
```

Metadata is preserved but non‑executable.

---

# **4.9.4 Canonical Example — With Comments**

### **VB‑Style**
```vb
' layer scan test
set to layer
begin
scan      ' first pass
validate  ' second pass
#!#
end
```

### **IR**
```cyborg
TARGET = LAYER
OPEN_PAYLOAD
EXEC_SCAN
EXEC_VALIDATE
SEAL
END_TRANSMISSION
```

Comments do not appear in IR.

---

# **4.9.5 Canonical Example — Zero‑Verb Payload**

### **VB‑Style**
```vb
set to you
begin
#!#
end
```

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
SEAL
END_TRANSMISSION
```

Zero‑verb payloads are valid.

---

# **4.9.6 Canonical Example — Maximal Verb Payload**

### **VB‑Style**
```vb
set to you
begin
validate
scan
build
give
explain
#!#
end
```

### **IR**
```cyborg
TARGET = AI
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_GIVE
EXEC_EXPLAIN
SEAL
END_TRANSMISSION
```

All five verbs in order.

---

# **4.9.7 Invalid Example — Missing Target**

### **VB‑Style**
```vb
begin
validate
#!#
```

### **IR Status**
```
INVALID — TARGET_ERROR: missing target.
```

---

# **4.9.8 Invalid Example — Missing Seal**

### **VB‑Style**
```vb
set to you
begin
validate
```

### **IR Status**
```
INVALID — MARKER_ERROR: missing seal.
```

---

# **4.9.9 Invalid Example — Nested Payload**

### **VB‑Style**
```vb
set to file
begin
begin
scan
#!#
#!#
```

### **IR Status**
```
INVALID — BOUNDARY_ERROR: nested payload.
```

---

# **4.9.10 Invalid Example — Unknown Verb**

### **VB‑Style**
```vb
set to you
begin
optimize
#!#
```

### **IR Status**
```
INVALID — EXECUTION_ERROR: unknown verb "optimize".
```

---

# **4.9.11 Invalid Example — Trailing Content**

### **VB‑Style**
```vb
set to you
begin
validate
#!#
extra
```

### **IR Status**
```
INVALID — MARKER_ERROR: trailing content after seal.
```

---

# **4.9.12 Invalid Example — Verb Outside Payload**

### **VB‑Style**
```vb
validate
set to you
begin
scan
#!#
```

### **IR Status**
```
INVALID — EXECUTION_ERROR: verb outside payload.
```

---

# **4.9.13 Invalid Example — Verb With Arguments**

### **VB‑Style**
```vb
set to you
begin
validate deep
#!#
```

### **IR Status**
```
INVALID — EXECUTION_ERROR: verb contains arguments.
```

---

# **4.9.14 Invalid Example — Grouped Verbs**

### **VB‑Style**
```vb
set to you
begin
scan validate
#!#
```

### **IR Status**
```
INVALID — EXECUTION_ERROR: grouped verbs.
```

---

# **4.9.15 Invalid Example — Marker Fragmentation**

### **VB‑Style**
```vb
set to you
# B G I N
validate
#!#
```

### **IR Status**
```
INVALID — MARKER_ERROR: fragmented marker.
```

---

# **4.9.16 Summary**

Page 4.9 provides the **master canonical example set**:

- minimal modules  
- maximal modules  
- metadata modules  
- comment modules  
- zero‑verb modules  
- multi‑verb modules  
- all major invalid patterns  

This corpus defines the **reference truth** for all IR implementations.

