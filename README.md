# GDSL — Generalised Data Structures Library

**Author:** Sarthak Salunke  
**Date:** 4/7/2024  
**Language:** C++17

GDSL is a single-header C++ library containing reusable implementations of common data structures and algorithms. The complete library implementation is in `GDSL.h`; `main.cpp` is a separate demonstration program.

## Project structure

```text
Generalised-Data-Structures-Library/
├── GDSL.h
├── main.cpp
├── README.md
├── .gitignore
└── LICENSE (add a license if/when selected)
```

## Features

- Singly linear linked list
- Singly circular linked list
- Doubly linear linked list
- Doubly circular linked list
- Stack
- Queue
- Dynamic array wrapper
- Linear, bidirectional and binary search
- Bubble, optimised bubble, selection and insertion sort
- Binary search tree with traversals and node counts
- Singly linked-list operations: search, first/last occurrence, middle-element detection, cycle detection and reverse

## Requirements

- A C++17-compatible compiler (GCC, Clang or MSVC)
- No third-party dependencies

## Compile and run the demonstration

From the project directory:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 main.cpp -o gdsl_demo
./gdsl_demo
```

On Windows Command Prompt:

```bat
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 main.cpp -o gdsl_demo.exe
gdsl_demo.exe
```

## Use GDSL in your own program

Keep `GDSL.h` in the same directory as your source file, or add its directory to your compiler include path.

```cpp
#include <iostream>
#include "GDSL.h"

int main()
{
    GDSL::Stack<int> values;
    values.Push(10);
    values.Push(20);
    values.Display();

    return 0;
}
```

Compile your program:

```bash
g++ -std=c++17 your_program.cpp -o your_program
```

## API notes

- Linked-list positions are **1-based**.
- Searching functions return **zero-based indexes**, or `-1` when the value is not found.
- `BinarySearch` requires its input vector to be sorted in ascending order.
- `SinglyLL::MiddleElement(result)` returns `false` for an empty list. For an even-sized list, it writes the second (upper) middle element to `result`.
- `SinglyLL::CheckLoop()` uses Floyd's cycle-detection algorithm and returns `true` if a cycle is detected.
- `BinarySearchTree` ignores duplicate values.
- Sorting and searching algorithms operate on `std::vector<T>`.
- The library uses templates; keep template implementations in the header.

## Design notes

- All library names are inside the `GDSL` namespace.
- The library has no `main()` function. The demonstration program is separate.
- Owning linked-list and tree classes release their dynamically allocated nodes in destructors.
- Copying is disabled for the pointer-owning linked-list and tree classes to prevent accidental shallow copies.

## Notes about the source exercises

The C/C++ exercises supplied for this project were used as source material and adapted into reusable C++ components. Bugs and edge cases were corrected during the conversion. The Java Employee DBMS exercise is a separate Java project and is not included in this C++ library.

## License

No license has been selected yet. Add a license file before publishing if you want to specify permissions for reuse, modification and distribution.
