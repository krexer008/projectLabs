add_executable(022 main.cpp)


target_include_directories(022 PRIVATE ${SFML_INCLUDE_DIR})

target_compile_features(02 PUBLIC cxx_std_17)

target_compile_definitions(02 PRIVATE SFML_STATIC)

target_link_libraries(022 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})