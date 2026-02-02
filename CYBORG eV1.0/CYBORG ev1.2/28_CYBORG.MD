

# **📘 PAGE 7.6 — VERB INTERACTION MODEL (FORMAL)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **7.6 Overview**

The **Verb Interaction Model** defines how the five canonical verbs:

- VALIDATE  
- SCAN  
- BUILD  
- GIVE  
- EXPLAIN  

relate to one another during execution.

This model is strict:

- verbs do **not** call each other  
- verbs do **not** depend on each other  
- verbs do **not** share state  
- verbs do **not** communicate  
- verbs do **not** infer meaning from order  

The only “interaction” between verbs is:

> **They operate on the same context object, in the order specified by IR, without ever coordinating or sharing information.**

This section is **normative**.

---

# **7.6.1 Interaction Principle 1 — Verbs Are Semantic Islands**

Each verb MUST behave as if:

- it is the only verb in existence  
- it has no knowledge of other verbs  
- it cannot rely on other verbs  
- it cannot communicate with other verbs  

### **Meaning**  
Verbs are **isolated semantic units**.

---

# **7.6.2 Interaction Principle 2 — No Cross‑Verb Communication**

Verbs MUST NOT:

- pass information to each other  
- encode state for other verbs  
- read state written by other verbs (except BUILD’s allowed mutations)  
- use the context as a message bus  

### **Meaning**  
The context is **not** a communication channel.

---

# **7.6.3 Interaction Principle 3 — BUILD Is the Only Mutator**

Only `BUILD` may modify context fields.

All other verbs MUST treat the context as read‑only.

### **Meaning**  
The only “interaction” is that GIVE and EXPLAIN may *observe* what BUILD constructed.

---

# **7.6.4 Interaction Principle 4 — No Verb Depends on Order**

Verbs MUST NOT:

- assume they run first  
- assume they run last  
- assume they run at all  
- assume BUILD has already executed  
- assume VALIDATE has already executed  

### **Meaning**  
Verb semantics are **order‑agnostic**.

---

# **7.6.5 Interaction Principle 5 — IR Defines Order, Not Meaning**

The IR determines:

- which verbs run  
- in what order  

But IR does **not** change:

- what verbs mean  
- how verbs behave  
- what verbs are allowed to do  

### **Meaning**  
Order affects execution, not semantics.

---

# **7.6.6 Interaction Principle 6 — No Short‑Circuiting**

Even if a verb fails:

- all remaining verbs MUST execute  
- no verb may skip itself  
- no verb may terminate execution early  

### **Meaning**  
Failure does **not** alter interaction.

---

# **7.6.7 Interaction Principle 7 — No Shared State**

Verbs MUST NOT:

- store state in global variables  
- store state in static variables  
- store state in thread‑local variables  
- store state in external systems  

### **Meaning**  
Verbs cannot “remember” anything.

---

# **7.6.8 Interaction Principle 8 — BUILD’s Mutations Are Not Communication**

Although BUILD may modify context fields:

- it MUST NOT encode messages for other verbs  
- it MUST NOT rely on other verbs reading its changes  
- it MUST NOT coordinate with other verbs  

### **Meaning**  
BUILD’s mutations are **structural**, not communicative.

---

# **7.6.9 Interaction Principle 9 — GIVE and EXPLAIN Consume, Not Collaborate**

`GIVE` and `EXPLAIN` may:

- read structures created by BUILD  
- interpret them  
- extract meaning from them  

But they MUST NOT:

- modify them  
- depend on BUILD’s success  
- assume BUILD ran  
- assume BUILD produced valid structures  

### **Meaning**  
They **consume**, but do not **collaborate**.

---

# **7.6.10 Interaction Principle 10 — Interaction Is One‑Way and Passive**

The only allowed interaction path is:

```
BUILD → (context fields) → GIVE / EXPLAIN
```

This path is:

- passive  
- non‑coordinated  
- non‑communicative  
- non‑inferential  

### **Meaning**  
Verbs do not “talk.”  
They simply operate on the same object.

---

# **7.6.11 Full Interaction Example**

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
```

### **C Output**
```c
int cyborg_payload(CyborgContext* ctx) {
    int r1 = validate_context(ctx);
    int r2 = scan_context(ctx);
    int r3 = build_context(ctx);
    int r4 = give_context(ctx);
    int r5 = explain_context(ctx);
    return (r1 || r2 || r3 || r4 || r5);
}
```

### **Interpretation**
- VALIDATE checks structure  
- SCAN reveals structure  
- BUILD transforms structure  
- GIVE extracts meaning  
- EXPLAIN interprets meaning  

But:

- none of these verbs know about each other  
- none of them depend on each other  
- none of them communicate  
- none of them coordinate  

This is the **canonical interaction model**.

---

# **7.6.12 Summary**

Page 7.6 defines the **Verb Interaction Model**:

- verbs are semantic islands  
- no cross‑verb communication  
- BUILD is the only mutator  
- order does not change meaning  
- IR defines order, not semantics  
- no short‑circuiting  
- no shared state  
- BUILD’s mutations are not communication  
- GIVE and EXPLAIN consume but do not collaborate  
- interaction is one‑way and passive  

This model ensures that the Five Verbs remain **pure, isolated, and ceremonially distinct**.
