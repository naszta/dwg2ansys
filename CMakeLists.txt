CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

PROJECT(dwg2ansys)

SET(LIBRARY_OUTPUT_PATH ${dwg2ansys_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all libraries.")
SET(EXECUTABLE_OUTPUT_PATH ${dwg2ansys_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all executables.")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

SET(dwg2ansys_MAJOR_VERSION 0)
SET(dwg2ansys_MINOR_VERSION 3)
IF(EXISTS ${dwg2ansys_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
	  COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY "${dwg2ansys_SOURCE_DIR}"
      OUTPUT_VARIABLE "dwg2ansys_BUILD_VERSION"
	  ERROR_QUIET
	  OUTPUT_STRIP_TRAILING_WHITESPACE
    )
	MESSAGE( STATUS "Git version: ${dwg2ansys_BUILD_VERSION}" )
  ELSE(GIT_FOUND)
    SET(dwg2ansys_BUILD_VERSION 0) 
  ENDIF(GIT_FOUND)
ENDIF(EXISTS ${dwg2ansys_SOURCE_DIR}/.git)
SET(dwg2ansys_VERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}.${dwg2ansys_BUILD_VERSION}")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/dwg2ansysVersion.h.in ${CMAKE_CURRENT_BINARY_DIR}/dwg2ansysVersion.h @ONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/icon.ico ${CMAKE_CURRENT_BINARY_DIR}/icon.ico COPYONLY)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(bin)
ADD_SUBDIRECTORY(gui)

# install RealDWG
INSTALL(FILES
  "${RealDWG_ROOT_DIR}/ac1st18.dll"
  "${RealDWG_ROOT_DIR}/acdb18.dll"
  "${RealDWG_ROOT_DIR}/acge18.dll"
  "${RealDWG_ROOT_DIR}/AcUt.dll"
  "${RealDWG_ROOT_DIR}/acdb18enures.dll"
  DESTINATION bin
)

OPTION(dwg2ansys_MAKE_PACK "Generate pacakage files." ON)
IF(dwg2ansys_MAKE_PACK)
  INCLUDE(CPackConfig.cmake)
ENDIF(dwg2ansys_MAKE_PACK)
