add_library(beam2 "")

target_link_libraries(beam2
  PUBLIC
    mainp
)

target_sources(beam2
  PUBLIC
    acvd11.inc
    bfle11.inc
    bmem11.inc
    comm11.inc
    delt11.inc
    dump11.inc
    ele11_db.f90
    elem11.f90
    elmd11.inc
    gaus11.inc
    inpd11.f90
    luma11.inc
    mase11.inc
    outd11.inc
    rest11.inc
    resv11.inc
    stra11.inc
    streb2.inc
    surf11.inc
    toar11.inc
    updl11.inc
)
