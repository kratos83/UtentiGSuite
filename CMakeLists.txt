CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

PROJECT(utenti)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

INCLUDE(AddFileDependencies)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckFunctionExists)
INCLUDE(FindPkgConfig)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "3")

#SET(VERSION_SUFFIX "")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
IF(VERSION_SUFFIX)
	SET(VERSION "${VERSION}-${VERSION_SUFFIX}")
ENDIF(VERSION_SUFFIX)

INCLUDE(DetectMachine)

LIST(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Sql REQUIRED)
FIND_PACKAGE(Qt5PrintSupport REQUIRED)


# make sub-directories
ADD_SUBDIRECTORY(xlsx)
ADD_SUBDIRECTORY(src)

#
# add distclean-target
#
ADD_CUSTOM_TARGET(distclean
			COMMAND make clean
			COMMAND rm -rf `find -name cmake_install.cmake` `find -name Makefile` `find -type d -name CMakeFiles` CMakeCache.txt)

#
# display configuration information
#

MESSAGE("\n"
"Installation Summary\n"
"--------------------\n"
"* Install Directory           : ${CMAKE_INSTALL_PREFIX}\n"
"* Build type                  : ${CMAKE_BUILD_TYPE}\n"
"* Platform                    : ${CMAKE_SYSTEM_PROCESSOR} (${Machine})\n"
)

MESSAGE(
"\n"
"-----------------------------------------------------------------\n"
"IMPORTANT:\n"
"after installing missing packages, remove CMakeCache.txt before\n"
"running cmake again!\n"
"-----------------------------------------------------------------\n"
"\n\n")

INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Utenti")
SET(CPACK_PACKAGE_VENDOR "Angelo Scarnà")

SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")

IF(VERSION_SUFFIX)
	SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_SUFFIX}")
ENDIF(VERSION_SUFFIX)

set(CPACK_NSIS_CREATE_ICONS_EXTRA "
    	CreateShortCut \\\"$DESKTOP\\\\Utenti.lnk\\\" \\\"$INSTDIR\\\\utenti.exe\\\"")
	set(CPACK_NSIS_DELETE_ICONS_EXTRA "
    		Delete \\\"$DESKTOP\\\\Utenti.lnk\\\"")
SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "Utenti-${VERSION_SUFFIX}")
INCLUDE(CPack)
