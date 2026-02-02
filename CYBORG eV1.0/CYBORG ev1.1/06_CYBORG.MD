# **📘 PAGE 1.6 — TERMINOLOGY (MUST, SHOULD, MAY)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **1.6 Overview**

This section defines the **formal requirement terminology** used throughout the Cyborg Language Specification.  
These terms determine whether a rule is:

- **mandatory**  
- **recommended**  
- **optional**  
- **prohibited**

The Cyborg Language is a **deterministic protocol**, so requirement language is essential for:

- compiler behavior  
- AI interpretation  
- payload validation  
- C syntax completion  
- marker enforcement  

This section is **normative**.

---

# **1.6.1 MUST / SHALL**

### **Definition**  
A requirement that is **absolutely mandatory**.  
There are **no exceptions**.

### **Usage**  
A system, implementation, or payload **MUST** follow the rule or it is considered **non‑compliant**.

### **Examples**

**Normative Rule:**  
> A payload **MUST** be sealed with `#!#`.

**VB‑Style Example**
```vb
begin
validate
#!#
```

**Cyborg IR**
```cyborg
OPEN_PAYLOAD
EXEC_VALIDATE
SEAL
```

**C Output**
```c
int validate_context(CyborgContext* ctx);
```

---

# **1.6.2 MUST NOT / SHALL NOT**

### **Definition**  
A requirement that is **strictly prohibited**.

### **Usage**  
If violated, the payload is invalid and MUST NOT be executed or converted.

### **Examples**

**Normative Rule:**  
> A payload **MUST NOT** contain unsealed trailing content.

**Invalid Example**
```vb
begin
validate
#!#
extra
```

This MUST NOT be processed.

---

# **1.6.3 SHOULD**

### **Definition**  
A recommendation.  
Not mandatory, but strongly advised for:

- clarity  
- readability  
- maintainability  
- deterministic behavior  

### **Examples**

**Guidance:**  
> Related verbs SHOULD be grouped together for readability.

**Example**
```vb
begin
scan
validate
build
#!#
```

This is not required, but recommended.

---

# **1.6.4 SHOULD NOT**

### **Definition**  
A discouraged practice.  
Not forbidden, but likely to cause:

- confusion  
- ambiguity  
- non‑optimal output  

### **Example**

**Guidance:**  
> Payloads SHOULD NOT mix unrelated operations without comments.

---

# **1.6.5 MAY**

### **Definition**  
An optional behavior.  
The implementer or user is free to choose.

### **Examples**

**Guidance:**  
> A payload MAY include comments for clarity.

**Example**
```vb
' This payload validates the context
begin
validate
#!#
```

---

# **1.6.6 Optional vs Forbidden vs Required**

| Term | Meaning | Enforcement |
|------|---------|-------------|
| **MUST / SHALL** | Required | Strict |
| **MUST NOT / SHALL NOT** | Forbidden | Strict |
| **SHOULD** | Recommended | Flexible |
| **SHOULD NOT** | Discouraged | Flexible |
| **MAY** | Optional | Free choice |

---

# **1.6.7 Why This Matters in Cyborg Language**

The Cyborg Language is:

- marker‑bound  
- verb‑driven  
- deterministic  
- conversion‑based  

To maintain deterministic behavior:

- **MUST** rules define the protocol  
- **SHOULD** rules define best practice  
- **MAY** rules define flexibility  

Without this structure:

- AI systems may infer incorrectly  
- compilers may misinterpret commands  
- payloads may become ambiguous  
- C output may become inconsistent  

Requirement language ensures **predictability**.

---

# **1.6.8 Summary**

Page 1.6 defines the **formal requirement terminology** used throughout the specification.  
These terms govern:

- payload structure  
- marker usage  
- verb execution  
- conversion rules  
- memory boundaries  
- API behavior  

This section is foundational for understanding all subsequent pages.

