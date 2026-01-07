#!/bin/bash
set -ue

# --- Ensure we are at the root of the git repository ---
cd "$(git rev-parse --show-toplevel)" || exit 1

# --- Colors ---
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'

# --- Get commit message (optional argument or prompt) ---
if [ "$#" -eq 0 ]; then
    echo -e "${CYAN}No commit message provided.${NC}"
    read -p "Enter commit message: " msg
    [ -z "$msg" ] && { echo "Error: Commit message cannot be empty." >&2; exit 1; }
elif [ "$#" -eq 1 ]; then
    msg="$1"
else
    echo "Error: Too many arguments" >&2
    echo "Usage: $0 [\"commit message\"]" >&2
    exit 1
fi

# --- Function to confirm force push ---
confirm_force_push() {
    local context="$1"
    echo -e "${MAGENTA}⚠️  WARNING: Force push requested for $context${NC}"
    read -p "Are you SURE you want to force push? (type 'yes' to confirm): " confirm1
    if [ "$confirm1" != "yes" ]; then
        echo "Force push cancelled."
        return 1
    fi
    read -p "FINAL CONFIRMATION: Force push will overwrite remote. Type 'FORCE' to proceed: " confirm2
    if [ "$confirm2" != "FORCE" ]; then
        echo "Force push cancelled."
        return 1
    fi
    return 0
}

