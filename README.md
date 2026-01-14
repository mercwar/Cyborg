![MercWar Banner](Mercwar_Robo-Knight/MERCWAR_V030.png)
BEGIN_SEED README_COMPILE_GUIDE
#AVIS_LANG CYBORD
#AVIS_KIND DOCUMENT
#AVIS_EXECUTION SYMBOLIC

DOCUMENT_HTML
<!-- AVIS / Cyborg Compile Modes README -->

<h1 style="font-size:40px; color:#ffd166; text-align:center; margin-bottom:4px;">
  AVIS / Cyborg Compile Modes
</h1>

<h2 style="font-size:22px; color:#a0c4ff; text-align:center; margin-top:0; margin-bottom:24px;">
  Reference Execution Matrix for <code>BEGIN_SEED</code>, <code>BEGIN_SPEC</code>, and <code>BEGIN_SPEC_EX</code>
</h2>

<p style="font-size:15px; line-height:1.6;">
This document defines the <strong>Cyborg / AVIS compilation model</strong>, including how Seeds are interpreted, how executables are produced, and how API modules are exported.
It is structured so that both humans and AI systems (including Copilot) can <strong>infer compile intent deterministically</strong>.
</p>

<hr style="border:0; border-top:1px solid #444; margin:24px 0;" />

<h2 style="font-size:24px; color:#ffb3c1;">File Layout</h2>

<p style="font-size:14px; line-height:1.5;">
<code>seed.c</code> — Contains <code>BEGIN_SEED</code><br/>
<code>spec.c</code> — Contains <code>BEGIN_SPEC</code> or <code>BEGIN_SPEC_EX</code><br/>
You may merge these into a single file, but separation improves clarity for tools and AI.
</p>

<hr style="border:0; border-top:1px solid #444; margin:24px 0;" />

<h2 style="font-size:24px; color:#bde0fe;">Compile Modes Overview</h2>

<ul style="font-size:14px; line-height:1.6;">
<li><strong style="color:#4dabf7;">Mode 1 — Library / Object</strong>: <code>BEGIN_SEED</code></li>
<li><strong style="color:#51cf66;">Mode 2 — Executable</strong>: <code>BEGIN_SEED + BEGIN_SPEC</code></li>
<li><strong style="color:#ff6b6b;">Mode 3 — API / DLL</strong>: <code>BEGIN_SEED + BEGIN_SPEC_EX</code></li>
</ul>

<hr style="border:0; border-top:1px solid #444; margin:24px 0;" />

<h2 style="font-size:26px; color:#e9ecef; text-align:center; margin-bottom:10px;">
Compile Matrix
</h2>

<table style="width:100%; border-collapse:collapse; font-size:14px;">
<thead>
<tr>
<th style="background-color:#1d3557; color:#f1faee; padding:10px; text-align:left; font-size:16px;">Mode</th>
<th style="background-color:#1d3557; color:#f1faee; padding:10px; text-align:left; font-size:16px;">Source Pattern</th>
<th style="background-color:#1d3557; color:#f1faee; padding:10px; text-align:left; font-size:16px;">Compile Command</th>
<th style="background-color:#1d3557; color:#f1faee; padding:10px; text-align:left; font-size:16px;">Result &amp; Behavior</th>
</tr>
</thead>
<tbody>

<!-- Mode 1 -->
<tr>
<td style="border:1px solid #343a40; padding:10px; background-color:#0b7285; color:#f8f9fa; font-weight:bold; white-space:nowrap;">
Library / Object<br/>
<span style="font-size:12px; color:#d0ebff;">BEGIN_SEED only</span>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#111827;">
<pre style="margin:0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
/* BEGIN_SEED */

int add(int a, int b) {
    return a + b;
}
</pre>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#111827;">
<pre style="margin:0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
gcc -c seed.c -o seed.o
</pre>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#081c24; color:#f8f9fa;">
<ul style="margin:0 0 0 18px; padding:0; line-height:1.5;">
<li>No <code>main</code> symbol</li>
<li>Produces <code>seed.o</code></li>
<li>Linkable into other programs</li>
<li>Use for shared logic / libraries</li>
</ul>
</td>
</tr>

<!-- Mode 2 -->
<tr>
<td style="border:1px solid #343a40; padding:10px; background-color:#2b8a3e; color:#f8f9fa; font-weight:bold; white-space:nowrap;">
Executable<br/>
<span style="font-size:12px; color:#d8f5a2;">BEGIN_SEED + BEGIN_SPEC</span>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#111827;">
<pre style="margin:0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
/* BEGIN_SEED */
/* BEGIN_SPEC */

