add_library(truss "")

target_link_libraries(truss
  PUBLIC
    matdb
)

target_sources(truss
  PUBLIC
    acvdf2.inc
    commv2.inc
    deltc2.inc
    dumpi2.inc
    ele02_db.f90
    elemt2.f90
    elmda2.inc
    gauss2.inc
    inpda2.f90
    lumas2.inc
    masel2.inc
    outdy2.inc
    resta2.inc
    resvp2.inc
    stra02.inc
    stre02_1.f90
    stre02_6.f90
    stre02.inc
    updlo2.inc
)
