add_executable(wildmatch_test wildmatch_test.c)
target_compile_options(wildmatch_test PRIVATE ${PROJECT_CFLAGS})
target_link_libraries(wildmatch_test wildmatch)

add_test(wildmatch_test wildmatch_test)