# --- Function to process a single submodule ---
process_submodule() {
    local path="$1"
    [ -d "$path" ] || { echo "Skipped submodule '$path' (directory not found)"; return; }
    pushd "$path" >/dev/null || { echo "Failed to cd into '$path'"; return 1; }

    local name="Submodule: $(basename "$path")"
    local box_width=46
    local left_padding=$(( (box_width - ${#name}) / 2 ))
    local right_padding=$(( box_width - ${#name} - left_padding ))
    
    echo -e "\n${BLUE}╔══════════════════════════════════════════════╗${NC}"
    printf "${BLUE}║${NC}${YELLOW}%${left_padding}s%s%${right_padding}s${NC}${BLUE}║${NC}\n" "" "$name" ""
    echo -e "${BLUE}╚══════════════════════════════════════════════╝${NC}"

    git add . 2>/dev/null || true

    if git diff --staged --quiet 2>/dev/null; then
        echo "  -> Nothing to commit."
    else
        echo -e "  Default message: ${GREEN}\"$msg\"${NC}"
        read -p "  Press ENTER for default, or enter new message: " submodule_msg
        [ -z "$submodule_msg" ] && submodule_msg="$msg"

        if git commit -m "$submodule_msg"; then
            echo "  -> Committed: \"$submodule_msg\""
        else
            echo "  -> Commit failed."
            popd >/dev/null
            return 1
        fi

        if git rev-parse --abbrev-ref --symbolic-full-name @{u} >/dev/null 2>&1; then
            if git push 2>/dev/null; then
                echo '  -> Pushed.'
            else
                echo '  -> Push failed.'
                read -p "  Retry with force-with-lease? (y/n): " retry_choice
                if [[ "$retry_choice" =~ ^[Yy]$ ]]; then
                    if confirm_force_push "$(basename "$path")"; then
                        git push --force-with-lease && echo '  -> Force pushed.' || echo '  -> Force push failed.'
                    fi
                fi
            fi
        else
            echo '  -> No upstream branch. Skipping push.'
        fi
    fi

    popd >/dev/null
}

# --- Function to commit & push main repo ---
commit_main_repo() {
    local name="Main Repository"
    local box_width=46
    local left_padding=$(( (box_width - ${#name}) / 2 ))
    local right_padding=$(( box_width - ${#name} - left_padding ))
    
    echo -e "\n${RED}╔══════════════════════════════════════════════╗${NC}"
    printf "${RED}║${NC}%${left_padding}s%s%${right_padding}s${RED}║${NC}\n" "" "$name" ""
    echo -e "${RED}╚══════════════════════════════════════════════╝${NC}"

    git add .

    if git diff --staged --quiet; then
        echo "Main repo: Nothing to commit."
    else
        echo -e "  Default message: ${GREEN}\"$msg\"${NC}"
        read -p "  Press ENTER for default, or enter new message: " main_msg
        [ -z "$main_msg" ] && main_msg="$msg"
        
        if git commit -m "$main_msg"; then
            echo "Main repo: Committed with message \"$main_msg\""
        else
            echo "Main repo: Commit failed."
            exit 1
        fi
    fi

    if git rev-parse --abbrev-ref --symbolic-full-name @{u} >/dev/null 2>&1; then
        if git push 2>/dev/null; then
            echo "Main repo: Pushed."
        else
            echo "Main repo: Push failed."
            read -p "  Retry with force-with-lease? (y/n): " retry_choice
            if [[ "$retry_choice" =~ ^[Yy]$ ]]; then
                if confirm_force_push "main repository"; then
                    if git push --force-with-lease; then
                        echo "Main repo: Force pushed."
                    else
                        echo "Error: Main repo force push failed." >&2
                        exit 1
                    fi
                fi
            else
                echo "Error: Main repo push failed and not retried." >&2
                exit 1
            fi
        fi
    else
        echo "Main repo: No upstream branch. Skipping push."
    fi
}

# Helper function to print a line with the right border aligned
print_row() {
    local content="$1"
    local border_color="$2"
    # Strip ANSI color codes to calculate visible length for alignment
    local clean_content=$(echo -e "$content" | sed 's/\x1b\[[0-9;]*m//g')
    local len=${#clean_content}
    local width=78  # Total inner width
    local pad=$((width - len))

    if [ $pad -lt 0 ]; then pad=0; fi
    local spaces=$(printf "%${pad}s")
    
    echo -e "${border_color}║${NC}${content}${spaces}${border_color}║${NC}"
}

# --- Function to print repository summary ---
print_repo_summary() {
    local repo_name="$1"
    local repo_path="$2"
    local is_main="$3"
    
    # Choose border color based on repo type
    local border_color="${BLUE}"
    if [ "$is_main" = "true" ]; then
        border_color="${RED}"
    fi
    
    pushd "$repo_path" >/dev/null || return

    # --- Header ---
    echo -e "${border_color}╔══════════════════════════════════════════════════════════════════════════════╗${NC}"
    
    # Center the title
    clean_title=" $repo_name "
    left_pad=$(( (78 - ${#clean_title}) / 2 ))
    title_spaces=$(printf "%${left_pad}s")
    print_row "${YELLOW}${title_spaces}${repo_name}${NC}" "$border_color"
    
    echo -e "${border_color}╟──────────────────────────────────────────────────────────────────────────────╢${NC}"

    # --- Status Line ---
    if [ -z "$(git status --porcelain)" ]; then
        print_row " ${CYAN}Status:${NC}      ${GREEN}Clean${NC}" "$border_color"
    else
        print_row " ${CYAN}Status:${NC}      ${RED}Modified${NC}" "$border_color"
    fi

    # --- Recent Commits & Changes ---
    print_row " ${CYAN}Recent Commits:${NC}" "$border_color"

    git log -n 5 --format="%h %s" | while read -r hash msg; do
        # 1. Print Commit Hash and Message
        print_row "               ${YELLOW}${hash}${NC} | ${RED} ${msg}" "$border_color"

        # 2. Print File Stats
        git show --format="" --stat=55 "$hash" | head -n 5 | while IFS= read -r stat_line; do
            if [ -n "$stat_line" ]; then
                 print_row "                  ${stat_line}" "$border_color"
            fi
        done
    done

    echo -e "${border_color}╚══════════════════════════════════════════════════════════════════════════════╝${NC}"
    echo

    popd >/dev/null
}

# --- Step 1: Process submodules FIRST (if any) ---
if [ -f ".gitmodules" ]; then
    echo "Processing submodules..."
    
    # Build array of submodule paths
    submodule_paths=()
    while IFS= read -r key; do
        path=$(git config -f .gitmodules "$key")
        submodule_paths+=("$path")
    done < <(git config -f .gitmodules --name-only --get-regexp 'submodule\..*\.path')
    
    # Process each submodule
    for path in "${submodule_paths[@]}"; do
        process_submodule "$path"
    done
fi

# --- Step 2: Commit & push main repo LAST ---
commit_main_repo

# --- Step 3: Print final summary ---
echo ""
echo "--- Main Repository Status ---"
git status
echo

# --- Step 4: Print summaries ---
echo "--- Repository Summaries ---"
echo

# Main repository summary
print_repo_summary "Main Repository" "." "true"

# Submodule summaries
if [ -f ".gitmodules" ]; then
    for path in "${submodule_paths[@]}"; do
        [ -d "$path" ] || continue
        print_repo_summary "Submodule: $(basename "$path")" "$path" "false"
    done
fi

exit 0