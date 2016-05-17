add_library(wildmatch SHARED wildmatch.c)
target_compile_options(wildmatch PRIVATE ${PROJECT_CFLAGS})

install(TARGETS wildmatch DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES wildmatch.h DESTINATION include/${PROJECT_NAME})
