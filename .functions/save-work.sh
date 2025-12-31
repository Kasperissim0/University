#!/bin/bash
set -ue

# Ensure we are at the root of the git repository
cd "$(git rev-parse --show-toplevel)" || exit 1

# Require exactly one argument (the commit message)
if [ "$#" -ne 1 ]; then
  echo "Error: Invocation must include commit message" >&2
  echo "Usage: $0 \"commit message\"" >&2
  exit 1
fi

msg="$1"

# If .gitmodules exists, commit and push changes in submodules first
if [ -f ".gitmodules" ]; then
  echo "Committing and pushing submodules..."
  git submodule foreach "
    git add . 2>/dev/null || true
    if git diff --staged --quiet 2>/dev/null; then
      echo 'Submodule \$path: Nothing to commit.'
    else
      git commit -m '$msg' && echo 'Submodule \$path: Committed.' || echo 'Submodule \$path: Commit failed.'
      if git rev-parse --abbrev-ref --symbolic-full-name @{u} >/dev/null 2>&1; then
        git push && echo 'Submodule \$path: Pushed.' || echo 'Submodule \$path: Push failed.'
      else
        echo 'Submodule \$path: No upstream, skipping push.'
      fi
    fi
  "
fi

# Stage all changes in main repo (including submodule updates)
git add .

# Commit main repo
if git diff --staged --quiet; then
  echo "Main repo: Nothing to commit."
  git status --short
  exit 0
fi

git commit -m "$msg"
echo "Main repo: Committed."

# Push main repo
if git push; then
  echo "Main repo: Pushed."
else
  echo "Error: Main repo push failed." >&2
  exit 1
fi

# Clear and show status
clear
git status

exit 0