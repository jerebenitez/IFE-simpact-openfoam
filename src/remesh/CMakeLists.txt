add_library(remesh "")

target_link_libraries(remesh
  PUBLIC
    mainp
)

target_sources(remesh
  PUBLIC
    del_e_mrea.f90
    deloln.f90
    dispcrv.f90
    dspval.f90
    exnods.f90
    fnod_fix.f90
    get_ifxb.f90
    meshmo_db.f90
    mshcri.f90
    newfix.f90
    nodfnd.f90
    plines.f90
    pregid.f90
    qloop.f90
    rdmeshmo.f90
    remesh.f90
    rmctrln.f90
    rnmesh.f90
    solrem.f90
    sortlb.f90
    transf1.f90
    transf.f90
    verifd.f90
    vertex.f90
)