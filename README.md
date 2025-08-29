# Quicksort Assignment (First-Pivot Lomuto)

This assignment provides a **standard quicksort** implementation in C that **always uses the first element as the pivot** (Lomuto-style partitioning adapted to first pivot). You will find datasets in the `datasets/` directory, run the sorter, do the profiling, and collect outputs in the `outputs/` directory.  
**Note:** Students are responsible for measuring performance.

## Project Layout

```
quicksort-assignment/
├── datasets/                 # Input files go here (e.g., sample_100.txt)
├── outputs/                  # Sorted results will be written here (auto-created)
├── src/                      # (Optional) additional sources if you split files
├── main.c                    # Entry point (reads from datasets/, writes to outputs/)
├── Makefile                  # Build rules
└── README.md
```

## Build

```bash
make
```

> The Makefile should produce your executable (named `qs`).
> If you change Makefile to output a different binary name, adjust the run command accordingly.

## Run

The program **always**:
- Reads **from `datasets/<input_file>`**
- Writes **to `outputs/<input_file>`** (same filename)

Examples:

```bash
./qs sample_100.txt
```

After running, you will see a new file in `outputs/` with the same name as the input (for better understanding the command above has already been executed and the output has been included):

```
datasets/sample_100.txt  -->  outputs/sample_100.txt
```

## Input/Output Format

- **Input**: Plain text file with integers separated by whitespace.
- **Output**: One integer per line, sorted in non-decreasing order.

## What You Need To Do

- Run the sorter as shown above.
- Perform profiling experiments (execution time, cache performance, I/O, etc.) on your own.

## Notes

- The quicksort uses the **first element** as pivot and a **Lomuto-like** partition adapted to that choice.
- The program automatically creates the `outputs/` directory if it doesn’t exist.
- If your dataset contains non-integer tokens, reading stops at the first invalid token.

## Example End-to-End

```bash
make
./qs mydata.txt
ls -lh outputs/mydata.txt
```

You should see a sorted file in `outputs/mydata.txt`.
