find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(SRCS
    main.cpp
    treeview_enable_edit_next_field.cpp
    treeview_enable_valid.cpp)

add_executable(edit-row ${SRCS})
target_link_libraries(edit-row ${GTKMM_LIBRARIES})
target_include_directories(edit-row PUBLIC . ${GTKMM_INCLUDE_DIRS})
