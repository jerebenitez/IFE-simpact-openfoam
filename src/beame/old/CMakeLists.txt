add_library(old "")

target_link_libraries(old
  PUBLIC
    beame
)

target_sources(old
  PUBLIC
    acvdf8.inc
    commv8.inc
    cuate8.f90
    deltc8.inc
    dumpi8.inc
    ele08_db.f90
    elemt8.f90
    elmda8.inc
    expot8.f90
    gauss8.inc
    inpda8.f90
    intrf8.inc
    istg18.inc
    istg28.inc
    locla8.inc
    lumas8.inc
    masel8.inc
    masmt8.inc
    nodxy8.inc
    outdy8.inc
    rare18.inc
    resta8.inc
    resvp8.inc
    setga8.inc
    stran8.inc
    surf08.inc
    updlo8.inc
)
