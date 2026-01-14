set(GLAPP_TESTS_NAME glapp_tests)
add_executable(${GLAPP_TESTS_NAME}
    main.cpp
)
target_include_directories(${GLAPP_TESTS_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${GLAPP_TESTS_NAME} PRIVATE glapp)
