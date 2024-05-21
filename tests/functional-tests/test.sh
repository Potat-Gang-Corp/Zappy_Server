#!/bin/bash

ZAPPY_SERVER="zappy_server"

if [ ! -f "$ZAPPY_SERVER" ]; then
  echo "L'exécutable $ZAPPY_SERVER n'a pas été trouvé." >&2
  exit 1
fi

while IFS= read -r line; do
  if [[ "$line" =~ ^\[[0-9]{3}\] ]]; then
    test_id=$(echo "$line" | sed 's/^\[\(.*\)\]$/\1/')
    read -r line
    test_name=$(echo "$line" | sed 's/NAME="\([^"]*\)"/\1/')
    read -r line
    setup=$(echo "$line" | sed 's/SETUP="\([^"]*\)"/\1/')
    read -r line
    clean=$(echo "$line" | sed 's/CLEAN="\([^"]*\)"/\1/')
    read -r line
    tests=""
    expected_return_code=0
    while IFS= read -r line && [[ ! "$line" =~ ^\[[0-9]{3}-END\]$ ]]; do
      tests+="$line"$'\n'
      if [[ "$line" =~ ^EXPECTED_RETURN_CODE= ]]; then
        expected_return_code=$(echo "$line" | sed 's/EXPECTED_RETURN_CODE=//')
      fi
    done

    echo "Exécution du test $test_id : $test_name"

    eval "$setup"

    while IFS= read -r cmd; do
      eval "$cmd"
      actual_return_code=$?
      if [ $actual_return_code -ne $expected_return_code ]; then
        echo "Test $test_id : KO (Return value $actual_return_code, expected $expected_return_code)"
        eval "$clean"
        exit 1
      fi
    done <<< "$tests"

    echo "Test $test_id : OK"
    
    eval "$clean"

  fi
done < tests/functional-tests/tests
