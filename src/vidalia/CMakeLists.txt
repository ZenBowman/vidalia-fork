##
##  $Id$
## 
##  This file is part of Vidalia, and is subject to the license terms in the
##  LICENSE file, found in the top level directory of this distribution. If 
##  you did not receive the LICENSE file with this file, you may obtain it
##  from the Vidalia source package distributed by the Vidalia Project at
##  http://www.torproject.org/projects/vidalia.html. No part of Vidalia, 
##  including this file, may be copied, modified, propagated, or distributed 
##  except according to the terms described in the LICENSE file.
##


include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/about
  ${CMAKE_CURRENT_SOURCE_DIR}/bwgraph
  ${CMAKE_CURRENT_SOURCE_DIR}/config
  ${CMAKE_CURRENT_SOURCE_DIR}/help/browser
  ${CMAKE_CURRENT_SOURCE_DIR}/log
  ${CMAKE_CURRENT_SOURCE_DIR}/network
  ${MARBLE_INCLUDE_DIR}
)

if (USE_BREAKPAD AND BREAKPAD_INCLUDE_DIR)
  include_directories(${BREAKPAD_INCLUDE_DIR})
endif(USE_BREAKPAD AND BREAKPAD_INCLUDE_DIR)
if (USE_GEOIP AND GEOIP_INCLUDE_DIR)
  include_directories(${GEOIP_INCLUDE_DIR})
endif(USE_GEOIP AND GEOIP_INCLUDE_DIR)

if (USE_MARBLE)
  if (APPLE OR WIN32)
  ##
  ## XXX: The Marble build system on OS X currently doesn't actually install the
  ## required include files to /usr/local/include or similar. Instead, we have
  ## to pluck them directly from the source tree. Ick.
  ##
    include_directories(
      ${MARBLE_INCLUDE_DIR}/AbstractLayer
      ${MARBLE_INCLUDE_DIR}/geodata
      ${MARBLE_INCLUDE_DIR}/geodata/data
      ${MARBLE_INCLUDE_DIR}/geodata/handlers
      ${MARBLE_INCLUDE_DIR}/geodata/parser
      ${MARBLE_INCLUDE_DIR}/geodata/scene
      ${MARBLE_INCLUDE_DIR}/Projections
    )
  endif(APPLE OR WIN32)
endif(USE_MARBLE)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/res/vidalia_win.rc.in
  ${CMAKE_CURRENT_SOURCE_DIR}/res/vidalia_win.rc
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/i18n/vidalia_i18n.qrc
  ${CMAKE_CURRENT_BINARY_DIR}/i18n/vidalia_i18n.qrc
)

## Process the translation files
add_subdirectory(i18n)

## About dialog sources
set(vidalia_SRCS 
  about/AboutDialog.cpp
  about/LicenseDialog.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  about/AboutDialog.h
  about/LicenseDialog.h
)

## Bandwidth graph sources
set(vidalia_SRCS ${vidalia_SRCS}
  bwgraph/BandwidthGraph.cpp
  bwgraph/GraphFrame.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  bwgraph/BandwidthGraph.h
  bwgraph/GraphFrame.h
)

