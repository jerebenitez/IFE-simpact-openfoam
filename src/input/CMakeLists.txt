add_library(input "")

target_link_libraries(input
  PUBLIC
    mainp
)

target_sources(input
  PUBLIC
    c_input.f90
    defnam.f90
    idntdt.f90
    lispa0.f90
    runen23.f90
)
