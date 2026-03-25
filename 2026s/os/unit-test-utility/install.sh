#!/bin/bash

# =============================================================================
# install.sh - Installs `utu` as a system-wide CLI command
# =============================================================================

CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

INSTALL_DIR="$HOME/.local/bin"
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

echo -e "${CYAN}Installing unit test utility (utu)...${NC}"

# Create ~/.local/bin if it doesn't exist
mkdir -p "$INSTALL_DIR"

# Symlink the script instead of copying it
ln -sf "$SCRIPT_DIR/utest" "$INSTALL_DIR/utu"
ln -sf "$SCRIPT_DIR/utest" "$INSTALL_DIR/ut"
ln -sf "$SCRIPT_DIR/utest" "$INSTALL_DIR/utest"
chmod +x "$INSTALL_DIR/utu" "$INSTALL_DIR/ut" "$INSTALL_DIR/utest"

# Get version from script
VERSION=$(grep "^VERSION=" "$SCRIPT_DIR/utest" | cut -d'"' -f2)

# Check if ~/.local/bin is on PATH
if [[ ":$PATH:" != *":$INSTALL_DIR:"* ]]; then
    echo ""
    echo -e "${CYAN}⚠️  $INSTALL_DIR is not in your PATH.${NC}"
    echo -e "Add this line to your ~/.bashrc or ~/.zshrc:"
    echo ""
    echo -e '    export PATH="$HOME/.local/bin:$PATH"'
    echo ""
    echo -e "Then run:  source ~/.bashrc"
fi

echo -e "${GREEN}✅ utu/ut/utest symlinked to $INSTALL_DIR/${NC}"
echo -e "😎 Latest Version: ${RED}$VERSION${NC}"
