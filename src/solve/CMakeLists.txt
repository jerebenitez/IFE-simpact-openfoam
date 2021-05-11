add_library(solve "")

target_link_libraries(solve
  PUBLIC
    mainp./mainp
    input
)

target_sources(solve
  PUBLIC
    colsol.f90
    ensmat.f90
    lump_mass.f90
    masaux.f90
    masmtx.f90
    reduce_mass.f90
    renum0.f90
    renum1.f90
    renum2.f90
    renum3.f90
    renum4.f90
    renumn.f90
    ubicmx.f90
)