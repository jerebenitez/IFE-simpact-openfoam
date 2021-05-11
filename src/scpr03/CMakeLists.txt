add_library(scpr03 "")


target_sources(scpr03
  PUBLIC
    form_patch_lib.f90
    spr_constants.f90
    spr_elem_type_db.f90
    spr_lib.f90
    spr_type_db.f90
    transf_g.f90
    trian.f90
)