## Configuration dialog sources
set(vidalia_SRCS ${vidalia_SRCS}
  config/AbstractTorSettings.cpp
  config/AdvancedPage.cpp
  config/AppearancePage.cpp
  config/BridgeUsageDialog.cpp
  config/ConfigDialog.cpp
  config/ConfigPageStack.cpp
  config/DomainValidator.cpp
  config/ExitPolicy.cpp
  config/GeneralPage.cpp
  config/IpValidator.cpp
  config/Local8BitStringValidator.cpp
  config/NetworkPage.cpp
  config/NetworkSettings.cpp
  config/NicknameValidator.cpp
  config/Policy.cpp
  config/PortValidator.cpp
  config/PortConfigurator.cpp
  config/ServerPage.cpp
  config/ServerSettings.cpp
  config/Service.cpp
  config/ServiceList.cpp
  config/ServicePage.cpp
  config/TorrcDialog.cpp
  config/ServiceSettings.cpp
  config/TorSettings.cpp
  config/VidaliaSettings.cpp
  config/VSettings.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  config/AbstractTorSettings.h
  config/AdvancedPage.h
  config/AppearancePage.h
  config/BridgeUsageDialog.h
  config/ConfigDialog.h
  config/ConfigPage.h
  config/ConfigPageStack.h
  config/DomainValidator.h
  config/GeneralPage.h
  config/Local8BitStringValidator.h
  config/NetworkPage.h
  config/NetworkSettings.h
  config/NicknameValidator.h
  config/PortValidator.h
  config/ServerPage.h
  config/ServerSettings.h
  config/ServicePage.h
  config/TorrcDialog.h
  config/TorSettings.h
  config/VidaliaSettings.h
  config/VSettings.h
)
if (USE_MINIUPNPC)
  include_directories(${MINIUPNPC_INCLUDE_DIR})
  set(vidalia_SRCS ${vidalia_SRCS}
    config/UPNPControl.cpp
    config/UPNPControlThread.cpp
    config/UPNPTestDialog.cpp
  )
  qt4_wrap_cpp(vidalia_SRCS
    config/UPNPControl.h
    config/UPNPControlThread.h
    config/UPNPTestDialog.h
  )
endif(USE_MINIUPNPC)

## Help browser sources
set(vidalia_SRCS ${vidalia_SRCS}
  help/browser/HelpBrowser.cpp
  help/browser/HelpTextBrowser.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  help/browser/HelpBrowser.h
  help/browser/HelpTextBrowser.h
)

## Message log sources
set(vidalia_SRCS ${vidalia_SRCS}
  log/LogFile.cpp
  log/LogHeaderView.cpp
  log/LogMessageColumnDelegate.cpp
  log/LogTreeItem.cpp
  log/LogTreeWidget.cpp
  log/MessageLog.cpp
  log/StatusEventItem.cpp
  log/StatusEventItemDelegate.cpp
  log/StatusEventWidget.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  log/LogFile.h
  log/LogHeaderView.h
  log/LogTreeWidget.h
  log/MessageLog.h
  log/StatusEventItemDelegate.h
  log/StatusEventWidget.h
)

## Network map sources
set(vidalia_SRCS ${vidalia_SRCS}
  network/CircuitItem.cpp
  network/CircuitListWidget.cpp
  network/CountryInfo.cpp
  network/GeoIpRecord.cpp
  network/GeoIpResolver.cpp
  network/NetViewer.cpp
  network/RouterDescriptorView.cpp
  network/RouterInfoDialog.cpp
  network/RouterListItem.cpp
  network/RouterListWidget.cpp
  network/StreamItem.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  network/CircuitListWidget.h
  network/CountryInfo.h
  network/GeoIpResolver.h
  network/NetViewer.h
  network/RouterDescriptorView.h
  network/RouterInfoDialog.h
  network/RouterListWidget.h
)
if (USE_MARBLE)
  set(vidalia_SRCS ${vidalia_SRCS}
    network/TorMapWidget.cpp
    network/TorMapWidgetInputHandler.cpp
    network/TorMapWidgetPopupMenu.cpp
  )
  qt4_wrap_cpp(vidalia_SRCS
    network/TorMapWidget.h
    network/TorMapWidgetInputHandler.h
    network/TorMapWidgetPopupMenu.h
  )
else(USE_MARBLE)
  set(vidalia_SRCS ${vidalia_SRCS}
    network/TorMapImageView.cpp
    network/ZImageView.cpp
  )
  qt4_wrap_cpp(vidalia_SRCS
    network/TorMapImageView.h
    network/ZImageView.h
  )
endif(USE_MARBLE)
if (USE_GEOIP)
  set(vidalia_SRCS ${vidalia_SRCS}
    network/GeoIpDatabase.cpp
  )
  qt4_wrap_cpp(vidalia_SRCS
    network/GeoIpDatabase.h
  )
