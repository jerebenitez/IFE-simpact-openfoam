add_library(prism "")

target_link_libraries(prism
  PUBLIC
    mainp./mainp
)

target_sources(prism
  PUBLIC
    acvd16.inc
    bmat16.inc
    bmat16q.inc
    bsma16.inc
    comm16.inc
    delt16.inc
    dump16.inc
    ele16_db.f90
    elem16.f90
    elmd16.inc
    expo16.inc
    gaus16.inc
    impo16.inc
    inpd16.f90
    jacob16.inc
    lcsy16.inc
    luma16.inc
    mase16.inc
    outd16.inc
    rest16.inc
    resv16.inc
    slno16.inc
    slum16.inc
    surf16.inc
    toar16.inc
    updl16.inc
)