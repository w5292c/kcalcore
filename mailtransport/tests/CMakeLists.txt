set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro(add_akonadi_isolated_test _source _path)
  get_filename_component(_targetName ${_source} NAME_WE)
  set(_srcList ${_source} )

  kde4_add_executable(${_targetName} TEST ${_srcList})
  target_link_libraries(${_targetName}
    ${QT_QTTEST_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDBUS_LIBRARY}
    akonadi-kde
    akonadi-kmime
    mailtransport
    kmime
    ${KDE4_KDECORE_LIBS}
  )

  # based on kde4_add_unit_test
  if (WIN32)
    get_target_property( _loc ${_targetName} LOCATION )
    set(_executable ${_loc}.bat)
  else()
    set(_executable ${EXECUTABLE_OUTPUT_PATH}/${_targetName})
  endif()
  if (UNIX)
    set(_executable ${_executable}.shell)
  endif()

  find_program(_testrunner akonaditest)

  add_test( mailtransport-${_targetName} ${_testrunner} -c ${CMAKE_CURRENT_SOURCE_DIR}/${_path}/config.xml ${_executable} )
endmacro()



# Independent executables:

set(tm_srcs transportmgr.cpp)
kde4_add_executable(transportmgr TEST ${tm_srcs})
target_link_libraries(transportmgr ${KDE4_KDEUI_LIBS} mailtransport)

set(queuer_srcs queuer.cpp)
kde4_add_executable(queuer TEST ${queuer_srcs})
target_link_libraries(queuer ${KDE4_KDEUI_LIBS} mailtransport kmime akonadi-kde akonadi-kmime)

set( sendqueued_srcs sendqueued.cpp )
kde4_add_executable( sendqueued TEST ${sendqueued_srcs} )
target_link_libraries( sendqueued ${KDE4_KDEUI_LIBS} mailtransport akonadi-kde akonadi-kmime)

set( clearerror_srcs clearerror.cpp )
kde4_add_executable( clearerror TEST ${clearerror_srcs} )
target_link_libraries( clearerror ${KDE4_KDEUI_LIBS} mailtransport akonadi-kde akonadi-kmime)

set( abort_srcs abort.cpp )
kde4_add_executable( abort TEST ${abort_srcs} )
target_link_libraries( abort ${KDE4_KDEUI_LIBS} mailtransport akonadi-kde)


# Akonadi testrunner-based tests:

add_akonadi_isolated_test( attributetest.cpp unittestenv )
add_akonadi_isolated_test( messagequeuejobtest.cpp unittestenv )
add_akonadi_isolated_test( filteractiontest.cpp unittestenv_akonadi )
