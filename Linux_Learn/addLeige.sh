#!/bin/bash
adduser leige
usermod -aG sudo leige
echo Enter any key to continue
read -n 1 -s
cat /etc/passwd
cat /etc/group