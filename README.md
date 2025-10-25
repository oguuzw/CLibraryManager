## ClibraryManager - Book Library (C)

ClibraryManager is a small C example that reads book records from a text file (`kitaplar.txt`), builds a queue, and then converts that queue into a circular doubly-linked list sorted by ISBN. The program provides a simple menu with operations such as loading from file, deleting by ISBN, searching (by genre and length), sorting (by author), and computing library statistics (total books, total pages, average pages).

## Files
- `1.c` : Main source file. Implements a queue (`kuyruk`) and a circular doubly-linked list (`node`) and their operations.
- `kitaplar.txt` : Input file containing book records (place in the project root).
- `README.md` : This file.

## Build and Run (Windows - PowerShell)
1. Open PowerShell and change into the project directory (example path):

```powershell
cd 'C:\Users\oguuz\OneDrive\Desktop\ClibraryManager'
```

2. Compile with GCC (MinGW or equivalent must be installed):

```powershell
gcc 1.c -o kutuphane.exe
```

3. Run the program:

```powershell
.\kutuphane.exe
```

Choose option 1 from the menu to load records from `kitaplar.txt` and list them.

## `kitaplar.txt` format
Each line is a book record with fields separated by the pipe character `|` in this order:

ISBN|Title|Author|Genre|PageCount

Example:

```
9786050950953|Simyacı|Paulo Coelho|Roman|184
9789750724556|Kürk Mantolu Madonna|Sabahattin Ali|Klasik|160
```

Note: The current code reads ISBN as a `double` using `fscanf` with `%lf`. It is safer to store ISBN as a string (e.g. `char ISBN[32];`) to avoid precision and formatting issues.

## Features
- Build queue from file
- Convert queue to an ISBN-sorted circular doubly-linked list
- Menu operations: load (from file), delete (by ISBN), search (by genre and length), sort (by author), library statistics
- Simple console listing output

## Known Issues and Caveats
- The `siralama()` (sorting) function in `1.c` needs careful handling of node pointer assignments when swapping nodes in a circular doubly-linked list. Edge cases such as one- or two-element lists and updating the `listeIlk` pointer must be handled.
- `dosyadanKuyrugaEkle()` uses `fscanf` and may dereference `temp` when scanning fails; this can lead to segmentation faults on malformed input. Add input validation and free any allocated node when scanning fails.
- Some operations lack sufficient NULL checks and proper `free()` usage; for larger datasets this may cause memory leaks or invalid memory access. Add cleanup routines to free the queue and list on exit.

## Recommended Fixes (short list)
- Change ISBN to a string type (e.g. `char ISBN[32];`) and adapt `fscanf` accordingly (e.g. `%31[^|]|...`).
- In `dosyadanKuyrugaEkle()`, after `malloc`, always check `fscanf` return; if it fails, `free()` the node and handle the error safely.
- Add NULL checks before accessing `next`/`prev` when converting the queue to the list and during delete/swap operations.
- Free all allocated nodes for both queue and list on program exit to avoid memory leaks.

## Contributing
1. Fork the repository.
2. Create a branch (e.g. `fix/readme-and-fixes`).
3. Make changes, run tests, and open a pull request describing your changes.

---
This README was produced from the project sources. If you want, I can also apply the suggested code fixes (safe parsing, freeing on error, change ISBN to string, and verify the sorting routine) and run a quick compile test.
