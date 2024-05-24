#!/bin/bash

print_usage() {
  echo "Usage: zappy_server -p PORT -x WIDTH -y HEIGHT -n NAME1 NAME2 ... -c CLIENTS -f FREQUENCY"
  exit 84
}

# Check for required flags
if [[ "$*" != *"-p"* || "$*" != *"-x"* || "$*" != *"-y"* || "$*" != *"-n"* || "$*" != *"-c"* || "$*" != *"-f"* ]]; then
  echo "Error: missing required flags"
  print_usage
fi

# Parse arguments
while [[ $# -gt 0 ]]; do
  case "$1" in
    -p)
      shift
      if [[ ! "$1" =~ ^[0-9]+$ ]] || (( $1 <= 0 || $1 > 65535 )); then
        echo "Error: invalid port number"
        exit 84
      fi
      ;;
    -x)
      shift
      if [[ ! "$1" =~ ^[0-9]+$ ]] || (( $1 <= 0 )); then
        echo "Error: invalid width"
        exit 84
      fi
      ;;
    -y)
      shift
      if [[ ! "$1" =~ ^[0-9]+$ ]] || (( $1 <= 0 )); then
        echo "Error: invalid height"
        exit 84
      fi
      ;;
    -n)
      shift
      if [[ "$1" =~ ^- ]]; then
        echo "Error: missing team names"
        exit 84
      fi
      ;;
    -c)
      shift
      if [[ ! "$1" =~ ^[0-9]+$ ]] || (( $1 <= 0 )); then
        echo "Error: invalid clients count"
        exit 84
      fi
      ;;
    -f)
      shift
      if [[ ! "$1" =~ ^[0-9]+$ ]] || (( $1 <= 0 )); then
        echo "Error: invalid frequency"
        exit 84
      fi
      ;;
    *)
      shift
      ;;
  esac
  shift
done

echo "Server started successfully with the given parameters"
exit 0
