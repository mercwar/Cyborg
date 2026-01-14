![MercWar Banner](Mercwar_Robo-Knight/MERCWAR_V030.png)
AVIS / Cyborg Compile System
Reference Architecture for SEED, SPEC, and SPEC_EX Compilation
This repository defines the Cyborg/AVIS compilation model, including how Seeds are interpreted, how executables are produced, and how API modules are exported.
It provides a predictable, machine‑readable structure for both humans and AI systems.

📦 File Layout
Code
seed.c        # Contains BEGIN_SEED
spec.c        # Contains BEGIN_SPEC or BEGIN_SPEC_EX
Files may be merged, but separating intent improves clarity for tools and AI.

🌱 1. BEGIN_SEED (Library / Object Mode)
A file containing only BEGIN_SEED compiles into a C object file.

Example
c
/* BEGIN_SEED */

int add(int a, int b) {
    return a + b;
}
Compile
bash
gcc -c seed.c -o seed.o
Behavior
Produces seed.o

No main function

Linkable into other programs

🚀 2. BEGIN_SEED + BEGIN_SPEC (Executable Mode)
Adding BEGIN_SPEC emits a standard C entry point.

Example
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
Compile
bash
gcc seed.c -o program
Behavior
Produces an executable

Standard main entry point

Full C runtime

🔌 3. BEGIN_SEED + BEGIN_SPEC_EX (API / DLL Mode)
BEGIN_SPEC_EX emits an API entry instead of main.

Example
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
Compile (Windows)
bash
gcc -shared -o cyborg.dll seed.c
Compile (Linux)
bash
gcc -shared -fPIC seed.c -o libcyborg.so
Behavior
No main

Exported api_entry

Loadable by host applications

⚖️ Validity Rules
Code
BEGIN_SEED      → required
BEGIN_SPEC      → emits main()
BEGIN_SPEC_EX   → emits api_entry()
SPEC and SPEC_EX → mutually exclusive
🔧 Language Mapping
AVIS Token	Meaning in C
BEGIN_SEED	Translation unit
BEGIN_SPEC	Program entry point
BEGIN_SPEC_EX	API/DLL entry point
END_*	Structural close only
🧩 Compile Identity (Authoritative)
Code
If main exists → executable
If api_entry exists → API/DLL
If neither → library/object
This rule is canonical and should be enforced by tools and AI.

📚 Purpose of This Repository
This repo serves as the reference compile authority for:

AI interpreters

Build systems

AVIS/Cyborg language tools

Human developers

It ensures consistent behavior across all environments.
