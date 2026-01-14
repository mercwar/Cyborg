![MercWar Banner](Mercwar_Robo-Knight/MERCWAR_V030.png)



<!-- DARK THEME — AVIS / Cyborg Compile Modes README -->

<h1 style="font-size:36px; color:#ffe066; text-align:center; margin-bottom:6px;">
  ⚙️ AVIS / Cyborg Compile Modes
</h1>

<h2 style="font-size:20px; color:#74c0fc; text-align:center; margin-top:0; margin-bottom:20px;">
  Execution Matrix for <code>BEGIN_SEED</code>, <code>BEGIN_SPEC</code>, <code>BEGIN_SPEC_EX</code>
</h2>

<p style="font-size:15px; line-height:1.6; color:#e9ecef;">
This guide defines the <strong>AVIS / Cyborg</strong> compile model.  
It is optimized for <strong>1024×768</strong> displays and dark‑theme GitHub rendering.
</p>

<hr style="border:0; border-top:1px solid #333; margin:20px 0;" />

<h2 style="font-size:22px; color:#ff8787;">📁 File Layout</h2>


seed.c        # Contains BEGIN_SEED
spec.c        # Contains BEGIN_SPEC or BEGIN_SPEC_EX


<hr style="border:0; border-top:1px solid #333; margin:20px 0;" />

<h2 style="font-size:22px; color:#a5d8ff;">📦 Compile Modes</h2>

<table style="width:100%; border-collapse:collapse; font-size:14px;">
<thead>
<tr>
<th style="background:#0b0f19; color:#fff; padding:8px; font-size:15px;">Mode</th>
<th style="background:#0b0f19; color:#fff; padding:8px; font-size:15px;">Details</th>
</tr>
</thead>
<tbody>

<!-- MODE 1 -->
<tr>
<td style="border:1px solid #222; padding:8px; background:#0b3c4c; color:#fff; font-weight:bold;">
🟦 Library / Object  
<small>BEGIN_SEED</small>
</td>
<td style="border:1px solid #222; padding:8px; background:#0d1117; color:#e5e5e5;">
<b>Source:</b>
<pre style="margin:0; font-size:12px; background:#0d1117; color:#e5e5e5;">
/* BEGIN_SEED */
int add(int a,int b){return a+b;}
</pre>

<b>Compile:</b>  
<code>gcc -c seed.c -o seed.o</code>

<b>Behavior:</b>  
🟧 No main  
🟧 Produces seed.o  
🟧 Linkable  
</td>
</tr>

<!-- MODE 2 -->
<tr>
<td style="border:1px solid #222; padding:8px; background:#1b4d2b; color:#fff; font-weight:bold;">
🟩 Executable  
<small>BEGIN_SEED + BEGIN_SPEC</small>
</td>
<td style="border:1px solid #222; padding:8px; background:#0f1c12; color:#e5e5e5;">
<b>Source:</b>
<pre style="margin:0; font-size:12px; background:#0d1117; color:#e5e5e5;">
/* BEGIN_SEED */
/* BEGIN_SPEC */
int main(){return 0;}
</pre>

<b>Compile:</b>  
<code>gcc seed.c -o program</code>

<b>Behavior:</b>  
🟧 Standard main  
🟧 Produces executable  
</td>
</tr>

<!-- MODE 3 -->
<tr>
<td style="border:1px solid #222; padding:8px; background:#5c1a1a; color:#fff; font-weight:bold;">
🟥 API / DLL  
<small>BEGIN_SEED + BEGIN_SPEC_EX</small>
</td>
<td style="border:1px solid #222; padding:8px; background:#140c0c; color:#e5e5e5;">
<b>Source:</b>
<pre style="margin:0; font-size:12px; background:#0d1117; color:#e5e5e5;">
/* BEGIN_SEED */
/* BEGIN_SPEC_EX */
EXPORT int api_entry(){return 0;}
</pre>

<b>Compile:</b>  
Windows: <code>gcc -shared -o cyborg.dll seed.c</code>  
Linux: <code>gcc -shared -fPIC seed.c -o libcyborg.so</code>

<b>Behavior:</b>  
🟧 No main  
🟧 Exports api_entry  
</td>
</tr>

<!-- RULES -->
<tr>
<td style="border:1px solid #222; padding:8px; background:#3c1a5c; color:#fff; font-weight:bold;">
🟪 Rules
</td>
<td style="border:1px solid #222; padding:8px; background:#0d0d12; color:#e5e5e5;">
<ul style="margin:0; padding-left:18px; line-height:1.4;">
<li><code>BEGIN_SEED</code> required</li>
<li><code>BEGIN_SPEC</code> → executable</li>
<li><code>BEGIN_SPEC_EX</code> → API/DLL</li>
<li>SPEC and SPEC_EX cannot coexist</li>
</ul>
</td>
</tr>

</tbody>
</table>

<hr style="border:0; border-top:1px solid #333; margin:20px 0;" />

<h2 style="font-size:22px; color:#ffe066;">🧩 Language Mapping</h2>

| Token | Meaning |
|-------|---------|
| `BEGIN_SEED` | Translation unit |
| `BEGIN_SPEC` | Program entry |
| `BEGIN_SPEC_EX` | API/DLL entry |
| `END_*` | Structural close |

<hr style="border:0; border-top:1px solid #333; margin:20px 0;" />

<h2 style="font-size:22px; color:#ff922b;">📌 Canonical Compile Identity</h2>


main       → executable
api_entry  → API/DLL
neither    → library/object


<hr style="border:0; border-top:1px solid #333; margin:20px 0;" />

<h2 style="font-size:22px; color:#74c0fc;">🎯 Purpose</h2>

This README is the **reference compile authority** for:

- AI interpreters  
- Build systems  
- AVIS / Cyborg tooling  
- Human developers  

It ensures deterministic compile behavior across all environments.

