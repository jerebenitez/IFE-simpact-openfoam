add_library(sprism "")

target_link_libraries(sprism
  PUBLIC
    mainp
)

target_sources(sprism
  PUBLIC
    acvd05.inc
    bmat05.inc
    bmat05q.inc
    bsma05.inc
    comm05.inc
    delt05.inc
    dump05.inc
    ele05_db.f90
    elem05.f90
    elmd05.inc
    expo05.inc
    gaus05.inc
    impo05.inc
    inpd05.f90
    jacob05.inc
    lcsy05.inc
    load05.inc
    luma05.inc
    mase05.inc
    outd05.inc
    rest05.inc
    resv05.inc
    slno05.inc
    slum05.inc
    surf05.inc
    toar05.inc
    updl05.inc
)
