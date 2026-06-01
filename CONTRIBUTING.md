
# Cyborg & Constellation: Master Repository Guide

Welcome to the central gateway of the **Mercwar Ecosystem**.

This repository contains **Cyborg**—a deterministic AI translation language for Windows message communication—and **Constellation**, its official distributed runtime, validation pipeline, and simulation network.

> **Cyborg Law**
> *Every message must be readable by both machine and mind.*

---

## 🌌 Overview & Architecture

Cyborg bridges low-level Windows messaging layers with AI-assisted interpretation by representing communication through structured, reversible hexadecimal patterns. Constellation serves as the operational backbone, ensuring all message routing, opcode behaviors, and translations are validated in a sandboxed cluster before deployment.

```text
┌──────────────────────────┐
│      Cyborg Message      │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│    Protocol Translator   │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│    AVIS-Stage Validator  │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│   Constellation Nodes    │
└────────────┬─────────────┘
             │
             ▼
┌──────────────────────────┐
│   Windows Message Layer  │
└──────────────────────────┘
```

### Core Design Principles

* **Determinism**: Identical input always produces identical output.
* **Reversibility**: All translations must support lossless round-trip reconstruction.
* **Clarity**: Message streams remain readable by both human maintainers and AI tooling.
* **Compatibility**: Full alignment with Windows messaging standards and runtime behavior.

---

## ⚙️ The Constellation Pipeline

Data processing flows through six automated intelligence stages:

1. **Scanner** (`constellation.c`)
   Discovers subsystem versions, execution parameters, and local runtime state.

2. **Reducer** (`constellation_reduce.c`)
   Normalizes raw stream inputs and removes non-deterministic artifacts.

3. **Autobuild** (`constellation_autobuild.c`)
   Compiles schema configurations into validated `.bin` artifacts.

4. **Linker** (`constellation_linker.c`)
   Merges transactional fragments into a unified `intelligence.model`.

5. **Validator** (`constellation_validator.c`)
   Enforces AVIS compliance and protocol integrity constraints.

6. **Publisher** (`constellation_publisher.c`)
   Packages and distributes telemetry to the `AVIS-Datalake`.

---

## 📜 Development Laws

All contributors must comply with the following protocol rules:

### 1. Hex Messaging Law

* No ambiguous, collision-prone, or non-deterministic hex patterns.
* All transformations must remain fully reversible.

### 2. AIFVS Artifact Compliance

* Every source file must include an `AIFVS-ARTIFACT` header block.
* Required for indexing, traceability, and automated validation systems.

### 3. Messaging Integrity Rule

* Any modification to opcode logic, parsing systems, or translation rules must remain consistent with the Windows messaging layer.

---

## 🚀 Getting Started & Local Simulation

### 1. Installation

Clone the repository locally:

```bash
git clone https://github.com/mercwar/Constellation.git
cd Constellation
```

Follow the build instructions in the documentation folder to install required tooling and compile native binaries.

---

### 2. Configure Your Network Cluster

Define topology and validation behavior in:

`config/constellation.json`

```json
{
  "nodes": [
    {
      "name": "controller-01",
      "host": "127.0.0.1",
      "port": 8080
    }
  ],
  "roles": [
    "validator",
    "translator",
    "ingress",
    "egress"
  ],
  "test_vectors": "path/to/test/message/vectors"
}
```

---

### 3. Launch Local Constellation

1. Start the **Constellation Controller** using your config file.
2. Spawn one or more **Worker Nodes**.
3. Verify translation + validation pipelines are active.
4. Use CLI tools in `/tools` to inject hex streams and inspect output traces.

---

## 🧪 Testing Guidelines

Testing is mandatory for all protocol changes.

### Validation Strategies

* **Unit Tests**: Validate opcode-level correctness and structural rules.
* **Integration Tests**: Verify multi-node routing and cluster stability.
* **Regression Coverage**: Every bugfix must include reproducible test vectors.

### Cluster Stability Rules

* Synchronize clocks across nodes to prevent timestamp drift.
* Enforce deterministic seeds for all test vectors.
* Log and preserve all failing hex streams as future test cases.

---

## 🐚 Shell AVI Development

Shell AVIs are automation scripts used to generate, transform, and test Cyborg messages in shell environments.

### Learning Path

1. **Analyze**
   Study tools in `/tools` and `/examples`.

2. **Sandbox**
   Build a script that:

   * Reads hex from `stdin`
   * Validates against schema
   * Routes output to a Constellation worker

3. **Pipeline Mastery**
   Use standard utilities:
   `cat`, `jq`, `sed`, `awk`

4. **CI Integration**
   Ensure:

   * Proper logging
   * Reliable exit codes
   * Automated deployment compatibility

---

## 📂 Repository Organization

| Directory Path   | Purpose                              |
| ---------------- | ------------------------------------ |
| `Constellation/` | Core engine and pipeline schema      |
| `robots/`        | Automated cluster entities           |
| `sources/`       | Raw datasets and historical assets   |
| `maps/`          | Network topology and routing graphs  |
| `queries/`       | Data filtering and extraction logic  |
| `tools/`         | Build scripts and automation AVIs    |
| `tabs/`          | Interface specs and engineering logs |
| `images/`        | Architecture diagrams and visuals    |
| `universal/`     | State tracking and global maps       |

---

## 🤝 Collaboration & Support

* **Community**: Strategy discussions and datasets are shared via the Mercwar community network.
* **Issues**: Report bugs or protocol violations via repository issue tracking.

  * Always include a reproducible test vector.

---

# ⚖️ Legal Notice & License

### Ownership

This repository and all associated frameworks (including Cyborg, Constellation, and derived systems) are part of the **Mercwar Ecosystem** unless otherwise stated.

### Usage Rights

Permission is granted to:

* Clone and study the repository
* Modify code for personal or research use
* Run local simulations and test environments

### Restrictions

You may NOT:

* Redistribute modified versions as proprietary software
* Remove attribution to the Mercwar Ecosystem
* Use this system for unlawful, harmful, or malicious automation
* Misrepresent derivative work as original authorship

### No Warranty

This software is provided **“as is”**, without warranty of any kind, express or implied. The authors are not responsible for:

* Data loss
* System instability
* Misuse of protocol logic
* Runtime failures in production environments

### Liability Limitation

Under no circumstances shall the authors or contributors be liable for any damages arising from use or misuse of this system.

### Bottom line: Contribution is user level
