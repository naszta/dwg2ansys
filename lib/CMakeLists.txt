PROJECT(dwg2ansysLib)

SET(RealDWG_ROOT_DIR "" CACHE PATH "RealDWG root directory")

SET(RealDWG_INCLUDE_DIR "${RealDWG_ROOT_DIR}/Inc")
IF(NOT EXISTS "${RealDWG_INCLUDE_DIR}")
  MESSAGE(FATAL_ERROR "RealDWG include directory is invalid")
ENDIF(NOT EXISTS "${RealDWG_INCLUDE_DIR}")

SET(RealDWG_LIB_DIR "${RealDWG_ROOT_DIR}/Lib")
IF(NOT EXISTS "${RealDWG_LIB_DIR}")
  MESSAGE(FATAL_ERROR "RealDWG lib directory is invalid")
ENDIF(NOT EXISTS "${RealDWG_LIB_DIR}")

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${RealDWG_INCLUDE_DIR}
)

SET(dwg2ansysLibLibs
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

OPTION(USE_BREP_MODULE "Use Brep module" OFF)
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
  SET(dwg2ansysLibLibs ${dwg2ansysLibLibs}
    ${RealDWG_BREP_LIB_DIR}/acbr18.lib
	${RealDWG_BREP_LIB_DIR}/acgex18.lib
  )
ENDIF(USE_BREP_MODULE)

SET(dwg2ansysLibSrcs
  AcadHost.cxx
  Convert.cxx
  Model.cxx
  Serialize.cxx
)

SET(dwg2ansysLibHdrs
  AcadHost.h
  Convert.h
  Model.h
  Serialize.h
  dwg2ansysLibExport.h
  ${dwg2ansys_BINARY_DIR}/dwg2ansysVersion.h
)

IF(USE_BREP_MODULE)
  SET(dwg2ansysSrcs ${dwg2ansysSrcs}
    SerializeBrep.cxx  
  )
  SET(dwg2ansysHdrs ${dwg2ansysHdrs}
    SerializeBrep.h
  )
ENDIF(USE_BREP_MODULE)

IF(WIN32)
  SET(WIN_VERSION ${CMAKE_CURRENT_BINARY_DIR}/dwg2ansysVersion.rc)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/dwg2ansysVersion.rc.in ${WIN_VERSION} @ONLY IMMEDIATE)
  SOURCE_GROUP("Resources" FILES ${WIN_VERSION} )
ENDIF(WIN32)

ADD_LIBRARY(dwg2ansysLib SHARED ${dwg2ansysLibSrcs} ${dwg2ansysLibHdrs} ${WIN_VERSION})

TARGET_LINK_LIBRARIES(dwg2ansysLib
  ${dwg2ansysLibLibs}
)

SET_TARGET_PROPERTIES(dwg2ansysLib PROPERTIES
  VERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}"
  SOVERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}"
)

INSTALL(TARGETS dwg2ansysLib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

