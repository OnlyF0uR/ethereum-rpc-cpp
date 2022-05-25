cmake_minimum_required(VERSION 3.22)
project("eth-rpc" VERSION 1.0.0 DESCRIPTION "Wrapper for the ethereum json rpc")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directories including CURL and JSONCPP
include_directories(include/ ${CURL_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIR} ${BOOST_INCLUDEDIR})

# Add all source files
file(GLOB SOURCE_FILES
    "src/*.cpp"
    "src/rlp/*.c"
    "src/*.c"
    "src/crypto/*.c"
)
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/wrapper.hpp)

# Config file
configure_file(eth-rpc.pc.in eth-rpc.pc @ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE .)

# Install the lib
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the pkconfig file
install(FILES ${CMAKE_BINARY_DIR}/eth-rpc.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)