# FAST University Discrete Structures Simulation

A Computational Framework for Courses, Prerequisites, Scheduling & Verification

This project simulates FAST University’s academic operations using Discrete Structures concepts. It models students, courses, prerequisites, scheduling rules, logical constraints, relations, and functions—while automatically checking correctness through inference, induction, and structural validation.

The system is built as a modular, scalable framework suitable for university-scale datasets.

# Collabrators:
Muhammad Hasham 24F-3039 (7-11 + raylib)

Hafsa akram 24F-3035 (4-6,12)

 # Project Goals

The aim is to demonstrate how Discrete Structures can be applied to real university operations:

✔ Verify multi-term prerequisite chains using induction

✔ Generate legal course schedules

✔ Perform logical inference on academic rules

✔ Model relationships using sets, relations, and functions

✔ Detect conflicts using relation properties

✔ Ensure correctness through proof-based verification

 # System Architecture & Modules
1️⃣ Course & Scheduling Module

Purpose:
Generate all valid semester course sequences based on prerequisites.

Core Concepts:

Recursion

Dynamic programming

Partial order constraints

Example:
If CS201 → requires CS101 & CS102, the system ensures valid sequences only.

2️⃣ Student Group Combination Module

Purpose:
Assign students to project groups, labs, and elective batches through combinatorial logic.

Core Concepts:

Sets

Combinations and permutations

Counting principles

3️⃣ Induction & Strong Induction Module

Purpose:
Automatically validate multi-level prerequisites.

Uses:

Simple induction for linear chains

Strong induction for indirect prerequisites

Example:
Advanced CS → requires Basic CS & Intro CS.
System verifies every ancestor prerequisite.

4️⃣ Logic & Inference Engine

Purpose:
Parse academic rules and verify logical consistency.

Core Concepts:

Propositional logic

Predicate logic

Modus ponens, syllogisms

Tautology detection

Example:
“If Prof. X teaches CS101 → Lab must be Lab A.”
Engine confirms whether allocation satisfies the rule.

5️⃣ Set Operations Module

Purpose:
Represent all entities (students, courses, faculty, rooms) using sets.

Supports:

Union

Intersection

Difference

Power sets

Subset checks

Example:
Find students enrolled in both CS101 ∩ MATH101.

6️⃣ Relations Module

Purpose:
Create relations such as student-course, course-room, faculty-course.

Validates:

Reflexive

Symmetric

Transitive

Equivalence relations

Partial orders

Relation composition

Example:
Detect students indirectly enrolled in conflicting courses.

7️⃣ Functions Module

Purpose:
Establish mappings and verify their mathematical properties.

Examples:

Students → Courses

Courses → Faculty

Faculty → Rooms

Checks:

Injectivity

Surjectivity

Bijectivity

Function composition

Inverse functions (if feasible)

Example:
Every course must map to exactly one faculty (injective).

8️⃣ Automated Proof & Verification Module

Purpose:
Generate machine-readable proofs to verify course rules & prerequisite chains.

Includes:

Induction proofs

Contradiction proofs

Logical deductions

Relation proofs

9️⃣ Consistency Checker Module

Purpose:
Identify scheduling conflicts and rule violations.

Detects:

Course overlap

Missing prerequisites

Overloaded students

Conflicting room assignments

🔟 Algorithmic Efficiency & Benchmarking

Purpose:
Ensure high performance for university-scale data.

Techniques:

Memoization

Recursion

Bitsets

Optimization using vectors

Dynamic programming

# CLI Interface

A clean menu-based command-line system where users can:

Add students

Add courses

Define prerequisites

Assign faculty

Run verifications

Display relations and functions

# Unit Testing & Benchmarking

Includes automated tests for:

Sets

Relations

Functions

Logic rules

Scheduling constraints

Induction-based prerequisites

Ensures correctness and performance.

# Technologies Used

C++ 
raylib 
