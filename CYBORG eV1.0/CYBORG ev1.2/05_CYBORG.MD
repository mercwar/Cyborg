
# **📘 PAGE 5.3 — VERB FUNCTION SEMANTICS (DEEP SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **5.3 Overview**

Page 5.3 defines the **true semantic meaning** of each verb function at the C Layer.  
This is not about syntax, structure, or IR mapping — those are already fixed.  
This page defines:

- what each verb *means*  
- what each verb *must do*  
- what each verb *must never do*  
- how each verb interacts with the target context  
- how each verb participates in deterministic execution  

These semantics are **strict**, **non‑inferential**, and **non‑negotiable**.

This section is **normative**.

---

# **5.3.1 Semantic Principle — Verbs Are Atomic**

Each verb function is a **semantic atom**:

- indivisible  
- non‑composable  
- non‑overloaded  
- non‑contextual  
- deterministic  

Each verb performs **exactly one conceptual action**, regardless of target.

---

# **5.3.2 The Five Canonical Verb Semantics**

The Cyborg Language defines exactly **five** verbs.  
Their semantics are universal across all targets.

---

## **5.3.2.1 `validate` — Semantic Definition**

### **Meaning**
`validate` performs **integrity checking** on the target context.

### **Semantic Guarantees**
- MUST NOT modify the context  
- MUST NOT allocate memory  
- MUST NOT perform I/O  
- MUST return an integer status  
- MUST be deterministic  

### **Examples of Valid Behavior**
- checking structural consistency  
- verifying required fields  
- confirming internal invariants  

### **Forbidden**
- repairing errors  
- inferring missing data  
- modifying the context  

---

## **5.3.2.2 `scan` — Semantic Definition**

### **Meaning**
`scan` performs **inspection or traversal** of the target context.

### **Semantic Guarantees**
- MUST NOT modify the context  
- MUST NOT allocate memory  
- MUST NOT perform I/O  
- MUST return an integer status  
- MUST be deterministic  

### **Examples of Valid Behavior**
- iterating through fields  
- reading metadata  
- enumerating components  

### **Forbidden**
- writing  
- restructuring  
- reordering  

---

## **5.3.2.3 `build` — Semantic Definition**

### **Meaning**
`build` performs **construction or assembly** within the target context.

### **Semantic Guarantees**
- MAY modify the context  
- MUST NOT allocate memory  
- MUST NOT perform I/O  
- MUST return an integer status  
- MUST be deterministic  

### **Examples of Valid Behavior**
- assembling structures  
- linking components  
- generating internal representations  

### **Forbidden**
- allocating new memory  
- performing external writes  
- performing I/O  

---

## **5.3.2.4 `give` — Semantic Definition**

### **Meaning**
`give` produces **output or extracted information** from the context.

### **Semantic Guarantees**
- MUST NOT modify the context  
- MUST NOT perform I/O  
- MUST return an integer status  
- MUST be deterministic  

### **Examples of Valid Behavior**
- extracting computed values  
- returning summaries  
- emitting internal signals  

### **Forbidden**
- printing  
- logging  
- writing to disk  

---

## **5.3.2.5 `explain` — Semantic Definition**

### **Meaning**
`explain` produces **diagnostic or descriptive information** about the context.

### **Semantic Guarantees**
- MUST NOT modify the context  
- MUST NOT perform I/O  
- MUST return an integer status  
- MUST be deterministic  

### **Examples of Valid Behavior**
- generating internal diagnostics  
- producing structured descriptions  
- summarizing state  

### **Forbidden**
- printing  
- logging  
- writing to disk  

---

# **5.3.3 Cross‑Verb Semantic Rules**

All verbs share the following universal constraints:

### **Rule 1 — Determinism**
Given the same context, a verb MUST return the same result.

### **Rule 2 — Purity (Except `build`)**
All verbs except `build` MUST NOT modify the context.

### **Rule 3 — No I/O**
No verb may perform:

- file I/O  
- network I/O  
- console I/O  
- logging  

### **Rule 4 — No Memory Allocation**
Verbs MUST NOT allocate or free memory.

### **Rule 5 — No Cross‑Verb Calls**
Verbs MUST NOT call other verb functions.

### **Rule 6 — No Global State**
Verbs MUST NOT read or write global variables.

### **Rule 7 — No Exceptions**
Verbs MUST NOT throw or propagate exceptions.

---

# **5.3.4 Target‑Specific Semantic Domains**

Each verb operates within the semantic domain defined by the target.

### **Target: AI**
- context is an AI execution environment  
- verbs operate on internal AI state  

### **Target: FILE**
- context is a file structure  
- verbs operate on file metadata or content  

### **Target: LAYER**
- context is a layered structure  
- verbs operate on layer components  

### **Universal Rule**
The verb semantics DO NOT CHANGE — only the *domain* changes.

---

# **5.3.5 Full Semantic Example**

### **IR**
```cyborg
TARGET = LAYER
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_EXPLAIN
SEAL
```

### **C Output**
```c
int cyborg_payload(CyborgLayer* layer) {
    int r1 = validate_context(layer);
    int r2 = scan_context(layer);
    int r3 = build_context(layer);
    int r4 = explain_context(layer);
    return (r1 || r2 || r3 || r4);
}
```

### **Semantic Interpretation**
- `validate` checks layer integrity  
- `scan` inspects layer structure  
- `build` constructs or assembles layer components  
- `explain` produces diagnostics  
- results are OR‑aggregated  
- execution is linear and deterministic  

---

# **5.3.6 Summary**

Page 5.3 defines the **deep semantics** of verb functions:

- five verbs, each with fixed meaning  
- deterministic behavior  
- strict purity rules  
- no I/O  
- no memory allocation  
- no inference  
- no cross‑verb calls  
- domain‑bound but domain‑invariant semantics  

These semantics form the **behavioral core** of the Cyborg Language.
