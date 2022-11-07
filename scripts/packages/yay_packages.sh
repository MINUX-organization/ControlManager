#!/bin/bash

declare -a yay_packages=(
    # Firmwares
    linux-firmware-qlogic 
    aic94xx-firmware
    wd719x-firmware 
    upd72020x-fw 

    # GPU
    ## Nvidia
    ## AMD
    lib32-opencl-legacy-amdgpu-pro
    opencl-legacy-amdgpu-pro
    opencl-amd-dev
    opencl-amd
    amdapp-sdk
    ## Intel
    intel-compute-runtime
    intel-opencl-runtime
    intel-opencl
    ## Other
    rocm-opencl-runtime
    beignet
)



