#!/bin/bash
docker-compose up -d
docker ps -a
docker exec -it dockerfiledir_alpine_1 sh