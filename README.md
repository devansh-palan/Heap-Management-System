# Heap Management System

## Overview
This project implements a **dynamic heap management system** using **First Fit** and **Best Fit** strategies with linked lists to manage free and allocated memory blocks. The system simulates a heap of fixed size (100 bytes) and allows users to allocate and free memory dynamically.

## Features
- **Memory Allocation:**
  - **First Fit:** Allocates the first available block that is large enough.
  - **Best Fit:** Allocates the smallest block that is large enough.
- **Memory Deallocation:**
  - Frees allocated memory blocks and merges adjacent free blocks.
- **Heap Management:**
  - Maintains a **free list** and **allocated list** using linked lists.
- **User Interface:**
  - Provides options to allocate, free, and view memory blocks.

## Data Structures Used
- **Singly Linked List:**
  - Manages the free memory blocks.
  - Manages the allocated memory blocks.
- **Heap Array (`heap[100]`):**
  - Simulates a fixed-size memory space.

## File Structure
- `2.c` - The main source code implementing heap management.

## Compilation & Execution
### Prerequisites
- A C compiler (GCC recommended)

### Compilation
```sh
gcc 2.c -o heap_manager
```

### Running the Program
```sh
./heap_manager
```

## Usage Instructions
1. **Select an allocation strategy:**
   - `1` for First Fit
   - `2` for Best Fit
2. **Enter the block size** to allocate memory.
3. **Free memory** by entering the starting address.
4. **View the current state** of allocated and free lists.
5. **Exit the program** when done.

## Example Output
```
Choose an option:
1. First Fit
2. Best Fit
3. Free Memory
4. Show Lists
5. Exit
1
Enter block size:
10
Allocated at index: 0 (Actual Address: 0x7ffc6b8a)
```

## Future Enhancements
- Extend the heap size dynamically.
- Use **double linked lists** for better merging efficiency.

## License
This project is licensed under the MIT License.

