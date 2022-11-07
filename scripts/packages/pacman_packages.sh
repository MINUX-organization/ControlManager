#!/bin/bash

declare -a pacman_packages=(
    # System
    linux-zen-headers
    linux-headers
    base-devel
    linux
    dbus
    yajl

    # Utility
    dmidecode-tool
    dmidecode

    # Xorg
    xorg-xclock
    xorg-server 
    xorg-xinit
    xorg-apps
    xterm
    xorg

    # Video drivers
    xf86-video-nouveau
    xf86-video-sisusb
    xf86-video-voodoo
    xf86-video-amdgpu
    xf86-video-amdgpu
    xf86-video-dummy
    xf86-video-fbdev
    xf86-video-intel
    xf86-video-vesa
    xf86-video-ati

    # Build
    extra-cmake-modules
    cmake
    boost
    curl
    dpkg

    # GPU
    ## Nvidia
    lib32-nvidia-utils 
    nvidia-settings
    nvidia-libgl
    nvidia-prime
    nvidia-utils
    nvidia-dkms 
        # nvidia
    ## AMD
    lib32-mesa 
    ## Intel
    lib32-vulkan-intel 
    vulkan-intel 
    ## Other
    lib32-vulkan-icd-loader
    vulkan-icd-loader 

    # GPU Utils
    ## Nvidia
    lib32-opencl-nvidia
    opencl-nvidia
    cuda-tools
    cuda
    ## AMD
    lib32-opencl-mesa
    opencl-mesa
    ## Intel
    intel-compute-runtime
    ## Other
    opencl-headers
    ocl-icd
)

