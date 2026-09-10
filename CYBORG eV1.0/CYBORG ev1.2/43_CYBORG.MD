

# **📘 PAGE 9.5 — IR PURITY RULES (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **9.5 Overview**

The **IR Purity Rules** define what the IR is *forbidden* to do.  
Where determinism ensures the IR is *predictable*, purity ensures the IR is *clean* — free of side effects, computation, or external influence.

IR purity is absolute.  
IR is not code.  
IR is not logic.  
IR is not configuration.

> **IR is pure semantic declaration. Nothing more.**

This section is **normative**.

---

# **9.5.1 Purity Rule 1 — IR Contains No Computation**

The IR MUST NOT contain:

- arithmetic  
- logic  
- expressions  
- comparisons  
- conditions  
- loops  
- macros  

### **Meaning**  
IR is **not executable**.

---

# **9.5.2 Purity Rule 2 — IR Contains No Parameters**

The IR MUST NOT:

- pass parameters to verbs  
- configure verbs  
- modify verb behavior  
- supply arguments  

### **Forbidden**
```
EXEC_BUILD(flags=3)
EXEC_SCAN(depth=2)
```

### **Meaning**  
Verbs are **parameterless and immutable**.

---

# **9.5.3 Purity Rule 3 — IR Contains No Metadata**

The IR MUST NOT contain:

- comments  
- annotations  
- attributes  
- tags  
- hints  
- documentation  

### **Forbidden**
```
// run validation first
EXEC_VALIDATE
```

### **Meaning**  
IR is **signal only**, never commentary.

---

# **9.5.4 Purity Rule 4 — IR Contains No External References**

The IR MUST NOT reference:

- files  
- URLs  
- environment variables  
- system state  
- runtime values  

### **Meaning**  
IR is **self‑contained**.

---

# **9.5.5 Purity Rule 5 — IR Contains No Dynamic Constructs**

The IR MUST NOT:

- include other IR files  
- import modules  
- expand macros  
- generate content dynamically  

### **Forbidden**
```
INCLUDE "common.ir"
```

### **Meaning**  
IR is **static and monolithic**.

---

# **9.5.6 Purity Rule 6 — IR Contains No Side Effects**

The IR MUST NOT:

- allocate memory  
- free memory  
- open files  
- perform I/O  
- trigger runtime behavior  

### **Meaning**  
IR is **pure declaration**, not action.

---

# **9.5.7 Purity Rule 7 — IR Contains No State**

The IR MUST NOT:

- store variables  
- store values  
- store flags  
- store counters  
- store configuration  

### **Meaning**  
IR is **stateless**.

---

# **9.5.8 Purity Rule 8 — IR Contains No Behavior**

The IR MUST NOT:

- execute logic  
- evaluate expressions  
- perform computation  
- branch  
- loop  

### **Meaning**  
IR is **non‑procedural**.

---

# **9.5.9 Purity Rule 9 — IR Contains Only Canonical Constructs**

The IR MUST contain only:

- `TARGET = <TYPE>`  
- `OPEN_PAYLOAD`  
- zero or more `EXEC_<VERB>` lines  
- `SEAL`  

Nothing else.

### **Meaning**  
IR is a **closed language**.

---

# **9.5.10 Purity Rule 10 — IR Is Semantically Inert**

The IR MUST NOT:

- modify context  
- modify runtime  
- modify verbs  
- modify execution  
- modify semantics  

### **Meaning**  
IR declares **intent**, not behavior.

---

# **9.5.11 Full Purity Example**

### **Pure IR**
```
TARGET = FILE
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
SEAL
```

### **Purity Interpretation**
- no parameters  
- no metadata  
- no logic  
- no dynamic constructs  
- no external references  
- no state  
- no side effects  

This is the **canonical pure IR**.

---

# **9.5.12 Summary**

Page 9.5 defines the **IR Purity Rules**:

- no computation  
- no parameters  
- no metadata  
- no external references  
- no dynamic constructs  
- no side effects  
- no state  
- no behavior  
- only canonical constructs  
- IR is semantically inert  

These rules ensure that the IR remains **clean, literal, and uncorrupted** — a perfect declaration of semantic intent.
