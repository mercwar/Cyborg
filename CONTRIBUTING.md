# Contributing to Cyborg

Cyborg is an **AI translation language** for sending Windows messages using
hex‑string semantics. Contributions must preserve the clarity, determinism,
and machine‑readability of the Cyborg message protocol.

## Development Guidelines

1. **AIFVS-ARTIFACT Headers**  
   All source files must include the `AIFVS-ARTIFACT` header for AI visibility.

2. **Hex Messaging Law**  
   Do not introduce ambiguous or non‑deterministic hex patterns.  
   All message definitions must remain reversible and AI‑interpretable.

3. **Windows Messaging Integrity**  
   Any new opcode, translation rule, or message mapping must be tested against
   the Cyborg Windows messaging layer.

## How to Submit

- Fork the repository  
- Create a feature branch (`git checkout -b feature/Cyborg-Enhancement`)  
- Submit a Pull Request describing the protocol improvement  

*Cyborg Law: Every message must be readable by both machine and mind.*
