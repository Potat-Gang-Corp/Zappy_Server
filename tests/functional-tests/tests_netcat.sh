#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to start the server
start_server() {
    echo "Starting server with command: $SERVER_CMD"
    eval "$SERVER_CMD"
    SERVER_PID=$!
    echo "Server started with PID: $SERVER_PID"
    sleep 1 # Wait a bit for the server to start
}

# Function to stop the server
stop_server() {
    if [ -n "$SERVER_PID" ]; then
        echo "Stopping server with PID: $SERVER_PID"
        kill "$SERVER_PID"
        wait "$SERVER_PID" 2>/dev/null
        echo "Server stopped"
    fi
}

# Function to execute a client test synchronously
run_client_test() {
    local command=$1
    local expected_responses=$2

    # Use netcat to send the command and capture the response
    local response=$(echo -e "$command" | timeout 10 nc localhost 8080 | tr -d '')

    echo "COMMAND: $command"
    echo -e "EXPECTED_RESPONSES: \n$expected_responses"
    echo -e "ACTUAL_RESPONSE: \n$response"

    # Compare expected and actual responses line by line
    local passed=true
    while IFS= read -r line; do
        local clean_line=$(echo "$line" | xargs)  # Trim whitespace
        if ! echo "$response" | grep -qFx "$clean_line"; then
            passed=false
            echo -e "${RED}KO${NC} (expected \"$clean_line\" not found in actual response)"
            break
        fi
    done <<< "$(echo "$expected_responses" | tr -d '')"

    if $passed; then
        echo -e "${GREEN}Test OK${NC}"
    else
        echo -e "${RED}Test failed${NC}"
    fi
}

# Main block to read and execute tests
TEST_FILE="./tests/functional-tests/tests_netcat.txt" # Adjust the path to your test file

while IFS= read -r line; do
    if [[ "$line" =~ \[([0-9]+)\] ]]; then
        TEST_NUM="${BASH_REMATCH[1]}"
        NAME=""
        SETUP=""
        CLEAN=""
        SERVER_CMD=""
        declare -a CLIENT_COMMANDS=()  # Clear previous test client commands
        declare -a CLIENT_EXPECTED_RESPONSES=()  # Clear previous test expected responses
    elif [[ "$line" =~ \[([0-9]+)-END\] ]]; then
        echo -e "\n${BLUE}Running Test $TEST_NUM${NC}: $NAME"

        # Execute setup
        eval "$SETUP"

        # Start the server
        start_server

        # Execute client tests in sequence
        for i in "${!CLIENT_COMMANDS[@]}"; do
            run_client_test "${CLIENT_COMMANDS[$i]}" "${CLIENT_EXPECTED_RESPONSES[$i]}"
        done

        # Stop the server and perform any cleanup
        stop_server
        eval "$CLEAN"
    elif [[ "$line" =~ NAME=\"(.+)\" ]]; then
        NAME="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ SETUP=\"(.+)\" ]]; then
        SETUP="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ CLEAN=\"(.+)\" ]]; then
        CLEAN="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ SERVER_CMD=\"(.+)\" ]]; then
        SERVER_CMD="${BASH_REMATCH[1]}"
    elif [[ "$line" =~ CLIENT_COMMAND=\"(.+)\" ]]; then
        CLIENT_COMMANDS+=("${BASH_REMATCH[1]}")
        CLIENT_EXPECTED_RESPONSES+=("")  # Prepare for next command/response pair
    elif [[ "$line" =~ CLIENT_EXPECTED_RESPONSE=\"(.+)\" ]]; then
        CLIENT_EXPECTED_RESPONSES[-1]+="${BASH_REMATCH[1]}"$'\n'
    fi
done < "$TEST_FILE"


