# File System Manipulation

A simple C++ command-line tool for scanning a directory (or entire drive) and organizing files based on their extensions. Built using the C++17 `std::filesystem` library.

## ⚠️ Disclaimer

This project is created **strictly for educational purposes** to learn and demonstrate file system operations in C++. It is not intended for production use.

- Always **test on sample/dummy files** before running on important directories.
- File operations such as renaming can be **destructive and difficult to reverse**.
- The author is not responsible for any data loss resulting from the use of this tool.
- Use at your own risk, and consider backing up your data before running any scan or modification features.

## Features

### Current

- **Scan Files** — Recursively scans a specified directory and all its subdirectories.
- **Group by Extension** — Organizes discovered files into a map keyed by their (lowercased) file extension.
- **Extension Count Summary** — Displays a count of how many files exist for each extension found.
- **Menu-Driven Interface** — Simple console menu to choose actions (currently: Scan Files, Exit).
- **Error Handling** — Skips inaccessible files/folders (`skip_permission_denied`) and catches filesystem errors without crashing.

### Planned (Upcoming)

- View files under a specific extension.
- Rename/change file extensions in bulk.
- Move/copy files into folders organized by extension (e.g., `Images/`, `Documents/`, `Videos/`).
- Logging of all file operations (for undo/tracking purposes).
- Interactive prompts for root path and target extensions instead of hardcoded values.
- Option to include/exclude system or permission-protected folders.

## Requirements

- C++17 or later (uses `std::filesystem`)
- A C++ compiler such as `g++`, `clang++`, or MSVC

## Building

Using g++:

```bash
g++ app.cpp -o app -std=c++17
```

## Usage

1. Run the compiled executable.
2. Set the `rootPath` variable in `main()` to the directory you want to scan.
3. Choose an option from the menu:
   - `1` — Scan Files: scans the directory and prints a summary of files grouped by extension.
   - `2` — Exit: closes the program.

## Project Structure

```
File System Manipulation/
├── app.cpp        # Main source file
└── README.md       # Project documentation
```

## Notes

- The `rootPath` is currently hardcoded in `main()` — update this to match your system before compiling/running.
- Extensions are normalized to lowercase for consistent grouping (e.g., `.TXT` and `.txt` are treated the same).
- Files without an extension are grouped under `[no extension]`.

## License

This project is open for learning and personal experimentation. No formal license has been applied yet.