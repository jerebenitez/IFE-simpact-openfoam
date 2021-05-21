add_library(tetra "")

target_sources(tetra
  PUBLIC
    acvd04.inc
    axep04.inc
    bmat04.inc
    comm04.inc
    delt04.inc
    dump04.inc
    ele04_db.f90
    elem04.f90
    elmd04.inc
    gaus04.inc
    gaus04n.inc
    inpd04.f90
    luma04.inc
    mase04.inc
    outd04.inc
    rest04.inc
    resv04e.inc
    resv04.inc
    resv04n.inc
    toar04.inc
    toar04n.inc
)