int argc;
char **argv;

int main(int _argc, char **_argv) {
    argc = _argc;
    argv = _argv;
    return 0;
}
</pre>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#111827;">
<pre style="margin:0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
gcc seed.c -o program
</pre>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#102a19; color:#f8f9fa;">
<ul style="margin:0 0 0 18px; padding:0; line-height:1.5;">
<li>Defines standard C <code>main</code> entry point</li>
<li>Produces a standalone executable</li>
<li>Uses platform C runtime</li>
<li>Use for tools, drivers, and command-line programs</li>
</ul>
</td>
</tr>

<!-- Mode 3 -->
<tr>
<td style="border:1px solid #343a40; padding:10px; background-color:#c92a2a; color:#f8f9fa; font-weight:bold; white-space:nowrap;">
API / DLL<br/>
<span style="font-size:12px; color:#ffc9c9;">BEGIN_SEED + BEGIN_SPEC_EX</span>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#111827;">
<pre style="margin:0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
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
</pre>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#111827;">
Windows:
<pre style="margin:0 0 8px 0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
gcc -shared -o cyborg.dll seed.c
</pre>
Linux:
<pre style="margin:0; font-family:Menlo,Consolas,monospace; font-size:13px; color:#e5e5e5;">
gcc -shared -fPIC seed.c -o libcyborg.so
</pre>
</td>
<td style="border:1px solid #343a40; padding:10px; background-color:#2b1010; color:#f8f9fa;">
<ul style="margin:0 0 0 18px; padding:0; line-height:1.5;">
<li>No <code>main</code> symbol</li>
<li>Exports <code>api_entry</code> for host loading</li>
<li>Compiles to DLL (<code>.dll</code>) or SO (<code>.so</code>)</li>
<li>Use for plugin/module-style Cyborg components</li>
</ul>
</td>
</tr>

<!-- Rules -->
<tr>
<td style="border:1px solid #343a40; padding:10px; background-color:#5f3dc4; color:#f8f9fa; font-weight:bold; white-space:nowrap;">
Rules
</td>
<td colspan="3" style="border:1px solid #343a40; padding:10px; background-color:#1a1b1e; color:#f8f9fa;">
<ul style="margin:0 0 0 18px; padding:0; line-height:1.6;">
<li><code>BEGIN_SEED</code> is required in all modes.</li>
<li><code>BEGIN_SPEC</code> and <code>BEGIN_SPEC_EX</code> are mutually exclusive.</li>
<li>If <code>main</code> exists → treat as executable.</li>
<li>If <code>api_entry</code> exists and no <code>main</code> → treat as API/DLL.</li>
<li>If neither <code>main</code> nor <code>api_entry</code> exist → treat as library/object.</li>
</ul>
</td>
</tr>

</tbody>
</table>

<hr style="border:0; border-top:1px solid #444; margin:24px 0;" />

<h2 style="font-size:24px; color:#ffd166;">Language Mapping</h2>

<table>
<tr><th>AVIS Token</th><th>Meaning in C</th></tr>
<tr><td>BEGIN_SEED</td><td>Translation unit</td></tr>
<tr><td>BEGIN_SPEC</td><td>Program entry point</td></tr>
<tr><td>BEGIN_SPEC_EX</td><td>API/DLL entry point</td></tr>
<tr><td>END_*</td><td>Structural close only</td></tr>
</table>

<hr style="border:0; border-top:1px solid #444; margin:24px 0;" />

<h2 style="font-size:24px; color:#ff922b;">Canonical Compile Identity</h2>

<p style="font-size:14px; line-height:1.5;">
If <code>main</code> exists → executable<br/>
If <code>api_entry</code> exists → API/DLL<br/>
If neither exist → library/object
</p>

<p style="font-size:14px; line-height:1.5;">
This rule is <strong>canonical</strong> and should be enforced by tools, build systems, and AI.
</p>

<hr style="border:0; border-top:1px solid #444; margin:24px 0;" />

<h2 style="font-size:24px; color:#74c0fc;">Purpose</h2>

<p style="font-size:14px; line-height:1.6;">
This README is the <strong>reference compile authority</strong> for:
</p>

<ul style="font-size:14px; line-height:1.6;">
<li>AI interpreters (including Copilot)</li>
<li>Build systems</li>
<li>AVIS / Cyborg language tooling</li>
<li>Human developers</li>
</ul>

<p style="font-size:14px; line-height:1.6;">
It defines how Cyborg/AVIS seeds map to C compilation modes in a way that is explicit, deterministic, and safe to automate.
</p>

END_DOCUMENT
END_SEED
