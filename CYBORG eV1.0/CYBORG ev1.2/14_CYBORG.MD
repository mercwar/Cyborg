Advancing, Demon. The Runtime Codex deepens.

---

# **📘 PAGE 6.1 — RUNTIME CONTEXT MODEL (FORMAL SPECIFICATION)**  
### *AVIS Cyborg Language System — MSDN + ISO Hybrid Reference*  
*(Hybrid Markdown + Code‑Styled Blocks Edition)*  

---

## **6.1 Overview**

The **Runtime Context Model** defines the structure, lifecycle, and behavioral rules of the context object passed into `cyborg_payload`.  
This context is the **sole data vessel** through which a Cyborg Module interacts with the host environment.

The context model is:

- deterministic  
- target‑bound  
- non‑inferential  
- non‑allocating  
- non‑self‑modifying  
- strictly governed by the Runtime Layer  

This section is **normative**.

---

# **6.1.1 Context Principle 1 — One Context Per Module Execution**

Each invocation of `cyborg_payload` MUST receive:

- exactly one context object  
- allocated by the Runtime Layer  
- initialized by the Runtime Layer  
- owned by the Runtime Layer  

### **Meaning**  
The C Layer never creates, destroys, or reallocates context.

---

# **6.1.2 Context Principle 2 — Target‑Bound Structure**

The context type is determined **solely** by the IR target:

| IR Target | Context Type |
|-----------|--------------|
| `AI` | `CyborgContext` |
| `FILE` | `CyborgFile` |
| `LAYER` | `CyborgLayer` |

### **Meaning**  
The C Layer MUST NOT reinterpret or cast the context.

---

# **6.1.3 Context Principle 3 — No Dynamic Allocation**

The Runtime Layer MUST allocate the context:

- statically  
- on the stack  
- or via a fixed allocator  

### **Forbidden**
- dynamic resizing  
- reallocation  
- heap‑based expansion  
- variable‑sized structures  

The context MUST have a **fixed, deterministic size**.

---

# **6.1.4 Context Principle 4 — No Self‑Modification**

The context MUST NOT:

- modify its own structure  
- allocate memory internally  
- free memory internally  
- change its type  
- change its size  

### **Exception**
The verb `build` MAY modify **fields**, but not **structure**.

---

# **6.1.5 Context Principle 5 — No External References**

The context MUST NOT contain:

- pointers to external memory  
- pointers to global state  
- pointers to runtime objects  
- pointers to system resources  
- file handles  
- sockets  
- threads  

### **Meaning**  
The context is **self‑contained**.

---

# **6.1.6 Context Principle 6 — Deterministic Initialization**

The Runtime Layer MUST initialize:

- all fields  
- all buffers  
- all counters  
- all flags  

Initialization MUST be:

- deterministic  
- complete  
- non‑lazy  
- non‑deferred  

### **Forbidden**
- uninitialized fields  
- lazy initialization  
- runtime inference  

---

# **6.1.7 Context Principle 7 — No Runtime Mutation (Except Build)**

Only the verb `build` may modify context fields.

All other verbs MUST treat the context as **read‑only**.

### **Meaning**
- `validate` → read  
- `scan` → read  
- `give` → read  
- `explain` → read  
- `build` → write  

---

# **6.1.8 Context Principle 8 — No Cross‑Verb State Sharing**

Verb functions MUST NOT:

- store state inside the context for other verbs  
- rely on state written by other verbs  
- encode execution order into the context  
- use the context as a communication channel  

### **Meaning**  
The context is **not a message bus**.

---

# **6.1.9 Context Principle 9 — No Host‑Driven Mutation During Execution**

The host MUST NOT modify the context:

- during payload execution  
- between verb calls  
- asynchronously  
- concurrently  

### **Meaning**  
The context is **frozen** during execution, except for `build`.

---

# **6.1.10 Context Principle 10 — Deterministic Destruction**

After execution:

- the Runtime Layer MAY destroy the context  
- destruction MUST be deterministic  
- destruction MUST NOT trigger callbacks  
- destruction MUST NOT free external resources  

### **Meaning**  
Context destruction is a **silent, final operation**.

---

# **6.1.11 Full Context Lifecycle Example**

### **1. Host Allocates Context**
```c
CyborgLayer layer;
```

### **2. Host Initializes Context**
```c
init_layer(&layer);
```

### **3. Host Invokes Payload**
```c
int result = cyborg_payload(&layer);
```

### **4. Payload Executes Deterministically**
- verbs read/write fields  
- no external interaction  
- no memory allocation  

### **5. Host Destroys Context**
```c
destroy_layer(&layer);
```

This is the **canonical lifecycle**.

---

# **6.1.12 Summary**

Page 6.1 defines the **Runtime Context Model**:

- one context per execution  
- target‑bound structure  
- deterministic initialization  
- no dynamic allocation  
- no external references  
- no self‑modification  
- no cross‑verb communication  
- no host mutation during execution  
- deterministic destruction  

The context is the **pure, isolated data vessel** of the Cyborg Runtime.

---

Demon — the next scroll is ready.

Say:

```
continue
```

and **Page 6.2 — Verb Binding Model (Formal Specification)** will manifest.