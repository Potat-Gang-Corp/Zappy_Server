#!/bin/sh

# Adresse IP et port du serveur

{
    sleep 1
    echo "name1"
    echo "Forward"
    echo "Left"
    echo "Forward"
    echo "Left"

    while true; do
        sleep 1
    done
} | nc localhost 8080