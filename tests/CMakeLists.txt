add_executable(wildmatch_test wildmatch_test.c)
target_compile_options(wildmatch_test PRIVATE ${PROJECT_CFLAGS})
target_link_libraries(wildmatch_test wildmatch)

add_test(wildmatch_test wildmatch_test)

add_executable(test-wildmatch test-wildmatch.c)
set_target_properties(test-wildmatch PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                      ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(test-wildmatch PRIVATE ${PROJECT_CFLAGS})
target_link_libraries(test-wildmatch wildmatch)

add_test(git-wildmatch-tests ${CMAKE_CURRENT_SOURCE_DIR}/t3070-wildmatch.sh)
