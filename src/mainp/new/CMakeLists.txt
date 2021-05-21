add_library(new "")

target_link_libraries(new
  PUBLIC
    mainp
)

target_sources(new
  PUBLIC
    dumpin.f90
    explit.f90
    sms_db.f90
    sxplit.f90
)
