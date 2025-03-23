#!/bin/bash

# Check if the correct number of arguments is provided
if [ $# -lt 2 ]; then
    echo "Usage: $0 <timeout_duration> <command> [args...]"
    exit 1
fi

TIMEOUT_DURATION=$1  # First argument: timeout duration (seconds)
shift                # Remove first argument, leaving only the command
COMMAND="$@"         # Capture the rest as the command

# Run the command with timeout
timeout "$TIMEOUT_DURATION" bash -c "$COMMAND"
EXIT_CODE=$?  # Capture the exit code

# Check if the command was killed due to timeout
if [ $EXIT_CODE -eq 124 ]; then
    exit 0  # Timeout occurred, return 0
else
    exit $EXIT_CODE  # Return the actual exit code of the command
fi
