# Matrix Operations

This program performs arithmetic operations on sparse matrices. Supported operations include:

- Addition
- Subtraction
- Multiplication
- Transpose

The program reads matrices in **Matrix Market Format**, and requires input files with the `.mtx` extension (note: these files are not included).

## How to use the program

1. Download all of the files into a single directory
2. Open the `main.c` file in VS Code (or any text editor or IDE)
3. To compile, run:
   ```bash
   make
   ```
4. To run the program, use the following command:
   ```bash
   ./main <file1.mtx> <file2.mtx> <operation> <print>
   ```
   - Ensure you are using the correct `.mtx` files
   - `<operation>` can be `addition`, `subtraction`, `multiplication`, or `transpose`
   - If computing `transpose`, both `.mtx` files should be the same
   - `<print>` can be `0` or `1`, where `1` prints all the matrices and `0` does not print anything
5. To remove the executable from the directory, run:
   ```bash
   make clean
   ```