endif(USE_GEOIP)

## Main Vidalia sources
set(vidalia_SRCS ${vidalia_SRCS}
  main.cpp
  Vidalia.cpp
  LanguageSupport.cpp
  MainWindow.cpp
  VClickLabel.cpp
  VidaliaWindow.cpp
  VMessageBox.cpp
  HelperProcess.cpp
  ControlPasswordInputDialog.cpp
)
qt4_wrap_cpp(vidalia_SRCS
  Vidalia.h
  MainWindow.h
  VClickLabel.h
  VidaliaWindow.h
  VMessageBox.h
  HelperProcess.h
  ControlPasswordInputDialog.h
)
if (USE_BREAKPAD)
  set(vidalia_SRCS ${vidalia_SRCS}
    CrashReporter.cpp
  )
endif(USE_BREAKPAD)

## Specify all the Qt Designer .ui files
qt4_wrap_ui(vidalia_SRCS
  ControlPasswordInputDialog.ui
  MainWindow.ui
  about/AboutDialog.ui
  about/LicenseDialog.ui
  bwgraph/BandwidthGraph.ui
  config/AdvancedPage.ui
  config/AppearancePage.ui
  config/BridgeUsageDialog.ui
  config/ConfigDialog.ui
  config/GeneralPage.ui
  config/NetworkPage.ui
  config/ServerPage.ui
  config/ServicePage.ui
  config/TorrcDialog.ui
  help/browser/HelpBrowser.ui
  log/MessageLog.ui
  network/NetViewer.ui
  network/RouterInfoDialog.ui
)

if (USE_MINIUPNPC)
  qt4_wrap_ui(vidalia_SRCS config/UPNPTestDialog.ui)
endif(USE_MINIUPNPC)

if (USE_AUTOUPDATE)
  set(vidalia_SRCS ${vidalia_SRCS}
    PackageInfo.cpp
    UpdateProcess.cpp
    UpdateProgressDialog.cpp
    UpdatesAvailableDialog.cpp
  )
  qt4_wrap_cpp(vidalia_SRCS
    UpdateProcess.h
    UpdateProgressDialog.h
    UpdatesAvailableDialog.h
  )
  qt4_wrap_ui(vidalia_SRCS
    UpdateProgressDialog.ui
    UpdatesAvailableDialog.ui
  )
endif(USE_AUTOUPDATE)

## Add the resource files (icons, etc.)
qt4_add_resources(vidalia_SRCS
  res/vidalia.qrc
  help/content/content.qrc
  ${CMAKE_CURRENT_BINARY_DIR}/i18n/vidalia_i18n.qrc
)

## Specify the map data Marble will need
set(marble_DATA
  landcolors.leg
  seacolors.leg
  maps/earth/bluemarble/bluemarble.dgml
  maps/earth/citylights/citylights.dgml
  maps/earth/srtm/srtm.dgml
  maps/earth/srtm/srtm.jpg
  mwdbii/DATELINE.PNT
  mwdbii/PAUST.PNT
  mwdbii/PBORDER.PNT
  mwdbii/PCANPROV.PNT
  mwdbii/PCOAST.PNT
  mwdbii/PDIFFBORDER.PNT
  mwdbii/PGLACIER.PNT
  mwdbii/PISLAND.PNT
  mwdbii/PLAKE.PNT
  mwdbii/PLAKEISLAND.PNT
  mwdbii/PMEXICO.PNT
  mwdbii/PUSA48.DIFF.PNT
  mwdbii/PUSA48.PNT
  mwdbii/RIVER.PNT
  placemarks/baseplacemarks.cache
  placemarks/boundaryplacemarks.cache
  placemarks/elevplacemarks.cache
  stars/stars.dat
  svg/worldmap.svg
)

