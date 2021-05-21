add_library(solve "")

target_link_libraries(solve
  PUBLIC
    input
    mainp
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
    renum0.h
    renum1.f90
    renum1.h
    renum2.f90
    renum2.h
    renum3.f90
    renum3.h
    renum4.f90
    renum4.h
    renumn.f90
    ubicmx.f90
)
