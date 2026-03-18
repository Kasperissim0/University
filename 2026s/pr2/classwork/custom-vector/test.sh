#!/bin/bash

# --- COLORS ---
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # NO COLOR

# ENSURE WE ARE IN THE DIRECTORY WHERE THE SCRIPT IS LOCATED
cd "$(dirname "$0")" || exit 1

# CREATE THE LOCAL TESTS DIRECTORY
mkdir -p tests

# COMPILATION FLAGS
# USING C++23 AS REQUESTED.
FLAGS="-fcolor-diagnostics -fansi-escape-codes -std=c++23 -g"

# BUILD ALL UTEST FILES IN THIS DIRECTORY
for f in utest*.cpp; 
do
    echo -e "${CYAN}--- COMPILING: $f ---${NC}"
    TNAME=$(basename "$f" .cpp)
    
    # INCLUDE MINIATUR.CPP IF IT EXISTS, AS SOME TESTS (LIKE UTEST-8) DEPEND ON IT.
    EXTRA_SOURCES=""
    if [[ -f "miniatur.cpp" ]]; then
        EXTRA_SOURCES="miniatur.cpp"
    fi

    clang++ $FLAGS "$f" $EXTRA_SOURCES -o "tests/$TNAME"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ ERROR: FAILED TO COMPILE $f${NC}"
    fi
done

# RUN THE BUILT TESTS
echo ""
echo -e "${YELLOW}--- RUNNING ALL TESTS ---${NC}"
for t in tests/utest*; do
    if [ -x "$t" ]; then
        echo "------------------------------------------------"
        echo -e "${GREEN}🚀 EXECUTING: $t${NC}"
        ./"$t"
        echo ""
    fi
done
