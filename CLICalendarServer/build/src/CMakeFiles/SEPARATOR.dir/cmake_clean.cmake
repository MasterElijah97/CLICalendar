file(REMOVE_RECURSE
  "libSEPARATOR.a"
  "libSEPARATOR.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/SEPARATOR.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
