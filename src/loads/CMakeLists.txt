add_library(loads "")


target_sources(loads
  PUBLIC
    aplfol.f90
    area2d.f90
    areaq.f90
    axepld.f90
    dedge0.f90
    dedge1.f90
    dsurf0.f90
    dsurf1.f90
    hydf_db.f90
    loa_db.f90
    loadfl.f90
    Loadpl.f90
    loaini.f90
    pyrmd4.f90
    rdfoll.f90
    rdhyd2d.f90
    rdload.f90
    tetr.f90
    vol2d.f90
    waterb_ini.f90
    wrtfl0.f90
    wrtfl1.f90
)