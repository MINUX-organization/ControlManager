#!/bin/bash
####################################################
# This script sets up operation system for working
####################################################
set -eu -o pipefail

sudo -n true

if [ "$EUID" -ne 0 ]
    then echo "Please run as root"
    exit
fi

# Common variables
systemd_services_path="/etc/systemd/system/"
services_path="scripts/services/"

# Build

# Create services for systemd
chmod 640 -R ${services_path}
cp -R $services_path $systemd_services_path
systemctl daemon-reload
systemctl enable ControlManager






