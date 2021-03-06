macro(add_akonadi_isolated_test _source)
  set(_test ${_source})
  get_filename_component(_name ${_source} NAME_WE)
  kde4_add_executable(${_name} TEST ${_test})
  target_link_libraries(${_name}
    akonadi-kde
    akonadi-kmime
    kmime
    mailtransport
    kpimidentities
    kpimutils
    kcalutils
    kcalcore
    akonadi-calendar
    ${QT_QTTEST_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KIO_LIBS}
  )

  # based on kde4_add_unit_test
  if (WIN32)
    get_target_property( _loc ${_name} LOCATION )
    set(_executable ${_loc}.bat)
  else ()
    set(_executable ./${_name})
  endif ()
  if (UNIX)
    set(_executable ${_executable}.shell)
  endif ()

  find_program(_testrunner akonaditest)

  add_test( libakonadi-${_name}
    ${_testrunner} -c
    ${CMAKE_CURRENT_SOURCE_DIR}/unittestenv/config.xml
    ${_executable}
  )
endmacro()

#add_akonadi_isolated_test( historytest.cpp )
#add_akonadi_isolated_test( incidencechangertest.cpp )
add_akonadi_isolated_test( mailclienttest.cpp )
#add_akonadi_isolated_test( calendarbasetest.cpp )
#add_akonadi_isolated_test( fetchjobcalendartest.cpp )
#add_akonadi_isolated_test( etmcalendartest.cpp )
