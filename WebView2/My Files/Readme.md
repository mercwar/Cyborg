# WebView2 – Project Integration Files

> **Location:**  
> `Github.com/mercwar/Cyborg/WebView2/MY FILES/`

---

## Purpose

This directory contains **project-specific WebView2 integration code** used by the Cyborg system.

Unlike the `SDK FILES` directory, files here are allowed to:
- Contain helpers
- Contain handlers
- Contain glue logic
- Contain tooling support

These files sit **on top of** the pinned WebView2 SDK.

---

## What Lives Here

Typical files include:

- COM base helpers (`AddRef`, `Release`)
- Callback handler implementations
- Controller and script handlers
- Resource manifests
- Logging and diagnostics helpers

All code here:
- Is still **pure ANSI C**
- Uses **classic COM**
- Avoids C++ and WinRT
- Is tailored to Cyborg’s architecture

---

## Design Rules

- SDK headers are **never modified here**
- ABI assumptions must match `SDK FILES`
- Convenience is allowed, magic is not
- Explicit code beats clever code

---

## Relationship to SDK FILES

Think of it like this:

- **SDK FILES** → “What WebView2 is”
- **MY FILES** → “How Cyborg uses it”

Separation is mandatory.

---

## Tooling Awareness

Files in this directory are structured so that:
- Copilot can parse them
- Resource manifests can log them
- Build systems can include them deterministically

Nothing here is accidental.

---

## Who Should Touch This Directory

This directory is for:
- Cyborg developers
- System integrators
- Tooling authors

If you need to add behavior, it belongs here — not in the SDK.

---

## Final Note

This directory is where WebView2 stops being a specification  
and starts being a system component.
