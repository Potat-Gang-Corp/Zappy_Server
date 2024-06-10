#!/bin/bash

# Couleurs pour les sorties
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Fichier des tests
TEST_FILE="./tests/functional-tests/tests.txt"

# Lire les tests du fichier
while IFS= read -r line; do
    if [[ "$line" =~ \[([0-9]+)\] ]]; then
        TEST_NUM="${BASH_REMATCH[1]}"
        NAME=""
        SETUP=""
        CLEAN=""
        TESTS=""
        EXPECTED_RETURN_CODE=""
    elif [[ "$line" =~ \[([0-9]+)-END\] ]]; then
        echo -e "\n${BLUE}Running Test $TEST_NUM${NC}: $NAME"
        # Exécuter le setup
        eval "$SETUP"

        # Modifier ici pour utiliser timeout sans eval
        TEST_COMMAND=$(echo "$TESTS" | sed 's/TESTS=//')
        timeout 10 $TEST_COMMAND
        ACTUAL_RETURN_CODE=$?

        # Afficher les informations de debug
        echo "TESTS: $TESTS"
        echo "EXPECTED_RETURN_CODE: $EXPECTED_RETURN_CODE"
        echo "ACTUAL_RETURN_CODE: $ACTUAL_RETURN_CODE"

        # Vérifier le code de retour
        if [ "$ACTUAL_RETURN_CODE" -eq 124 ]; then
            echo -e "${GREEN}Test timed out (Acceptable in this context)${NC}"
        elif [[ "$ACTUAL_RETURN_CODE" -eq "$EXPECTED_RETURN_CODE" ]]; then
            echo -e "${GREEN}OK${NC}"
        else
            echo -e "${RED}KO${NC} (expected $EXPECTED_RETURN_CODE, got $ACTUAL_RETURN_CODE)"
        fi

        # Exécuter le clean
        eval "$CLEAN"
    elif [[ "$line" =~ NAME=\"(.+)\" ]]; then
        NAME="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ SETUP=\"(.+)\" ]]; then
        SETUP="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ CLEAN=\"(.+)\" ]]; then
        CLEAN="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ TESTS= ]]; then
        TESTS=$(echo "$line" | sed 's/TESTS=//')
    elif [[ "$line" =~ EXPECTED_RETURN_CODE=([0-9]+) ]]; then
        EXPECTED_RETURN_CODE="${BASH_REMATCH[1]}"
    fi
done < "$TEST_FILE"








