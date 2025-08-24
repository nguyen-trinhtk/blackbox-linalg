# Optimized Linear System Solver & Analyzer

### Based on Wiedemann's Algorithm — STAR 2025

This repository is for a supporting tool of my **STAR 2025** research on **Solving Large Linear Systems Efficiently with Wiedemann's Algorithm**.

---

## Core Features
- C++ solver for large systems with NTL + GMP (exact arithmetic) based on Wiedemann's Algorithm
- CSV analyzer for structure, stability & runtime metrics
- Lightweight & reproducible, easy to clone and build

## Project Structure
wiedemann-analyzer/
├── docs/                   # Project documentation (abstract, report, poster)
├── external/               # External dependencies (e.g., NTL, GMP)
├── include/                # C++ header files
├── scratch/                # Research scripts & notebooks (Python, Jupyter)
├── linear-algebra-notes/   # Background notes on linear algebra prerequisites
└── references/             # Research papers, articles, and citations

## Installation & Dependencies

Requirements:

* [NTL (Number Theory Library)](https://libntl.org/)
* [GMP (GNU Multiple Precision Arithmetic Library)](https://gmplib.org/)
* g++ (C++17 or later)
---

## Build Instructions

```bash
```

---

## Usage

```bash
```

Example output:

```
```

---

## Research Poster

<p align="center">
  <img src="https://github.com/user-attachments/assets/cb5d2220-e438-4f0b-8daa-7e76103f6b7e" alt="FInPOs" width="290" height="390">
</p>

---

## References


| Matrix Size | Field GF(p) | Time (s) | Iterations |
| ----------- | ----------- | -------- | ---------- |
| 10k x 10k   | GF(2^61-1)  | 2.35     | 1024       |
| 50k x 50k   | GF(2^61-1)  | 15.8     | 4987       |

MIT License — see [LICENSE](LICENSE) for details.
