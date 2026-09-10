# **📘 PAGE 1.5 — NORMATIVE VS INFORMATIVE SECTIONS**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*

---

## **1.5 Overview**

This section defines the **two types of content** used throughout the Cyborg Language Specification:

- **Normative Sections** — rules that MUST be followed  
- **Informative Sections** — guidance, examples, and explanations  

This distinction is critical because the Cyborg Language is a **protocol**, not a narrative.  
Implementers MUST know which parts define **required behavior** and which parts provide **contextual understanding**.

---

# **1.5.1 Normative Sections**

Normative sections define:

- required syntax  
- required behavior  
- required markers  
- required execution semantics  
- required conversion rules  
- required memory boundaries  
- required error conditions  

These sections use ISO‑style requirement language:

| Keyword | Meaning |
|---------|---------|
| **MUST / SHALL** | Required behavior |
| **MUST NOT / SHALL NOT** | Prohibited behavior |
| **SHOULD** | Recommended behavior |
| **MAY** | Optional behavior |

### **Normative Example**

```vb
begin
validate
#!#
```

### Normative Interpretation

- A payload **MUST** begin with `begin` or `#BGIN`.  
- A payload **MUST** end with `#!#`.  
- The verb `validate` **MUST** map to a C function.  
- The payload **MUST NOT** contain unsealed content.  

### Normative C Output

```c
int validate_context(CyborgContext* ctx);
```

---

# **1.5.2 Informative Sections**

Informative sections provide:

- examples  
- explanations  
- diagrams  
- usage notes  
- best practices  
- background information  

Informative content **does not define required behavior**.

### **Informative Example**

> “Developers may find it useful to group related verbs together for readability.”

This is **guidance**, not a rule.

### Informative Example Block

```vb
' This example shows a typical validation payload
set to you
begin
scan
validate
#!#
```

This example is **informative**, not normative.

---

# **1.5.3 How to Identify Normative vs Informative Sections**

Normative sections:

- use MUST / SHALL / REQUIRED  
- define rules  
- define constraints  
- define conversion behavior  
- define marker boundaries  

Informative sections:

- use MAY / CAN / OPTIONAL  
- provide examples  
- provide commentary  
- provide diagrams  
- provide context  

---

# **1.5.4 Why This Distinction Matters**

The Cyborg Language is used by:

- humans  
- AI systems  
- compilers  
- interpreters  
- validators  

These systems must know:

- **what is required**  
- **what is optional**  
- **what is guidance**  
- **what is law**  

Without this distinction:

- AI systems may infer incorrectly  
- compilers may misinterpret commands  
- validators may enforce optional behavior  
- payloads may become non‑deterministic  

The Cyborg Language is built on **determinism**, and determinism requires **clear boundaries**.

---

# **1.5.5 Mixed Sections**

Some sections contain both normative and informative content.

Example:

### Mixed Section Example

**Normative:**  
> The payload MUST be sealed with `#!#`.

**Informative:**  
> Sealing the payload ensures that the engine does not process trailing content.

Mixed sections are allowed, but normative content MUST be clearly identifiable.

---

# **1.5.6 Summary**

Page 1.5 establishes the **rules of interpretation** for the entire document:

- Normative sections define **required behavior**  
- Informative sections provide **guidance and examples**  
- ISO requirement language is used consistently  
- Determinism depends on clear separation of rule vs guidance  

This prepares the reader for the technical depth of the remaining pages.

