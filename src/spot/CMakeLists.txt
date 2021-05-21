add_library(spot "")

target_sources(spot
  PUBLIC
    acvdf1.inc
    commv1.inc
    deltc1.inc
    dumpi1.inc
    ele01_db.f90
    elemt1.f90
    elmda1.inc
    gauss1.inc
    inpda1.f90
    lumas1.inc
    masel1.inc
    outdy1.inc
    resta1.inc
    resvp1.inc
    updlo1.inc
)
