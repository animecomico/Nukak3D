###### BEGIN GPL LICENSE BLOCK#####
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
# The Original Code is Copyright (C) 2007-2010 by Bioingenium Research Group.
# Bogota - Colombia
# All rights reserved.
#
# Author(s): Alexander Pinz�n Fern�ndez.
#
###### END GPL LICENSE BLOCK#####

# @file CmakeList.txt
# @brief Project configuration file.
# @author Alexander Pinzon Fernandez
# @version 3.0
# @date 18/11/2007 12:22 a.m.
PROJECT(nukak3d)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.8 FATAL_ERROR)
IF(APPLE)
	SET(SISPRO universal)
ELSE(APPLE)
	SET(SISPRO ${CMAKE_SYSTEM_PROCESSOR})
ENDIF(APPLE)
SET(SISTOPER ${CMAKE_SYSTEM_NAME}-${SISPRO})



# Define binary path
SET(EXECUTABLE_OUTPUT_PATH ${nukak3d_BINARY_DIR}/bin
 CACHE PATH "Output directory for building executable."
)

# Define library path
SET(LIBRARY_OUTPUT_PATH ${nukak3d_BINARY_DIR}/lib
 CACHE PATH "Output directory for building libraries."
)

# Define CMakeModules path
SET(CMAKE_MODULE_PATH ${nukak3d_SOURCE_DIR}/CMakeModules)

SET(nukak3d_VERSION_MAJOR 5)
SET(nukak3d_VERSION_MINOR 0)
SET(nukak3d_VERSION_BUILD 0)
SET(nukak3d_VERSION "${nukak3d_VERSION_MAJOR}.${nukak3d_VERSION_MINOR}.${nukak3d_VERSION_BUILD}")

#INCLUDE(${nukak3d_SOURCE_DIR}/extern/${SISTOPER}/vtk/lib/vtk-5.0/UseVTK.cmake)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(nukak3d_REQUIRED_C_FLAGS    "${nukak3d_REQUIRED_C_FLAGS}    -DVTK_MAJOR_VERSION=${VTK_MAJOR_VERSION}")
SET(nukak3d_REQUIRED_CXX_FLAGS  "${nukak3d_REQUIRED_CXX_FLAGS}  -DVTK_MAJOR_VERSION=${VTK_MAJOR_VERSION}")
SET(nukak3d_REQUIRED_C_FLAGS    "${nukak3d_REQUIRED_C_FLAGS}    -DVTK_MINOR_VERSION=${VTK_MINOR_VERSION}")
SET(nukak3d_REQUIRED_CXX_FLAGS  "${nukak3d_REQUIRED_CXX_FLAGS}  -DVTK_MINOR_VERSION=${VTK_MINOR_VERSION}")

INCLUDE("${VTK_CMAKE_DIR}/vtkWrapTcl.cmake")

IF("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" EQUAL "5.0")
  IF(VTK_INSTALL_PREFIX)
    IF(NOT EXISTS "${VTK_CMAKE_DIR}/vtkWrapperInit.data.in")
      MESSAGE("Vtk requerido.")
    ENDIF(NOT EXISTS "${VTK_CMAKE_DIR}/vtkWrapperInit.data.in")
  ELSE(VTK_INSTALL_PREFIX)
    SET(VTK_WRAP_TCL3_INIT_DIR "${VTK_SOURCE_DIR}/Wrapping")
    SET(VTK_WRAP_PYTHON3_INIT_DIR "${VTK_SOURCE_DIR}/Wrapping")
  ENDIF(VTK_INSTALL_PREFIX)
ENDIF("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" EQUAL "5.0")

#--------------
# Shared libraries
#IF( VTK_BUILD_SHARED_LIBS )
  SET(nukak3d_LIBS_STYLE "SHARED")
#ELSE( VTK_BUILD_SHARED_LIBS )
#  SET(nukak3d_LIBS_STYLE "STATIC")
#ENDIF( VTK_BUILD_SHARED_LIBS )


