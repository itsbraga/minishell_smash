#!/bin/bash

BOLD='\033[1m'
RED='\033[0;31m'
ORANGE='\33[38;5;208m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
PINK='\033[38;2;255;182;193m'
WHITE='\033[0;37m'
RESET='\033[0m'

COLORS=($RED $ORANGE $YELLOW $GREEN $CYAN $BLUE $PURPLE $PINK $WHITE)

rainbow_text() {
    TEXT=$1
    for i in $(seq 0 $((${#TEXT}-1))); do
        COLOR=${COLORS[$((i%${#COLORS[@]}))]}
        echo -ne "${COLOR}${BOLD}${TEXT:$i:1}${RESET}"
    done
}

rainbow_text "$1"