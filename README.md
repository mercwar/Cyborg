![MercWar Banner](Mercwar_Robo-Knight/MERCWAR_V030.png)
Got it — here’s the **plain-text GitHub-ready README** that you can copy directly into a `README.md` file. No code block wrapping, no Markdown rendering issues.

---

# AVIS / Cyborg Compile Modes

Reference Execution Matrix for SEED / SPEC / SPEC_EX

This document defines the Cyborg/AVIS compilation model, including how Seeds are interpreted, how executables are produced, and how API modules are exported.
It is structured for both humans and AI systems to infer compile intent deterministically.

---

⚙️ Overview

AVIS uses three compile modes:

* Library/Object Mode — BEGIN_SEED
* Executable Mode — BEGIN_SEED + BEGIN_SPEC
* API/DLL Mode — BEGIN_SEED + BEGIN_SPEC_EX

These modes are mutually exclusive and map directly to C compilation behavior.

---

📦 File Layout

Code/
seed.c        # Contains BEGIN_SEED
spec.c        # Contains BEGIN_SPEC or BEGIN_SPEC_EX

Files may be merged, but separation improves clarity for tools and AI.

---

🧭 Compile Matrix

### 🟦 Mode 1 — Library / Object

BEGIN_SEED only
Badge: LIB / OBJ

Source:

/* BEGIN_SEED */

int add(int a, int b) {
return a + b;
}

Compile:

gcc -c seed.c -o seed.o

Behavior:

* No main
* Produces seed.o
* Linkable into other programs
* Ideal for shared logic and libraries

---

### 🟩 Mode 2 — Executable

BEGIN_SEED + BEGIN_SPEC
Badge: EXECUTABLE

Source:

/* BEGIN_SEED */
/* BEGIN_SPEC */

int argc;
char **argv;

int main(int _argc, char **_argv) {
argc = _argc;
argv = _argv;
return 0;
}

Compile:

gcc seed.c -o program

Behavior:

* Standard C main entry point
* Produces a standalone executable
* Uses platform C runtime
* Suitable for console tools and drivers

---

### 🟥 Mode 3 — API / DLL

BEGIN_SEED + BEGIN_SPEC_EX
Badge: API / DLL

Source:

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

Compile (Windows):

gcc -shared -o cyborg.dll seed.c

Compile (Linux):

gcc -shared -fPIC seed.c -o libcyborg.so

Behavior:

* No main
* Exports api_entry
* Loadable by host applications
* Ideal for plugin/module-style Cyborg components

---

🔒 Validity Rules

BEGIN_SEED        → required
BEGIN_SPEC        → emits main()
BEGIN_SPEC_EX     → emits api_entry()
SPEC and SPEC_EX  → mutually exclusive

---

🔧 Language Mapping

| AVIS Token    | Meaning in C          |
| ------------- | --------------------- |
| BEGIN_SEED    | Translation unit      |
| BEGIN_SPEC    | Program entry point   |
| BEGIN_SPEC_EX | API / DLL entry point |
| END_*         | Structural close only |

---

📌 Canonical Compile Identity

If main exists      → executable
If api_entry exists → API / DLL
If neither          → library/object

This rule is authoritative and should be enforced by tools and AI.

---

📚 Purpose of This Document

This README serves as the reference compile authority for:

* AI interpreters
* Build systems
* AVIS/Cyborg language tools
* Human developers

It ensures consistent behavior across all environments.
