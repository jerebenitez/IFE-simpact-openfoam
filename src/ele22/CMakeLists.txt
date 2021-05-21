add_library(ele22 "")

target_link_libraries(ele22
  PUBLIC
    input
    mainp
)

target_sources(ele22
  PUBLIC
    acvd22.inc
    code22.inc
    comm22.inc
    ele22_db.f90
    elem22.f90
    elmd22.inc
    gaus22.inc
    gauste.inc
    heat22.inc
    inpd22.f90
    luma22.inc
    mase22.inc
    poin22.inc
    updl22.inc
)
