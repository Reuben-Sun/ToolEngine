add_executable(client main.cpp client_framework.h client_framework.cpp)
target_link_libraries(client PRIVATE scene)

# Optick dll
add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:OptickCore>
    $<TARGET_FILE_DIR:client>
)

# tbb dll
add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:tbb>
    $<TARGET_FILE_DIR:client>
)

# Copy shaders
message(STATUS ${CMAKE_SOURCE_DIR})
add_custom_command(TARGET client POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/shaders/spv
	$<TARGET_FILE_DIR:client>/shaders
)

# Copy textures
add_custom_command(TARGET client POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/textures
	$<TARGET_FILE_DIR:client>/textures
)

# Copy models
add_custom_command(TARGET client POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/models
	$<TARGET_FILE_DIR:client>/models
)