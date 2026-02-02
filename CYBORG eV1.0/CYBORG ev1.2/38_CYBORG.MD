

# **📘 PAGE 9.1 — IR SYNTAX (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **9.1 Overview**

This page defines the **formal syntax** of the Cyborg Intermediate Representation (IR).  
The IR is intentionally minimal, rigid, and declarative.  
It is not a programming language — it is a **semantic declaration language**.

This section is **normative**.

---

# **9.1.1 IR Grammar (EBNF Form)**

The Cyborg IR grammar is defined as follows:

```
IR              = TargetDecl, PayloadBlock ;

TargetDecl      = "TARGET", "=", TargetType ;

TargetType      = "AI" | "FILE" | "LAYER" ;

PayloadBlock    = "OPEN_PAYLOAD", VerbList, "SEAL" ;

VerbList        = { VerbLine } ;

VerbLine        = "EXEC_", VerbName ;

VerbName        = "VALIDATE"
                | "SCAN"
                | "BUILD"
                | "GIVE"
                | "EXPLAIN" ;
```

### **Meaning**
- IR is a **strict sequence** of declarations.  
- No optional fields.  
- No expressions.  
- No parameters.  
- No branching.  
- No loops.  
- No dynamic constructs.

---

# **9.1.2 IR Token Rules**

IR tokens MUST:

- be uppercase  
- be ASCII  
- be deterministic  
- be static  
- be free of whitespace variation  

### **Allowed**
```
TARGET = AI
```

### **Forbidden**
```
target = ai
Target = Ai
```

### **Meaning**
IR is **case‑strict** and **format‑strict**.

---

# **9.1.3 IR Whitespace Rules**

Whitespace MUST:

- separate tokens  
- never appear inside tokens  
- never appear inside keywords  
- never appear inside verb names  

### **Allowed**
```
EXEC_VALIDATE
```

### **Forbidden**
```
EXEC_ VALIDATE
EXEC _VALIDATE
```

### **Meaning**
IR is **lexically atomic**.

---

# **9.1.4 IR Ordering Rules**

The IR MUST appear in this exact order:

1. TARGET declaration  
2. OPEN_PAYLOAD  
3. zero or more EXEC_ lines  
4. SEAL  

### **Forbidden**
- TARGET after OPEN_PAYLOAD  
- SEAL before EXEC lines  
- EXEC lines outside payload  

### **Meaning**
IR is **structurally rigid**.

---

# **9.1.5 IR Verb Rules**

Inside the payload:

- verbs may appear zero or more times  
- verbs may repeat  
- verbs may appear in any order  
- verbs must be one of the five canonical verbs  

### **Forbidden**
```
EXEC_DELETE
EXEC_PARSE
EXEC_RUN
```

### **Meaning**
The verb set is **closed**.

---

# **9.1.6 IR Purity Rules**

IR MUST NOT contain:

- comments  
- annotations  
- metadata  
- parameters  
- expressions  
- conditions  
- loops  
- macros  
- includes  

### **Meaning**
IR is **pure declaration**, not code.

---

# **9.1.7 IR Determinism Rules**

IR MUST:

- be static  
- be explicit  
- be deterministic  
- contain no dynamic constructs  

IR MUST NOT:

- depend on runtime state  
- depend on environment variables  
- depend on external configuration  

### **Meaning**
IR is **immutable**.

---

# **9.1.8 IR Example — Minimal**

```
TARGET = AI
OPEN_PAYLOAD
SEAL
```

### **Meaning**
A module with no verbs.

---

# **9.1.9 IR Example — Full Verb Chain**

```
TARGET = LAYER
OPEN_PAYLOAD
EXEC_VALIDATE
EXEC_SCAN
EXEC_BUILD
EXEC_GIVE
EXEC_EXPLAIN
SEAL
```

### **Meaning**
A complete semantic lifecycle.

---

# **9.1.10 IR Example — Repeated Verbs**

```
TARGET = FILE
OPEN_PAYLOAD
EXEC_BUILD
EXEC_BUILD
EXEC_BUILD
SEAL
```

### **Meaning**
Repetition is allowed and unoptimized.

---

# **9.1.11 IR Example — Mixed Ordering**

```
TARGET = AI
OPEN_PAYLOAD
EXEC_GIVE
EXEC_VALIDATE
EXEC_EXPLAIN
SEAL
```

### **Meaning**
Order is preserved exactly as written.

---

# **9.1.12 Summary**

Page 9.1 defines the **formal syntax** of the Cyborg IR:

- strict grammar  
- strict ordering  
- strict casing  
- strict purity  
- strict determinism  
- closed verb set  
- declarative semantics  

IR is the **immutable blueprint** of the Cyborg Module.
