![MercWar Banner](Mercwar_Robo-Knight/MERCWAR_V030.png)🌌 AVIS / Cyborg Compile Modes

🔥 Reference Execution Matrix for SEED / SPEC / SPEC_EX
This document defines the Cyborg/AVIS compilation model, including how Seeds are interpreted, how executables are produced, and how API modules are exported.
It is structured for both humans and AI systems to infer compile intent deterministically.

🎨 Legend & Visual Style
To simulate color inside GitHub Markdown:

🟦 Blue → Library/Object

🟩 Green → Executable

🟥 Red → API/DLL

🟪 Purple → Rules / Law

🟧 Orange → Notes / Behavior

📦 File Layout
Code
seed.c        # Contains BEGIN_SEED
spec.c        # Contains BEGIN_SPEC or BEGIN_SPEC_EX
Files may be merged, but separation improves clarity for tools and AI.

⚙️ Compile Matrix (Color‑Enhanced)
Below is the full execution matrix rewritten with emoji color blocks and visual flair.

🟦 Mode 1 — Library / Object
BEGIN_SEED only
🧾 Source
c
/* BEGIN_SEED */

int add(int a, int b) {
    return a + b;
}
🔧 Compile
bash
gcc -c seed.c -o seed.o
🟧 Behavior
No main

Produces seed.o

Linkable into other programs

Ideal for shared logic and libraries

🟩 Mode 2 — Executable
BEGIN_SEED + BEGIN_SPEC
🧾 Source
c
/* BEGIN_SEED */
/* BEGIN_SPEC */

int argc;
char **argv;

int main(int _argc, char **_argv) {
    argc = _argc;
    argv = _argv;
    return 0;
}
🔧 Compile
bash
gcc seed.c -o program
🟧 Behavior
Standard C main entry point

Produces a standalone executable

Uses platform C runtime

Suitable for console tools and drivers

🟥 Mode 3 — API / DLL
BEGIN_SEED + BEGIN_SPEC_EX
🧾 Source
c
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
🔧 Compile (Windows)
bash
gcc -shared -o cyborg.dll seed.c
🔧 Compile (Linux)
bash
gcc -shared -fPIC seed.c -o libcyborg.so
🟧 Behavior
No main

Exports api_entry

Loadable by host applications

Ideal for plugin/module-style Cyborg components

🟪 Validity Rules (Authoritative)
Code
BEGIN_SEED      → required
BEGIN_SPEC      → emits main()
BEGIN_SPEC_EX   → emits api_entry()
SPEC and SPEC_EX → mutually exclusive
🎛️ Language Mapping
Token	Meaning in C
BEGIN_SEED	Translation unit
BEGIN_SPEC	Program entry point
BEGIN_SPEC_EX	API/DLL entry point
END_*	Structural close only
🧩 Canonical Compile Identity
Code
If main exists → executable
If api_entry exists → API/DLL
If neither → library/object
This rule is canonical and should be enforced by tools and AI.

📚 Purpose of This Document
This README serves as the reference compile authority for:

AI interpreters

Build systems

AVIS/Cyborg language tools

Human developers

It ensures consistent behavior across all environments.
