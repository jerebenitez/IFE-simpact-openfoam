add_library(quadl "")

target_link_libraries(quadl
  PUBLIC
    mainp
)

target_sources(quadl
  PUBLIC
    acvd17.inc
    bmat17.inc
    comm17.inc
    delt17.inc
    dump17.inc
    eige17.f90
    ele17_db.f90
    elem17.f90
    elmd17.inc
    gaus17.inc
    inpd17.f90
    jaco17.inc
    luma17.inc
    mase17.inc
    masm17.inc
    nods17.inc
    outd17.inc
    rest17.inc
    resv17.inc
    resv17r.inc
    slnods17.inc
    surf17.inc
    updl17.inc
)
