CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

PROJECT(dwg2ansys)

SET(LIBRARY_OUTPUT_PATH ${dwg2ansys_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all libraries.")
SET(EXECUTABLE_OUTPUT_PATH ${dwg2ansys_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all executables.")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

SET(dwg2ansys_MAJOR_VERSION 0)
SET(dwg2ansys_MINOR_VERSION 1)
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

SET(RealDWG_INCLUDE_DIR "" CACHE PATH "RealDWG include dir")
IF(NOT EXISTS "${RealDWG_INCLUDE_DIR}")
  MESSAGE(FATAL_ERROR "RealDWG include directory is invalid")
ENDIF(NOT EXISTS "${RealDWG_INCLUDE_DIR}")

SET(RealDWG_LIB_DIR "" CACHE PATH "RealDWG lib dir")
IF(NOT EXISTS "${RealDWG_LIB_DIR}")
  MESSAGE(FATAL_ERROR "RealDWG lib directory is invalid")
ENDIF(NOT EXISTS "${RealDWG_LIB_DIR}")

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${RealDWG_INCLUDE_DIR}
)

SET(dwg2ansysLibs
  ${RealDWG_LIB_DIR}/acdb18.lib
  ${RealDWG_LIB_DIR}/acdbmgd.lib
  ${RealDWG_LIB_DIR}/acge18.lib
  ${RealDWG_LIB_DIR}/acgiapi.lib
  ${RealDWG_LIB_DIR}/acISMobj18.lib
  ${RealDWG_LIB_DIR}/AcMPolygonObj18.lib
  ${RealDWG_LIB_DIR}/AcSceneOE.lib
  ${RealDWG_LIB_DIR}/AcWipeoutObj18.lib
  ${RealDWG_LIB_DIR}/axdb.lib
  ${RealDWG_LIB_DIR}/rxapi.lib
  ${RealDWG_LIB_DIR}/rcexelib.obj
)

OPTION(USE_BREP_MODULE "Use Brep module" ON)
IF(USE_BREP_MODULE)
  SET(RealDWG_BREP_INCLUDE_DIR "" CACHE PATH "RealDWG Brep include dir")
  IF(NOT EXISTS "${RealDWG_BREP_INCLUDE_DIR}")
    MESSAGE(FATAL_ERROR "RealDWG Brep include directory is invalid")
  ENDIF(NOT EXISTS "${RealDWG_BREP_INCLUDE_DIR}")

  SET(RealDWG_BREP_LIB_DIR "" CACHE PATH "RealDWG Brep lib dir")
  IF(NOT EXISTS "${RealDWG_BREP_LIB_DIR}")
    MESSAGE(FATAL_ERROR "RealDWG Brep lib directory is invalid")
  ENDIF(NOT EXISTS "${RealDWG_BREP_LIB_DIR}")
  
  INCLUDE_DIRECTORIES(${RealDWG_BREP_INCLUDE_DIR})
  SET(dwg2ansysLibs ${dwg2ansysLibs}
    ${RealDWG_BREP_LIB_DIR}/acbr18.lib
	${RealDWG_BREP_LIB_DIR}/acgex18.lib
  )
ENDIF(USE_BREP_MODULE)

SET(dwg2ansysSrcs
  main.cxx
  AcadHost.cxx
  Convert.cxx
  Model.cxx
  Serialize.cxx
)

SET(dwg2ansysHdrs
  AcadHost.h
  Convert.h
  Model.h
  Serialize.h
  ${CMAKE_CURRENT_BINARY_DIR}/dwg2ansysVersion.h
)

IF(USE_BREP_MODULE)
  SET(dwg2ansysSrcs ${dwg2ansysSrcs}
    SerializeBrep.cxx  
  )
  SET(dwg2ansysHdrs ${dwg2ansysHdrs}
    SerializeBrep.h
  )
ENDIF(USE_BREP_MODULE)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/dwg2ansysVersion.h.in ${CMAKE_CURRENT_BINARY_DIR}/dwg2ansysVersion.h @ONLY)

ADD_EXECUTABLE(dwg2ansys ${dwg2ansysSrcs} ${dwg2ansysHdrs})

SET_TARGET_PROPERTIES(dwg2ansys PROPERTIES
  VERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}"
  SOVERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}"
) 

TARGET_LINK_LIBRARIES(dwg2ansys
  ${dwg2ansysLibs}
)
