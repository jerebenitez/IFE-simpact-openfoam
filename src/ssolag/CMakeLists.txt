add_library(ssolag "")

target_link_libraries(ssolag
  PUBLIC
    mainp
    tetra
)

target_sources(ssolag
  PUBLIC
    acvd04.inc
    bmat04.inc
    bmat04q.inc
    bsma04.inc
    comm04.inc
    delt04.inc
    dump04.inc
    ele04_db.f90
    elem04.f90
    elmd04.inc
    expo04.inc
    gaus04.inc
    impo04.inc
    Inpd04.f90
    jacob04.inc
    lcsy04.inc
    load04.inc
    luma04.inc
    mase04.inc
    outd04.inc
    rest04.inc
    resv04.inc
    slno04.inc
    slum04.inc
    surf04.inc
    updl04.inc
)
