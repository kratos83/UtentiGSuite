project(utenti)

cmake_minimum_required(VERSION 2.6)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules )

if(WIN32)
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11 -mwindows" )
ELSE()
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11" )
ENDIF()

set(utenti "utenti")

set(utenti_includes
${CMAKE_BINARY_DIR}/src
)

include_directories(${utenti_includes})

set(utenti_moc_hdrs 
	mainwindow.h
)

qt5_wrap_cpp(utenti_mocs ${utenti_moc_hdrs})

set(utenti_uis 
	mainwindow.ui
)
qt5_wrap_ui(utenti_ui_hdrs ${utenti_uis})

set(utenti_srcs 
	mainwindow.cpp
	main.cpp
)

qt5_add_resources(RESOURCE_FILES images.qrc) 

LINK_LIBRARIES(-lpthread)



IF(WIN32)
	SET(WINRC "${CMAKE_CURRENT_BINARY_DIR}/fabariagest.obj")
	ADD_DEFINITIONS(-D__USE_MINGW_ANSI_STDIO=1)
	ADD_CUSTOM_COMMAND(OUTPUT ${WINRC}
						COMMAND ${WINDRES}
							-I${CMAKE_CURRENT_SOURCE_DIR}
							-o${WINRC}
							-i${CMAKE_CURRENT_BINARY_DIR}/winicon.rc
						DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/winicon.rc)

ENDIF(WIN32)

ADD_EXECUTABLE(utenti ${utenti_srcs} ${utenti_mocs} ${utenti_ui_hdrs} ${RESOURCE_FILES} ${SOURCE_FILES} ${WINRC})

target_link_libraries( utenti
  xlsx_utenti
  Qt5::Widgets Qt5::Gui 
  Qt5::Sql Qt5::Core 
  Qt5::PrintSupport 
)

IF(WIN32)
    INSTALL(TARGETS utenti RUNTIME DESTINATION .)
	INSTALL(FILES
		"${MINGW_PREFIX}/bin/Qt5Core.dll"
		"${MINGW_PREFIX}/bin/Qt5Gui.dll"
		"${MINGW_PREFIX}/bin/Qt5Svg.dll"
		"${MINGW_PREFIX}/bin/Qt5Xml.dll"
		"${MINGW_PREFIX}/bin/Qt5Network.dll"
		"${MINGW_PREFIX}/bin/Qt5Sql.dll"
		"${MINGW_PREFIX}/bin/Qt5Widgets.dll"
		"${MINGW_PREFIX}/bin/Qt5PrintSupport.dll"
		"${MINGW_PREFIX}/bin/libexpat-1.dll"
		"${MINGW_PREFIX}/bin/libjpeg-8.dll"
		"${MINGW_PREFIX}/bin/libpng16-16.dll"
		"${MINGW_PREFIX}/bin/libstdc++-6.dll"
		"${MINGW_PREFIX}/bin/libtiff-5.dll"
		"${MINGW_PREFIX}/bin/libtiffxx-5.dll"
		"${MINGW_PREFIX}/bin/libturbojpeg.dll"
		"${MINGW_PREFIX}/bin/zlib1.dll"
		"${MINGW_PREFIX}/bin/libwinpthread-1.dll"
		"${MINGW_PREFIX}/bin/libsqlite3-0.dll"
		"${MINGW_PREFIX}/bin/libiconv-2.dll"
		"${MINGW_PREFIX}/bin/libfreetype-6.dll"
		"${MINGW_PREFIX}/bin/libglib-2.0-0.dll"
		"${MINGW_PREFIX}/bin/libharfbuzz-0.dll"
		"${MINGW_PREFIX}/bin/libpcre16-0.dll"
		"${MINGW_PREFIX}/bin/libpcre2-16-0.dll"
		"${MINGW_PREFIX}/bin/libintl-8.dll"
		"${MINGW_PREFIX}/bin/libbz2-1.dll"
		"${MINGW_PREFIX}/bin/libcurl-4.dll"
        "${MINGW_PREFIX}/bin/libpcre-1.dll"
        "${MINGW_PREFIX}/bin/libpcre32-0.dll"
        "${MINGW_PREFIX}/bin/libidn-12.dll"
        "${MINGW_PREFIX}/bin/liblcms2-2.dll"
        "${MINGW_PREFIX}/bin/libopenjpeg-1.dll"
        "${MINGW_PREFIX}/bin/libopenjp2-7.dll"
        "${MINGW_PREFIX}/bin/libgraphite2.dll"
        "${MINGW_PREFIX}/bin/liblzma-5.dll"
         "${MINGW_PREFIX}/bin/libidn2-0.dll"
         "${MINGW_PREFIX}/bin/libunistring-2.dll"
	 	"${MINGW_PREFIX}/bin/libssp-0.dll"
		DESTINATION .
		)
    INSTALL(FILES "${MINGW_PREFIX}/bin/libopenjp2-7.dll" DESTINATION . RENAME "libopenjp2.dll")
    IF(WIN64)
    INSTALL(FILES 
        "${MINGW_PREFIX}/bin/libgcc_s_seh-1.dll"
        DESTINATION . )
ELSE ()
    INSTALL(FILES 
        "${MINGW_PREFIX}/bin/libgcc_s_sjlj-1.dll"
        DESTINATION . )
ENDIF(WIN64)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/sqldrivers/qsqlite.dll" 
		"${MINGW_PREFIX}/lib/qt/plugins/sqldrivers/sqlitecipher.dll"
		DESTINATION ./sqldrivers
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/platforms/qminimal.dll" 
		"${MINGW_PREFIX}/lib/qt/plugins/platforms/qwindows.dll"
		DESTINATION ./platforms
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/audio/qtaudio_windows.dll" 
		DESTINATION ./audio
		)
	INSTALL(FILES
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qgif.dll"
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qico.dll"
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qjpeg.dll"
		"${MINGW_PREFIX}/lib/qt/plugins/imageformats/qsvg.dll"
		DESTINATION ./imageformats
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt/plugins/printsupport/windowsprintersupport.dll" 
		DESTINATION ./printsupport
		)
    INSTALL(FILES
        "${MINGW_PREFIX}/lib/qt/plugins/styles/qwindowsvistastyle.dll" 
		DESTINATION ./styles
		)
	INSTALL(FILES
		"dat.db"
		DESTINATION . )
ELSE()
    INSTALL( TARGETS utenti RUNTIME DESTINATION /opt/utenti)
    INSTALL( FILES "utentibin" DESTINATION /usr/bin PERMISSIONS
		OWNER_READ OWNER_WRITE OWNER_EXECUTE
		GROUP_READ GROUP_EXECUTE
		WORLD_READ WORLD_EXECUTE)
    INSTALL( FILES "images/logo.png" DESTINATION /opt/utenti)
endif()