## Set the appropriate executable target for the current platform
if (APPLE)
  ## Set the output file name (make it uppercase on OS X)
  set(vidalia_BIN Vidalia)
  
  ## Create an OS X application bundle
  set(MACOSX_BUNDLE_BUNDLE_NAME           Vidalia)
  set(MACOSX_BUNDLE_BUNDLE_VERSION        ${VERSION})
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING  ${VERSION})
  set(MACOSX_BUNDLE_LONG_VERSION_STRING   "Version ${VERSION}")
  set(MACOSX_BUNDLE_ICON_FILE             vidalia.icns)
  set(MACOSX_BUNDLE_GUI_IDENTIFIER        "net.vidalia-project.vidalia")
  set(MACOSX_BUNDLE_INFO_STRING           "Vidalia ${VERSION}")

  ## Put everything inside the application bundle
  set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/)
  add_executable(${vidalia_BIN} MACOSX_BUNDLE ${vidalia_SRCS})

  ## Specify location of custom Info.plist file 
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in
                 ${CMAKE_CURRENT_BINARY_DIR}/MacOSXBundleInfo.plist)
  set_target_properties(${vidalia_BIN} PROPERTIES MACOSX_BUNDLE_INFO_PLIST 
                        ${CMAKE_CURRENT_BINARY_DIR}/MacOSXBundleInfo.plist)

  ## Get the location of the app bundle for the current configuration
  get_target_property(VIDALIA_EXECUTABLE ${vidalia_BIN} LOCATION)
  get_filename_component(MACOSX_BUNDLE_DIRECTORY ${VIDALIA_EXECUTABLE} PATH)
  get_filename_component(MACOSX_BUNDLE_DIRECTORY "${MACOSX_BUNDLE_DIRECTORY}/../../" ABSOLUTE)

  ## Include the bundle resource files
  add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
      ARGS -E make_directory ${MACOSX_BUNDLE_DIRECTORY}/Contents/Resources
    COMMAND ${CMAKE_COMMAND}
      ARGS -E make_directory ${MACOSX_BUNDLE_DIRECTORY}/share/tor
    COMMAND cp
      ARGS ${CMAKE_CURRENT_SOURCE_DIR}/res/icons/*.icns 
           ${MACOSX_BUNDLE_DIRECTORY}/Contents/Resources/
  )

  if (USE_MARBLE)
    ## Copy the Marble data into the bundle
    foreach(it ${marble_DATA})
      get_filename_component(outdir  ${it} PATH)
      get_filename_component(outfile ${it} NAME)
      set(outdir ${MACOSX_BUNDLE_DIRECTORY}/Contents/Resources/data/${outdir})

      add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
          ARGS -E make_directory ${outdir}
        COMMAND ${CMAKE_COMMAND}
          ARGS -E copy_if_different 
                ${MARBLE_DATA_DIR}/${it} ${outdir}/${outfile}
      )
    endforeach(it)

    ## Create the Marble plugins directory and copy in any wanted plugins
    if (MARBLE_PLUGINS)
      add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
          ARGS -E make_directory 
               ${MACOSX_BUNDLE_DIRECTORY}/Contents/Resources/plugins
      )
      foreach(it ${MARBLE_PLUGINS})
        add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
          COMMAND ${CMAKE_COMMAND}
            ARGS -E copy_if_different ${it}
             ${MACOSX_BUNDLE_DIRECTORY}/Contents/Resources/plugins/
        )
      endforeach(it)
    endif(MARBLE_PLUGINS)
  endif(USE_MARBLE)
else(APPLE)
  ## Set the output file name
  set(vidalia_BIN vidalia)

  if (WIN32)
    ## Create a Windows binary
    win32_add_rc(vidalia_SRCS res/vidalia_win.rc)
    add_executable(${vidalia_BIN} WIN32 ${vidalia_SRCS})

    ## Copy the Marble data into the data/ directory under the binary
    if (USE_MARBLE)
      foreach(it ${marble_DATA})
        get_filename_component(outdir  ${it} PATH)
        get_filename_component(outfile ${it} NAME)

        add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
          COMMAND ${CMAKE_COMMAND}
            ARGS -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${outdir}
          COMMAND ${CMAKE_COMMAND}
            ARGS -E copy_if_different ${MARBLE_DATA_DIR}/${it} 
                                      ${CMAKE_CURRENT_BINARY_DIR}/data/${it}
        )
      endforeach(it)

      ## Create the Marble plugins directory and copy in any wanted plugins
      if (MARBLE_PLUGINS)
        add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
          COMMAND ${CMAKE_COMMAND}
            ARGS -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/plugins/marble
        )
        foreach(it ${MARBLE_PLUGINS})
          add_custom_command(TARGET ${vidalia_BIN} POST_BUILD
            COMMAND ${CMAKE_COMMAND}
              ARGS -E copy_if_different ${it} 
                    ${CMAKE_CURRENT_BINARY_DIR}/plugins/marble/
          )
        endforeach(it)
      endif(MARBLE_PLUGINS)
    endif(USE_MARBLE)

  else (WIN32)
    ## Non-Windows, non-Mac
    add_executable(${vidalia_BIN} ${vidalia_SRCS})
  endif(WIN32)
endif(APPLE)
add_dependencies(${vidalia_BIN} i18n)


## Link to the Qt libraries and other libraries built as a part of Vidalia
target_link_libraries(${vidalia_BIN}
  ${QT_LIBRARIES}
  common
  torcontrol
)
if (USE_MINIUPNPC)
  target_link_libraries(${vidalia_BIN} miniupnpc)
endif(USE_MINIUPNPC)
if (USE_BREAKPAD)
  target_link_libraries(${vidalia_BIN} ${BREAKPAD_LIBRARY})
endif(USE_BREAKPAD)
if (USE_MARBLE)
  target_link_libraries(${vidalia_BIN}
    ${MARBLE_LIBRARIES}
    ${QT_QTSVG_LIBRARY}
  )
endif(USE_MARBLE)
if (USE_GEOIP)
  target_link_libraries(${vidalia_BIN} ${GEOIP_LIBRARIES})
endif(USE_GEOIP)

if (WIN32)
  target_link_libraries(${vidalia_BIN}
    ${QT_QTMAIN_LIBRARY}
  )
endif(WIN32)

if (APPLE)
  target_link_libraries(${vidalia_BIN}
    "-framework AppKit"
    iconv
  )
endif(APPLE)

## Specify the files to be installed
install(TARGETS ${vidalia_BIN} DESTINATION bin)
if(NOT WIN32 AND NOT APPLE)
  install(FILES vidalia.desktop DESTINATION share/applications)
  install(FILES res/16x16/tor-logo.png RENAME vidalia.png
          DESTINATION share/icons/hicolor/16x16/apps)
  install(FILES res/22x22/tor-logo.png RENAME vidalia.png
          DESTINATION share/icons/hicolor/22x22/apps)
  install(FILES res/32x32/tor-logo.png RENAME vidalia.png
          DESTINATION share/icons/hicolor/32x32/apps)
  install(FILES res/48x48/tor-logo.png RENAME vidalia.png
          DESTINATION share/icons/hicolor/48x48/apps)
  install(FILES res/64x64/tor-logo.png RENAME vidalia.png
          DESTINATION share/icons/hicolor/64x64/apps)
  install(FILES res/128x128/tor-logo.png RENAME vidalia.png
          DESTINATION share/icons/hicolor/128x128/apps)
endif(NOT WIN32 AND NOT APPLE)

## Remember the location of the Vidalia binary so we can use it in
## the Windows packaging scripts
get_target_property(VIDALIA_EXECUTABLE ${vidalia_BIN} LOCATION_RelWithDebInfo)
set(VIDALIA_EXECUTABLE ${VIDALIA_EXECUTABLE}
    CACHE STRING "Location of the Vidalia executable." FORCE)

