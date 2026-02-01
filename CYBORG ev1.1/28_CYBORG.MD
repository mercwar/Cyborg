

# **📘 PAGE 4.8 — IR ERROR DIAGNOSTICS (MACHINE‑LEVEL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **4.8 Overview**

This section defines the **machine‑level diagnostic system** used when IR validation fails.  
Diagnostics are:

- strict  
- non‑interpretive  
- non‑negotiable  
- immediate  
- fatal  

The diagnostic engine MUST NOT attempt:

- correction  
- inference  
- recovery  
- fallback behavior  

It MUST only **detect**, **classify**, and **report**.

This section is **normative**.

---

# **4.8.1 Diagnostic Philosophy**

Diagnostics follow three principles:

### **Principle 1 — Precision**  
Errors MUST be reported with exact category and location.

### **Principle 2 — Finality**  
Errors MUST halt execution immediately.

### **Principle 3 — Non‑Inference**  
Diagnostics MUST NOT guess what the user “meant.”

---

# **4.8.2 Diagnostic Categories**

Every IR error MUST fall into one of the following categories:

1. **TARGET_ERROR**  
2. **STRUCTURE_ERROR**  
3. **MARKER_ERROR**  
4. **EXECUTION_ERROR**  
5. **ORDER_ERROR**  
6. **BOUNDARY_ERROR**  
7. **OPCODE_ERROR**

Each category is defined below.

---

# **4.8.3 TARGET_ERROR**

Triggered when:

- no target is present  
- multiple targets exist  
- target appears after payload open  
- target appears inside payload  

### **Diagnostic Format**
```
ERROR: TARGET_ERROR — <description>
Line <n>: "<content>"
Execution halted.
```

---

# **4.8.4 STRUCTURE_ERROR**

Triggered when:

- declarations appear inside payload  
- comments break markers  
- whitespace fragments keywords  
- unknown constructs appear  

### **Diagnostic Format**
```
ERROR: STRUCTURE_ERROR — <description>
Line <n>: "<content>"
Execution halted.
```

---

# **4.8.5 MARKER_ERROR**

Triggered when:

- missing begin  
- missing seal  
- nested payloads  
- multiple opens  
- multiple seals  
- trailing content after seal  
- marker fragmentation  
- marker decoration  

### **Diagnostic Format**
```
ERROR: MARKER_ERROR — <description>
Line <n>: "<content>"
Execution halted.
```

---

# **4.8.6 EXECUTION_ERROR**

Triggered when:

- verb appears outside payload  
- verb appears after seal  
- verb contains arguments  
- verb is unknown  
- verb is combined with another verb  

### **Diagnostic Format**
```
ERROR: EXECUTION_ERROR — <description>
Line <n>: "<content>"
Execution halted.
```

---

# **4.8.7 ORDER_ERROR**

Triggered when:

- EXEC_* appears before OPEN_PAYLOAD  
- SEAL appears before EXEC_*  
- TARGET appears after OPEN_PAYLOAD  
- END_TRANSMISSION appears inside payload  

### **Diagnostic Format**
```
ERROR: ORDER_ERROR — <description>
Line <n>: "<content>"
Execution halted.
```

---

# **4.8.8 BOUNDARY_ERROR**

Triggered when:

- payload boundaries overlap  
- payload boundaries are nested  
- payload boundaries are missing  
- content appears after seal  

### **Diagnostic Format**
```
ERROR: BOUNDARY_ERROR — <description>
Line <n>: "<content>"
Execution halted.
```

---

# **4.8.9 OPCODE_ERROR**

Triggered when:

- IR contains unknown opcodes  
- IR contains malformed opcodes  
- IR contains illegal opcode sequences  

### **Diagnostic Format**
```
ERROR: OPCODE_ERROR — <description>
Opcode: <opcode>
Execution halted.
```

---

# **4.8.10 Diagnostic Severity**

All IR errors are **fatal**.

There are:

- no warnings  
- no recoverable states  
- no partial validity  
- no fallback modes  

If IR is invalid, **C generation MUST NOT occur**.

---

# **4.8.11 Diagnostic Examples**

### **Example 1 — Trailing Content**
```
ERROR: MARKER_ERROR — trailing content after seal.
Line 7: "extra"
Execution halted.
```

### **Example 2 — Unknown Verb**
```
ERROR: EXECUTION_ERROR — unknown verb "optimize".
Line 4: "optimize"
Execution halted.
```

### **Example 3 — Missing Target**
```
ERROR: TARGET_ERROR — no target declared.
Execution halted.
```

### **Example 4 — Nested Payload**
```
ERROR: BOUNDARY_ERROR — nested payload detected.
Line 5: "begin"
Execution halted.
```

---

# **4.8.12 Summary**

Page 4.8 defines the **machine‑level diagnostic system**:

- strict error categories  
- precise reporting  
- immediate halting  
- no inference  
- no correction  
- no recovery  

Diagnostics enforce the **ceremonial purity** of the Cyborg Language.

