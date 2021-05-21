add_library(ele21 "")

target_link_libraries(ele21
  PUBLIC
    input
    mainp
)

target_sources(ele21
  PUBLIC
    acvd21.inc
    code21.inc
    comm21.inc
    deriv1.inc
    ele21_db.f90
    elem21.f90
    elmd21.inc
    gaus21.inc
    heat21.inc
    inpd21.f90
    luma21.inc
    poin21.inc
    shape1t.inc
    updl21.inc
)
