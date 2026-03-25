# utest

A CLI tool for automatically compiling and running C++ unit tests — built for the OS UE (Betriebssysteme) exercises at Universität Wien.

## What it does

`utest` scans your current directory (or any parent) for `utest*.cpp` files, compiles them with `clang++`, runs each test binary, and reports pass/fail results. Output can be filtered, logged, and searched for failures using standard tools like `grep`.

---

## Installation

```bash
cd files
chmod +x install.sh utest
./install.sh
```

Then add `~/.local/bin` to your PATH if not already present:

```bash
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

After that, `utest` is available as a command from anywhere.

---

## Usage

```
utest [OPTIONS]
```

| Option       | Description                                      |
|--------------|--------------------------------------------------|
| `-n <nums>`  | Run only tests by number, comma-separated        |
| `-f`         | Show only failed tests                           |
| `-p`         | Show only passed tests                           |
| `-v`         | Verbose — print full output of each test         |
| `-l <file>`  | Log results to a file (ANSI codes stripped)      |
| `-s`         | Compact mode — per-file compile status           |
| `-S`         | Summary only — progress bar during compile       |
| `-u`         | Update — runs install.sh from script directory   |
| `-V`         | Print version                                    |
| `-h`         | Show help                                        |

### Examples

```bash
utest                        # compile and run all tests
utest -f                     # show only failing tests
utest -p                     # show only passing tests
utest -n 3                   # run only utest-3.cpp
utest -n 3,5,8               # run utest-3, utest-5, and utest-8
utest -v -l results.log      # verbose output, saved to file
utest -s                     # one-line-per-file compile status + summary
utest -S                     # progress bar + final pass/fail count
```

---

## Requirements

- `clang++` with C++23 support
- Bash 4+
- Test files must be named `utest*.cpp` and located in or above the current directory
- If `miniatur.cpp` exists in the same directory, it is automatically included during compilation

---

## How it works

1. **Argument parsing** via `getopts`
2. **Project root detection** — walks up from `$PWD` until it finds `utest*.cpp` files
3. **Compilation** — runs `clang++ -std=c++23 -g` on each matching file
4. **Test execution** — captures stdout/stderr and exit code per test
5. **Failure detection** — uses `grep -iE "FAIL|ERROR|❌"` on captured output
6. **Logging** — strips ANSI escape codes with `sed` before writing to file

---

## Project structure

```
files/
├── utest          # the CLI script
├── install.sh     # installs utest to ~/.local/bin
├── README.md      # this file
└── AI_DISCLOSURE.md
```