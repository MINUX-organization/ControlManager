#!/bin/bash
####################################################
# This script installs all dependencies and packages
# for system
####################################################
set -eu -o pipefail

sudo -n true

if [ "$EUID" -ne 0 ]
    then echo "Please run as root"
    exit
fi

# Importing
source scripts/packages/pacman_packages.sh
source scripts/packages/yay_packages.sh

# Common variables
build_dir="build/"
working_dir=$PWD

# Upgrade system
pacman -Syu || true

# Install pacman packages for system
for i in "${pacman_packages[@]}"
do
    pacman -S "$i" || true
done

[ ! -d "$build_dir" ] && mkdir -p "$build_dir"

cp -R depends/json $build_dir
cp -R depends/yay-git $build_dir

# Build yay
cd $build_dir/yay-git
sudo -u minux bash -c "makepkg -sri"
cd $working_dir

# Build nlohmann json library
cd $build_dir/json
cmake .
make -j4
make install
cd $working_dir

# Install yay (AUR) packages for system
for i in "${yay_packages[@]}"
do
    sudo -u minux bash -c "yay -S \"$i\""
done

# TODO: Install Nvidia drivers
# TODO: Install AMD drivers







