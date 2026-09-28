# Matrix Operations

A C program for performing arithmetic operations on sparse matrices using the **Matrix Market Format**.

The program supports matrix addition, subtraction, multiplication, and transposition, with command-line arguments used to specify the input matrices and operation.

## Features

* Sparse matrix representation
* Matrix addition
* Matrix subtraction
* Matrix multiplication
* Matrix transposition
* Matrix Market (`.mtx`) file input
* Optional matrix output
* Makefile-based compilation and cleanup

## Technologies

* **Language:** C
* **Build System:** Make
* **Libraries & APIs:** `stdlib.h`, `stdio.h`, `string.h`, `time.h`

## How to Run

### Requirements

* GCC
* Make
* A Unix-based terminal environment such as macOS or Linux
* Input matrices in Matrix Market (`.mtx`) format

### 1. Compile the program

```bash
make
```

### 2. Run the program

```bash
./main <file1.mtx> <file2.mtx> <operation> <print>
```

### Arguments

| Argument    | Description                                                 |
| ----------- | ----------------------------------------------------------- |
| `file1.mtx` | First input matrix                                          |
| `file2.mtx` | Second input matrix                                         |
| `operation` | `addition`, `subtraction`, `multiplication`, or `transpose` |
| `print`     | `1` to print matrices, `0` to suppress output               |

For matrix transposition, the second input file should contain the same matrix.

### 3. Clean the build

```bash
make clean
```

## Technical Concepts

* Sparse matrix data structures
* Matrix arithmetic
* Dynamic memory management
* File parsing
* Command-line arguments
* Modular C programming
* Makefiles and build automation