#INCLUDE(${nukak3d_SOURCE_DIR}/extern/${SISTOPER}/itk/lib/InsightToolkit/UseITK.cmake)
FIND_PACKAGE(ITK)
IF(ITK_FOUND)
	INCLUDE(${ITK_USE_FILE})		
	SET(nukak3d_REQUIRED_C_FLAGS    "${nukak3d_REQUIRED_C_FLAGS}    -Dnukak3d_USE_ITK")
	SET(nukak3d_REQUIRED_CXX_FLAGS  "${nukak3d_REQUIRED_CXX_FLAGS}  -Dnukak3d_USE_ITK")
	IF( ITK_BUILD_SHARED )
		SET( ITK_LIBS_STYLE "SHARED" )
	ELSE( ITK_BUILD_SHARED )
		SET( ITK_LIBS_STYLE "STATIC" )
	ENDIF( ITK_BUILD_SHARED )
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR "ITK not found. Please set ITK_DIR.")
ENDIF(ITK_FOUND)


IF(WIN32)
	SET(wxWidgets_USE_LIBS base core adv aui xrc xml html)
ELSE(WIN32)
	SET(wxWidgets_USE_LIBS base core gl adv aui xrc xml html)
ENDIF(WIN32)
 
IF(APPLE)
	FIND_PACKAGE(wxWidgets2)
ELSE(APPLE)
	IF(WIN32)
		FIND_PACKAGE(wxWidgets REQUIRED base core adv aui xrc xml html)
	ELSE(WIN32)
		FIND_PACKAGE(wxWidgets REQUIRED base core gl adv aui xrc xml html)
	ENDIF(WIN32)
ENDIF(APPLE)

IF(wxWidgets_FOUND)
	INCLUDE(${wxWidgets_USE_FILE})
	OPTION(wxWidgets_SHARED "wxWidgets build with Shared libraries?" OFF)
	IF( wxWidgets_SHARED )
		SET( wxWidgets_BUILD_SHARED_LIBS "ON" )      
		SET( wxWidgets_LIBS_STYLE "SHARED")
		ADD_DEFINITIONS(-DWXMAKINGDLL_ADDON)
	ELSE ( wxWidgets_SHARED )
		SET( wxWidgets_BUILD_SHARED_LIBS "OFF")      
		SET( wxWidgets_LIBS_STYLE "STATIC")
		REMOVE_DEFINITIONS(-DWXMAKINGDLL_ADDON)
	ENDIF( wxWidgets_SHARED )

	IF(UNIX AND NOT APPLE)
		FIND_PACKAGE(GTK-2 REQUIRED)     
		LINK_DIRECTORIES(${GTK_LINK_DIRS})
		SET(wxWidgets_LIBRARIES
			${wxWidgets_LIBRARIES}
			${GTK_LINK_LIBS}
		)
			
	ENDIF(UNIX AND NOT APPLE)

	ELSE(wxWidgets_FOUND)
		MESSAGE(ERROR " wxWidgets not found.")
ENDIF(wxWidgets_FOUND)  

FIND_PACKAGE(DCMTK)
IF(DCMTK_FOUND)
	SET(nukak3d_REQUIRED_C_FLAGS    "${nukak3d_REQUIRED_C_FLAGS}    -Dnukak3d_USE_DCMTK")
	SET(nukak3d_REQUIRED_CXX_FLAGS  "${nukak3d_REQUIRED_CXX_FLAGS}  -Dnukak3d_USE_DCMTK")
ELSE(DCMTK_FOUND)
	MESSAGE(FATAL_ERROR "DCMTK not found. Please set DCMTK_DIR in advance mode.")
ENDIF(DCMTK_FOUND)

FIND_PACKAGE(vtkINRIA3D REQUIRED)
INCLUDE(${vtkINRIA3D_USE_FILE})		
SET(nukak3d_REQUIRED_C_FLAGS    "${nukak3d_REQUIRED_C_FLAGS}    -Dnukak3d_USE_vtkINRIA3D")
SET(nukak3d_REQUIRED_CXX_FLAGS  "${nukak3d_REQUIRED_CXX_FLAGS}  -Dnukak3d_USE_vtkINRIA3D")

SET(nukak3d_REQUIRED_C_FLAGS    "${nukak3d_REQUIRED_C_FLAGS}    -DNKENGINE_EXPORTS")
SET(nukak3d_REQUIRED_CXX_FLAGS  "${nukak3d_REQUIRED_CXX_FLAGS}  -DNKENGINE_EXPORTS")

SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}    ${nukak3d_REQUIRED_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  ${nukak3d_REQUIRED_CXX_FLAGS}")

CONFIGURE_FILE (
   ${PROJECT_SOURCE_DIR}/doc/doxygen.config.in
   ${PROJECT_BINARY_DIR}/doxygen.config IMMEDIATE @ONLY
)

FIND_PACKAGE(Doxygen)
IF (DOXYGEN)
 ADD_CUSTOM_TARGET(doc
   ${DOXYGEN}
   ${PROJECT_BINARY_DIR}/doxygen.config
 )
ENDIF(DOXYGEN) 

SUBDIRS(
include
src
resources
doc
)

SET(CPACK_PACKAGE_NAME "Nukak3d")
SET(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${nukak3d_VERSION_MAJOR}.${nukak3d_VERSION_MINOR}.${nukak3d_VERSION_BUILD}-${SISTOPER}")
SET(CPACK_PACKAGE_VENDOR "Bioingenium Research Group, Universidad Nacional de Colombia.")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Nukak3d")
SET(CPACK_PACKAGE_VERSION "${nukak3d_VERSION_MAJOR}.${nukak3d_VERSION_MINOR}.${nukak3d_VERSION_BUILD}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${nukak3d_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${nukak3d_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${nukak3d_VERSION_BUILD}")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "nukak3d ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Readme.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/doc/Licence.txt")
SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/doc/Readme.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/doc/Readme.txt")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
IF(WIN32 OR APPLE)
  SET (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP 1)
  INCLUDE(InstallRequiredSystemLibraries)
  SET(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources\\\\nukak3d.ico")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  SET(CPACK_NSIS_HELP_LINK "http://www.bioingenium.unal.edu.co")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http://www.bioingenium.unal.edu.co")
  SET(CPACK_NSIS_CONTACT "apinzonf@unal.edu.co")
  SET(CPACK_NSIS_MODIFY_PATH ON)
  IF(WIN32)
    IF(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
		INSTALL_PROGRAMS(/bin ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
	ENDIF(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
	SET(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "Nukak3D")
  ELSE(WIN32)
	SET(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "Nukak3D")
  ENDIF(WIN32)
ELSE(WIN32 OR APPLE)
  SET(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "Nukak3D")
  INCLUDE(InstallRequiredSystemLibrariesLinux)
  IF(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
		INSTALL_PROGRAMS(/bin ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
  ENDIF(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
  
  INCLUDE(UseRPMTools)
  IF (RPMTools_FOUND)
    RPMTools_ADD_RPM_TARGETS(${PROJECT_NAME} "packaging/${PROJECT_NAME}.spec.in")
  ENDIF (RPMTools_FOUND)

  SET(CPACK_DEBIAN_PACKAGE_NAME "nuakk3d")
  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk2.0-0 (>= 2.14.4-0ubuntu1), dcmtk (>= 3.5.4-3)")
  SET(DEBIAN_PACKAGE_DEPENDS "libgtk2.0-0 (>= 2.14.4-0ubuntu1), dcmtk (>= 3.5.4-3)")
  SET(CPACK_DEBIAN_PACKAGE_VERSION "${nukak3d_VERSION_MAJOR}.${nukak3d_VERSION_MINOR}.${nukak3d_VERSION_BUILD}")
  SET(DEBIAN_PACKAGE_MAINTAINER "Alexander Pinzon Fernande apinzonf@gmail.com")
  SET(DEBIAN_PACKAGE_DESCRIPTION "Nukak3d is a flexible architecture that 
integrates general-purpose graphics libraries such as 
VTK, ITK, VTKInria3D, OpenGL, under a graphical user 
interface (wxWidgets) for three-dimensional visualization 
and processing of medical images.
 .
This product has been developed by Bioingenium Research Group, 
within the frame of the computer graphics project at the 
National University of Colombia")
  SET(DEBIAN_PACKAGE_SECTION "Medical")
  INCLUDE(UseDebian)
  IF(DEBIAN_FOUND)
    ADD_DEBIAN_TARGETS(${PROJECT_NAME})
   ENDIF(DEBIAN_FOUND)

ENDIF(WIN32 OR APPLE)

INCLUDE(CPack)
