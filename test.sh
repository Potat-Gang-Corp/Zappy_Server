#!/bin/bash

# Exécuter valgrind sur le serveur
valgrind --leak-check=full --track-origins=yes --show-reachable=yes -v ./zappy_server -p 8080 -x 10 -y 10 -n name1 name2 -c 10 -f 1000 &

# Attendre que le serveur soit lancé
sleep 5

# Se connecter au serveur avec nc et envoyer GRAPHIC
{ echo "GRAPHIC"; cat; } | nc localhost 8080
