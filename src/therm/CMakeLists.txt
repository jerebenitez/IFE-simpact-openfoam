add_library(therm "")

target_link_libraries(therm
  PUBLIC
    input
    mainp
)

target_sources(therm
  PUBLIC
    fixtem.f90
    fsurf_tbc_db.f90
    heaini.f90
    heat_db.f90
    heatpl.f90
    ift_db.f90
    rdfsur.f90
    rdheat.f90
    rdheat.h
    rdhedg.f90
    rdhedg.h
    rdhsur.f90
    rdhsur.h
    rdpret.f90
    rdpret.h
    rdtemp.f90
    tcsurf.f90
    texplit.f90
    tlmass.f90
)
