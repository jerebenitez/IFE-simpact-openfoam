add_library(shrev "")

target_link_libraries(shrev
  PUBLIC
    input
)

target_sources(shrev
  PUBLIC
    acvdf9.inc
    btstr9.inc
    commv9.inc
    deltc9.inc
    dump09.inc
    ele09_db.f90
    elemt9.f90
    elmda9.inc
    gauss9.inc
    inpda9.f90
    intrf9.inc
    istgp9.inc
    j2sst9.f90
    locla9.inc
    lumas9.inc
    masel9.inc
    nodxy9.inc
    outdy9.inc
    rest09.inc
    resvp9.inc
    setga9.inc
    shape9.f90
    stran9.inc
    surf09.inc
    updlo9.inc
)