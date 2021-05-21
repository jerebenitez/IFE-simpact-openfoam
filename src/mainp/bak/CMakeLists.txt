add_library(bak "")

target_link_libraries(bak
  PUBLIC
    mainp
)

target_sources(bak
  PUBLIC
    dumpin.f90
    explit.f90
    sms_db.f90
    sxplit.f90
)
