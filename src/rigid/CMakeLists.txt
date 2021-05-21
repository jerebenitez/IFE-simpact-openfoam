add_library(rigid "")

target_link_libraries(rigid
  PUBLIC
    mainp
)

target_sources(rigid
  PUBLIC
    acvd10.inc
    code10.inc
    comm10.inc
    dump10.inc
    ele10_db.f90
    elem10.f90
    elmd10.inc
    gaus10.inc
    hmin.f90
    inpd10.f90
    luma10.inc
    mase10.inc
    poin10.inc
    rearb0.inc
    rest10.inc
    rigb10.inc
    rigbdc.f90
    rigbdy.inc
    surf10.inc
    tlma10.inc
    tres10.inc
    updl10.inc
)
