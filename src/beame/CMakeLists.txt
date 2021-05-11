add_library(beame "")

add_subdirectory(old)

target_link_libraries(beame
  PUBLIC
    beame/old./beame
)

target_sources(beame
  PUBLIC
    acvdf8.inc
    bmatx8.inc
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