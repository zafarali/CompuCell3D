#writing run scripts
set(LIBRARY_PATH_SYNTAX LD_LIBRARY_PATH) #default choice
if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
   set(LIBRARY_PATH_SYNTAX LD_LIBRARY_PATH)
endif(${CMAKE_SYSTEM_NAME} STREQUAL Linux)

if(${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
   set(LIBRARY_PATH_SYNTAX DYLD_LIBRARY_PATH)
endif(${CMAKE_SYSTEM_NAME} STREQUAL Darwin)

SET(COMPUCELL_INSTALL_DIR @CMAKE_INSTALL_PREFIX@)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
  #here I need to change "/" to "\" to comply with windows style paths
  set(COMPUCELL_INSTALL_DIR_WINDOWS_STYLE ${COMPUCELL_INSTALL_DIR})
  #note to replace "/" with "\" you need in fact use "escaped baskslash as a string literal". this is property of regex
  #for more info please see http://www.amk.ca/python/howto/regex/ 
  STRING(REGEX REPLACE "/" "\\\\" COMPUCELL_INSTALL_DIR_WINDOWS_STYLE ${COMPUCELL_INSTALL_DIR_WINDOWS_STYLE})

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compucell3d.bat.in.windows ${CMAKE_BINARY_DIR}/post_install_tasks/compucell3d.bat @ONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/runScript.bat.in.windows ${CMAKE_BINARY_DIR}/post_install_tasks/runScript.bat @ONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/twedit++.bat.in.windows ${CMAKE_BINARY_DIR}/post_install_tasks/twedit++.bat @ONLY)  
  
  
  
  INSTALL(FILES 
  ${CMAKE_BINARY_DIR}/post_install_tasks/compucell3d.bat
  ${CMAKE_BINARY_DIR}/post_install_tasks/runScript.bat
  ${CMAKE_BINARY_DIR}/post_install_tasks/twedit++.bat
  DESTINATION ${CMAKE_INSTALL_PREFIX})

  
  if(BUILD_CPP_ONLY_EXECUTABLE)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cc3dScript.bat.in.windows ${CMAKE_BINARY_DIR}/post_install_tasks/cc3dScript.bat @ONLY)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/post_install_tasks/cc3dScript.bat DESTINATION ${CMAKE_INSTALL_PREFIX})
    
  endif(BUILD_CPP_ONLY_EXECUTABLE)
  
  #copying SetupScript file
  INSTALL(FILES "@CMAKE_SOURCE_DIR@/core/post_install_tasks/scriptSetup.py" DESTINATION ${CMAKE_INSTALL_PREFIX})    
  
  
  INSTALL(FILES "@CMAKE_SOURCE_DIR@/core/post_install_tasks/compucell3d.bat.in.v2" DESTINATION ${CMAKE_INSTALL_PREFIX})  
  INSTALL(FILES "@CMAKE_SOURCE_DIR@/core/post_install_tasks/runScript.bat.in.v2" DESTINATION ${CMAKE_INSTALL_PREFIX})  
  INSTALL(FILES "@CMAKE_SOURCE_DIR@/core/post_install_tasks/twedit++.bat.in.v2" DESTINATION ${CMAKE_INSTALL_PREFIX})  
  
 
  
else(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    # configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compucell3d_old.sh.in.linux ${CMAKE_BINARY_DIR}/compucell3d_old.sh @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/compucell3d.sh.in.linux ${CMAKE_BINARY_DIR}/post_install_tasks/compucell3d.sh @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/runScript.sh.in.linux ${CMAKE_BINARY_DIR}/post_install_tasks/runScript.sh @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/twedit++.sh.in.linux ${CMAKE_BINARY_DIR}/post_install_tasks/twedit++.sh @ONLY)
    
        INSTALL(FILES  
            ${CMAKE_BINARY_DIR}/post_install_tasks/compucell3d.sh ${CMAKE_BINARY_DIR}/post_install_tasks/runScript.sh ${CMAKE_BINARY_DIR}/post_install_tasks/twedit++.sh
            DESTINATION ${CMAKE_INSTALL_PREFIX} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                                                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                                                            WORLD_READ WORLD_WRITE WORLD_EXECUTE
            )

    if(BUILD_CPP_ONLY_EXECUTABLE)
      configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cc3dScript.sh.in.linux ${CMAKE_BINARY_DIR}/post_install_tasks/cc3dScript.sh @ONLY)
        INSTALL(FILES  
            ${CMAKE_BINARY_DIR}/post_install_tasks/cc3dScript.sh
            DESTINATION ${CMAKE_INSTALL_PREFIX} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                                                            GROUP_READ GROUP_WRITE GROUP_EXECUTE
                                                            WORLD_READ WORLD_WRITE WORLD_EXECUTE
            )

    endif(BUILD_CPP_ONLY_EXECUTABLE)


#     file(COPY ${CMAKE_INSTALL_PREFIX}/compucell3d.sh DESTINATION ${CMAKE_INSTALL_PREFIX}/compucell3d.sh 
#          PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
#                          GROUP_READ GROUP_WRITE GROUP_EXECUTE
#                          WORLD_READ WORLD_WRITE WORLD_EXECUTE
#     )
#     configure_file(${CMAKE_CURRENT_SOURCE_DIR}/runScript.sh.in.linux ${CMAKE_INSTALL_PREFIX}/runScript.sh @ONLY)
#     if(BUILD_CPP_ONLY_EXECUTABLE)
#       configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cc3dScript.sh.in.linux ${CMAKE_INSTALL_PREFIX}/cc3dScript.sh @ONLY)
#     endif(BUILD_CPP_ONLY_EXECUTABLE)
    
    
    #file(INSTALL DESTINATION ${CMAKE_INSTALL_PREFIX} TYPE FILE FILES ${CMAKE_CURRENT_SOURCE_DIR}/compucell3d.sh.in.linux )
    
endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)

# copying vtk, Qt, python25,OPENGL libraries used by the player on Windows
# if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)   
    # INSTALL(DIRECTORY  "@CMAKE_SOURCE_DIR@/windows_libs/bin/" DESTINATION @CMAKE_INSTALL_PREFIX@/bin
        # PATTERN "*.svn" EXCLUDE
        # PATTERN "@CMAKE_SOURCE_DIR@/windows_libs/bin/*")
# endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)   
# copying vtk, Qt, python25,OPENGL libraries used by the player on Windows
if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)   
    INSTALL(DIRECTORY  "@WINDOWS_DEPENDENCIES@/bin/" DESTINATION @CMAKE_INSTALL_PREFIX@/bin
        PATTERN "*.svn" EXCLUDE
        PATTERN "@WINDOWS_DEPENDENCIES@/bin/*")
        
  file(GLOB prerequisites "@WINDOWS_DEPENDENCIES@/Prerequisites/*")
  list(REMOVE_ITEM prerequisites "@WINDOWS_DEPENDENCIES@/Prerequisites/.svn")
  INSTALL(FILES ${prerequisites} DESTINATION "@CMAKE_INSTALL_PREFIX@/Prerequisites" )  
        
endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows) 



# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Configuration/Version.py.in @CMAKE_SOURCE_DIR@/core/pythonSetupScripts/Version.py)   


# ADD_CUSTOM_COMMAND(
    # OUTPUT Version.py
    # COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/GetSVNRevisionGenerator.py    
    # # DEPENDS _CompuCell
    # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/
# )

# ADD_CUSTOM_TARGET(RevisionSVN ALL DEPENDS GetSVNRevision.py)

SET(COMPUCELL3D_REVISION 0)
EXEC_PROGRAM(${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts ARGS RevisionNumber.py
      OUTPUT_VARIABLE COMPUCELL3D_REVISION)


# if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)   
# EXEC_PROGRAM(${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts ARGS ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/SVNRevisionWindows.py  ${CMAKE_SOURCE_DIR}
      # OUTPUT_VARIABLE COMPUCELL3D_REVISION)
# else(${CMAKE_SYSTEM_NAME} STREQUAL Windows) 
# EXEC_PROGRAM(${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts ARGS ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/SVNRevision.py  
      # OUTPUT_VARIABLE COMPUCELL3D_REVISION)

# endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows) 

      
# MESSAGE("COMPUCELL3D_REVISION= ",${COMPUCELL3D_REVISION})      

# configure_file(${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/Version.py.in @CMAKE_INSTALL_PREFIX@/pythonSetupScripts/Version.py)   
configure_file(${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/Version.py.in ${CMAKE_SOURCE_DIR}/core/pythonSetupScripts/Version.py)
   
INSTALL(FILES  "@CMAKE_SOURCE_DIR@/core/pythonSetupScripts/Version.py" DESTINATION @CMAKE_INSTALL_PREFIX@/pythonSetupScripts)    

# file(GLOB GetSVNRevision "@CMAKE_SOURCE_DIR@/core/pythonSetupScripts/GetSVNRevision.py")
# INSTALL(FILES ${GetSVNRevision} DESTINATION "@CMAKE_INSTALL_PREFIX@/pythonSetupScripts")  

# INSTALL(FILES ${GetSVNRevision} DESTINATION "@CMAKE_INSTALL_PREFIX@/player/Configuration")  
# INSTALL(FILES ${GetSVNRevision} DESTINATION "@CMAKE_INSTALL_PREFIX@/Twedit++")  


INSTALL(DIRECTORY  "@CMAKE_SOURCE_DIR@/core/pythonSetupScripts" DESTINATION @CMAKE_INSTALL_PREFIX@
    PATTERN "*.svn" EXCLUDE
    PATTERN "CompuCellPythonSimulationCML.py" EXCLUDE
    PATTERN "Version.py.in*" EXCLUDE
    PATTERN "@CMAKE_SOURCE_DIR@/core/pythonSetupScripts/*")

INSTALL(FILES  "@CMAKE_SOURCE_DIR@/core/pythonSetupScripts/CompuCellPythonSimulationCML.py" DESTINATION @CMAKE_INSTALL_PREFIX@/player )    

INSTALL(DIRECTORY  "@CMAKE_SOURCE_DIR@/core/Demos" DESTINATION @CMAKE_INSTALL_PREFIX@
    PATTERN "*.svn" EXCLUDE
    PATTERN "@CMAKE_SOURCE_DIR@/core/Demos/*")

# INSTALL(DIRECTORY  "@CMAKE_SOURCE_DIR@/core/examples_PythonTutorial" DESTINATION @CMAKE_INSTALL_PREFIX@
    # PATTERN "*.svn" EXCLUDE
    # PATTERN "@CMAKE_SOURCE_DIR@/core/examples_PythonTutorial/*")

# Copying images    
INSTALL(DIRECTORY  "@CMAKE_SOURCE_DIR@/core/icons" DESTINATION @CMAKE_INSTALL_PREFIX@
    PATTERN "*.svn" EXCLUDE
    PATTERN "@CMAKE_SOURCE_DIR@/core/icons/*")
    
    