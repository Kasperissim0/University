# Create an executable shell script which can be run like: ./save-work "some message"
# And git add . && git commit -m "some message" && git push && clear && git status is performed. 
# if no/>1 args are passed throw error and do nothing

# !/bin/bash
set -ue

# Require exactly one argument (the commit message)
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 \"commit message\"" >&2
  exit 1
fi
msg="$1"

# Ensure we're inside a git repository
if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  echo "Error: current directory is not inside a git repository." >&2
  exit 1
fi

# Stage all changes
git add .

# Try to commit. If there are no changes to commit, handle gracefully.
if git commit -m "$msg" >/dev/null 2>&1; then
  echo "Committed changes."
  # Push the commit
  if git push; then
    echo "Pushed successfully."
  else
    echo "Error: 'git push' failed." >&2
    exit 1
  fi
else
  echo "Nothing to commit (or commit failed)." >&2
  git status --short
  exit 0
fi

# Clear the terminal and show the repo status
clear
git status

exit 0