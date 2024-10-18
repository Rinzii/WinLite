cmake_minimum_required(VERSION 3.15)

# Project details
project(WinLite VERSION 1.0.0 LANGUAGES C)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Option to enable or disable installation
option(WINLITE_INSTALL "Enable installation of WinLite" ON)

# Library source files (header files only since there are no actual source files)
set(SOURCES
        include/WinLite/internal/minWindows.h
        include/WinLite/internal/postWinapi.h
        include/WinLite/internal/preWinapi.h
        include/WinLite/Windows.h
)

# Define the library as an INTERFACE library since it is header-only
add_library(WinLite INTERFACE)

# Specify the include directories
target_include_directories(WinLite INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Installation section, only if WINLITE_INSTALL is ON
if(WINLITE_INSTALL)
    # Installation instructions
    include(GNUInstallDirs)

    # Install the library target (header-only so no compiled files)
    install(TARGETS WinLite
            EXPORT WinLiteTargets
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Install the header files
    install(DIRECTORY include/WinLite
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Export the package for use with find_package
    install(EXPORT WinLiteTargets
            FILE WinLiteTargets.cmake
            NAMESPACE WinLite::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WinLite
    )

    # Create a ConfigVersion.cmake file for version tracking
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            WinLiteConfigVersion.cmake
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY AnyNewerVersion
    )

    # Install the Config and ConfigVersion files
    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/WinLiteConfigVersion.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WinLite
    )

    # Create a Config file to be used by find_package
    configure_package_config_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/WinLiteConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/WinLiteConfig.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WinLite
    )

    install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/WinLiteConfig.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/WinLite
    )
endif()
