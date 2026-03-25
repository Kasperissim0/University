# AI Disclosure

As required by the OS UE guidelines, this document discloses all AI tools used during the development of this project.

---

## Tools Used

| Tool    | Model / Version         |
|---------|-------------------------|
| Claude  | claude-sonnet-4-6 (claude.ai) |
| Gemini  | Gemini 3.1 Pro (gemini.google.com) |

---

## How AI was used

AI assistance was used to help structure and extend an initial bash script into a full CLI tool. Specifically:

- Suggesting the `getopts` pattern for argument parsing
- Adding the project-root-detection loop (walking up directories)
- Structuring the logging helper to strip ANSI codes with `sed` before writing to file
- Drafting the README template

All code was reviewed, understood, and manually adjusted. The core logic — compilation loop, test execution, failure detection via `grep` — was written and verified by hand.

---

## Prompts Used

1. *"Does my test.sh script meet the requirements for the themenoffene Ausarbeitung?"*
2. *"Add CLI args and grep-based failure filtering to the script"*
3. *"Create a proper CLI command (like in the slides), add a README and AI disclosure"*
4. *"fix this formatting... instead of ✅ OK should be COMPILED SUCCESSFULLY (caps lock)... remove the doctest and color passed/failed/skipped in general text"*
5. *"utest -S outputs '20 error(s) generated' on a new line, fix compact mode"*
6. *"update all of these (README, install.sh, AI_DISCLOSURE) to match the new script"*

