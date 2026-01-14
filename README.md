![MercWar Banner](Mercwar_Robo-Knight/MERCWAR_V030.png)Here’s a **fully merged, plain-text GitHub-ready README.md** combining all your HTML styling notes, colored-mode emojis, and the original AVIS / Cyborg compile documentation. You can copy this directly into your repo without losing formatting or clarity:

---

# AVIS / Cyborg Compile Modes

🔥 Reference Execution Matrix for `BEGIN_SEED`, `BEGIN_SPEC`, and `BEGIN_SPEC_EX`

This document defines the **Cyborg / AVIS compilation model**, including how Seeds are interpreted, how executables are produced, and how API modules are exported.
It is structured so that both humans and AI systems (including Copilot) can **infer compile intent deterministically**.

---

## 🎨 Legend & Visual Style

To simulate color inside GitHub Markdown:

* 🟦 Blue → Library/Object
* 🟩 Green → Executable
* 🟥 Red → API/DLL
* 🟪 Purple → Rules / Law
* 🟧 Orange → Notes / Behavior

---

## 📦 File Layout

```
seed.c        # Contains BEGIN_SEED
spec.c        # Contains BEGIN_SPEC or BEGIN_SPEC_EX
```

You may merge these into a single file, but keeping them separated improves clarity for tools and AI.

---

## ⚙️ Compile Modes Overview

* 🟦 **Mode 1 — Library / Object**: `BEGIN_SEED`
* 🟩 **Mode 2 — Executable**: `BEGIN_SEED + BEGIN_SPEC`
* 🟥 **Mode 3 — API / DLL**: `BEGIN_SEED + BEGIN_SPEC_EX`

These modes are mutually exclusive and map directly to C compilation behavior.

---

## 🧭 Compile Matrix

### 🟦 Mode 1 — Library / Object

**BEGIN_SEED only**

🧾 Source:

```c
/* BEGIN_SEED */

int add(int a, int b) {
    return a + b;
}
```

🔧 Compile:

```bash
gcc -c seed.c -o seed.o
```

🟧 Behavior:

* No `main` symbol
* Produces `seed.o`
* Linkable into other programs
* Use for shared logic / libraries

---

### 🟩 Mode 2 — Executable

**BEGIN_SEED + BEGIN_SPEC**

🧾 Source:

```c
/* BEGIN_SEED */
/* BEGIN_SPEC */

int argc;
char **argv;

int main(int _argc, char **_argv) {
    argc = _argc;
    argv = _argv;
    return 0;
}
```

🔧 Compile:

```bash
gcc seed.c -o program
```

🟧 Behavior:

* Defines standard C `main` entry point
* Produces a standalone executable
* Uses platform C runtime
* Use for tools, drivers, and command-line programs

---

### 🟥 Mode 3 — API / DLL

**BEGIN_SEED + BEGIN_SPEC_EX**

🧾 Source:

```c
/* BEGIN_SEED */
/* BEGIN_SPEC_EX */

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

int argc;
char **argv;

EXPORT int api_entry(int _argc, char **_argv) {
    argc = _argc;
    argv = _argv;
    return 0;
}
```

🔧 Compile:

**Windows:**

```bash
gcc -shared -o cyborg.dll seed.c
```

**Linux:**

```bash
gcc -shared -fPIC seed.c -o libcyborg.so
```

🟧 Behavior:

* No `main` symbol
* Exports `api_entry` for host loading
* Compiles to DLL (`.dll`) or SO (`.so`)
* Use for plugin/module-style Cyborg components

---

### 🟪 Validity Rules (Authoritative)

* `BEGIN_SEED` → required in all modes
* `BEGIN_SPEC` → emits `main()`
* `BEGIN_SPEC_EX` → emits `api_entry()`
* `SPEC` and `SPEC_EX` → mutually exclusive

---

### 🎛️ Language Mapping

| AVIS Token    | Meaning in C          |
| ------------- | --------------------- |
| BEGIN_SEED    | Translation unit      |
| BEGIN_SPEC    | Program entry point   |
| BEGIN_SPEC_EX | API / DLL entry point |
| END_*         | Structural close only |

---

### 🧩 Canonical Compile Identity

* If `main` exists → executable
* If `api_entry` exists → API/DLL
* If neither exists → library/object

This rule is canonical and should be enforced by tools, build systems, and AI.

---

## 📚 Purpose of This Document

This README serves as the **reference compile authority** for:

* AI interpreters (including Copilot)
* Build systems
* AVIS / Cyborg language tooling
* Human developers

It defines how Cyborg/AVIS seeds map to C compilation modes in a way that is explicit, deterministic, and safe to automate.

---

I can also create a **matching CONTRIBUTING.md** or **Visual Quick Reference** with the same emoji/color scheme if you want the repo fully cohesive.

Do you want me to do that next?
