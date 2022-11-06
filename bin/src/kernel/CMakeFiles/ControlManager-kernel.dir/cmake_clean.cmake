file(REMOVE_RECURSE
  "libControlManager-kernel.a"
  "libControlManager-kernel.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/ControlManager-kernel.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
