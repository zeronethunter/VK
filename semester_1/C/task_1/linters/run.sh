#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck . -i./build/ --enable=all --force --inconclusive --error-exitcode=1 -I ./subnet_lib --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ./src/*.c ./subnet_lib/*.c ./subnet_lib/*.h -warnings-as-errors=* -extra-arg=-std=c99 -- -I./subnet_lib" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c,h --filter=-readability/casting ./subnet_lib/* ./src/*" "Can't open for reading"

print_header "SUCCESS"