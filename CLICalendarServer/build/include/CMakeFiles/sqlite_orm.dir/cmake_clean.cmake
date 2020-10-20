file(REMOVE_RECURSE
  "libsqlite_orm.a"
  "libsqlite_orm.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sqlite_orm.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
