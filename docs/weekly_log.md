### Fall W5: October 23, 2025
Done: 
- Examples for DET problem
- Explore properties of PreConCyc (and why use)
- Probability of non-derogatory

```graph TD
  %% Define nodes in three columns
  
  %% Column 1 (color: #f9f, a pinkish color)
  style MinPoly fill:#f9f,stroke:#333,stroke-width:1px
  style LinSolve0 fill:#f9f,stroke:#333,stroke-width:1px
  style Singularity fill:#f9f,stroke:#333,stroke-width:1px
  style BlockWiedemann fill:#f9f,stroke:#333,stroke-width:1px

  MinPoly["MinPoly (scalar Wiedemann)"]
  LinSolve0["LinSolve0"]
  Singularity["Singularity"]
  BlockWiedemann["Block Wiedemann"]

  LinSolve0 --> Singularity
  LinSolve0 --> BlockWiedemann

  %% Column 2 (color: #9cf, a bluish color)
  style RxR fill:#9cf,stroke:#333,stroke-width:1px
  style SxS fill:#9cf,stroke:#333,stroke-width:1px
  style Nil fill:#9cf,stroke:#333,stroke-width:1px
  style Cyc fill:#9cf,stroke:#333,stroke-width:1px
  style CycNil fill:#9cf,stroke:#333,stroke-width:1px

  RxR["RxR"]
  SxS["SxS"]
  Nil["Nil"]
  Cyc["Cyc"]
  CycNil["CycNil"]

  %% Column 3 (color: same as column 1)
  style LinSolve1 fill:#f9f,stroke:#333,stroke-width:1px
  style Rank fill:#f9f,stroke:#333,stroke-width:1px
  style Det fill:#f9f,stroke:#333,stroke-width:1px

  LinSolve1["LinSolve1"]
  Rank["Rank"]
  Det["Det"]

  %% Connections

  MinPoly --> Cyc
  Cyc --> Det

  BlockWiedemann --> Nil
  Nil --> LinSolve1

  Rank --> RxR
  RxR --> LinSolve1

  Singularity --> SxS
  SxS -- "binary search" --> Rank

  MinPoly --> CycNil
  CycNil --> Rank
```

To-do:

### Fall W4: October 16, 2025
Done: 
- Run through paper, section I-III
- Note resource limitations
- Monte Carlo vs Las Vegas tradeoffs
- Cover different types of problems, preconditioners
- High-level idea of PreConInd proofs

To-do:
- Give examples
- Resource-aware, understand tradeoffs/limitations
- Relation between problems & preconditioners
