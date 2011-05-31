PROJECT(dwg2ansysGui)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${dwg2ansysLib_SOURCE_DIR}
  ${QT_INCLUDE_DIR}
)

SET(dwg2ansysGuiSrcs
  main.cxx
  MainDialog.cxx
)

SET(dwg2ansysGuiQtHdrs
  MainDialog.h
)

SET(dwg2ansysGuiHdrs
)

SET(UIS
  MainDialog.ui
)

SET(RCCS
  resources.qrc
)

IF(WIN32)
  SET(WIN_VERSION ${CMAKE_CURRENT_BINARY_DIR}/dwg2ansysVersion.rc)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/dwg2ansysVersion.rc.in ${WIN_VERSION} @ONLY IMMEDIATE)
  SOURCE_GROUP("Resources" FILES ${WIN_VERSION} )
ENDIF(WIN32)
CONFIGURE_FILE(${dwg2ansys_SOURCE_DIR}/icon.ico ${CMAKE_CURRENT_BINARY_DIR}/icon.ico COPYONLY)

QT4_ADD_RESOURCES(RCCSrcs ${RCCS})   
QT4_WRAP_UI(UISrcs ${UIS})
QT4_WRAP_CPP(MOCSrcs ${dwg2ansysGuiQtHdrs})

SOURCE_GROUP("Generated" FILES ${RCCSrcs})
SOURCE_GROUP("Generated" FILES ${UISrcs})
SOURCE_GROUP("Generated" FILES ${MOCSrcs})

ADD_EXECUTABLE(dwg2ansysGui WIN32 ${dwg2ansysGuiSrcs} ${dwg2ansysGuiHdrs} ${dwg2ansysGuiQtHdrs} ${WIN_VERSION} ${RCCSrcs} ${UISrcs} ${MOCSrcs})

TARGET_LINK_LIBRARIES(dwg2ansysGui
  ${QT_LIBRARIES}
  dwg2ansysLib
)

SET_TARGET_PROPERTIES(dwg2ansysGui PROPERTIES
  VERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}"
  SOVERSION "${dwg2ansys_MAJOR_VERSION}.${dwg2ansys_MINOR_VERSION}"
)

INSTALL(TARGETS dwg2ansysGui
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

INSTALL(FILES
  "${QT_LIBRARY_DIR}/QtCore4.dll"
  "${QT_LIBRARY_DIR}/QtGui4.dll"
  DESTINATION bin
)
