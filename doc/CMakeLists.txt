
if(PANG_BUILD_DOC)
	find_package(Doxygen REQUIRED)

	# define the install directory for miscellaneous files
	if(WINDOWS)
		set(INSTALL_MISC_DIR .)
	elseif(UNIX)
		set(INSTALL_MISC_DIR share/SFML)
	endif()

	# set the input and output documentation paths
	set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
	set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/doc)


	# configure the source Doxyfile by copying it and replacing all @variables@
	set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)
	configure_file(${DOXYGEN_INPUT_DIR}/doc/Doxyfile ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

	# target setup
	add_custom_target(doc ALL
		              COMMAND ${CMAKE_COMMAND} -E echo_append "Building Documentation..."
		              COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
		              COMMAND ${CMAKE_COMMAND} -E echo "Done."
		              WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

	# setup install rules
	install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
		    DESTINATION ${INSTALL_MISC_DIR}/doc
		    COMPONENT doc)
endif()
