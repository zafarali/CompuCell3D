
if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
SET(LIBS
  CompuCellLibShared
  #AutomatonStatic
  #BoundaryStatic
  Field3DStatic
  #Potts3DStatic

   # XercesUtilsStatic
   BasicUtilsStatic
   PublicUtilitiesStatic
   UnitsStatic
   # XMLCerealStatic
   # ${XERCESC_LIBRARY}
   ${PYTHON_LIBRARIES}

)
else(${CMAKE_SYSTEM_NAME} STREQUAL Windows)

INCLUDE_DIRECTORIES(/usr/include)

SET(DOLFIN_LIBS )

if(USE_DOLFIN) 
    SET(DOLFIN_LIBS dolfin)
endif()

SET(LIBS
  CompuCellLibShared
  #AutomatonShared
  #BoundaryShared
  Field3DShared
  #Potts3DShared

   # XercesUtilsShared
   BasicUtilsShared
   PublicUtilitiesShared
   UnitsShared
   # XMLCerealShared
   # ${XERCESC_LIBRARY}
   ${PYTHON_LIBRARIES}
   ${DOLFIN_LIBS}

)


endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)



SET(LIBS_AUX
   ChemotaxisSimpleShared
   ChemotaxisShared
   MitosisShared
   MitosisSteppableShared
   NeighborTrackerShared
   PixelTrackerShared
   BoundaryPixelTrackerShared   
   ContactLocalFlexShared
   ContactLocalProductShared
   CellOrientationShared
   PolarizationVectorShared
   ElasticityTrackerShared
   ElasticityShared   
   PlasticityTrackerShared
   PlasticityShared
   FocalPointPlasticityShared
   ContactMultiCadShared
   AdhesionFlexShared
   ConnectivityLocalFlexShared
   ConnectivityGlobalShared
   # LengthConstraintLocalFlexShared
   LengthConstraintShared
   MomentOfInertiaShared
   SecretionShared
   VolumeTrackerShared
   CenterOfMassShared
#AutogeneratedModules - DO NOT REMOVE THIS LINE IT IS USED BY TWEDIT TO LOCATE CODE INSERTION POINT
#CleaverMeshDumper_autogenerated
CleaverMeshDumperShared
# # # #CGALMeshDumper_autogenerated
# # # CGALMeshDumperShared
#ContactOrientation_autogenerated
ContactOrientationShared
#BoundaryMonitor_autogenerated
BoundaryMonitorShared
#CellTypeMonitor_autogenerated
CellTypeMonitorShared
#Polarization23_autogenerated
Polarization23Shared
#ClusterSurface_autogenerated
ClusterSurfaceShared
#ClusterSurfacetracker_autogenerated
ClusterSurfaceTrackerShared

   
   PyPlugin
# #    VolumeShared
# #    SurfaceShared
# #    VolumeTrackerShared
# #    SurfaceTrackerShared
# #    VolumeLocalFlexShared
# #    SurfaceLocalFlexShared
# #    VolumeFlexShared
# #    SurfaceFlexShared
# #    CenterOfMassShared
# #    ChemotaxisShared
# #    PlayerSettingsShared
# #    CellTypeShared
# #    ContactShared
# #    UniformFieldInitializerShared
# #    BlobFieldInitializerShared
# #    FoamDataOutputShared
# #    PDESolversShared
# #    BoxWatcherShared
# #    PIFInitializerShared
# #    PIFDumperShared
# #    PDESolverCallerShared
# #    CompartmentShared
# #    SimpleClockShared
# #    ChemotaxisDictyShared
# #    DictyShared
# #    SimpleArrayShared
# #    OrientedContactShared
# #    MomentOfInertiaShared
# #    LengthConstraintShared
   # # MolecularContactShared
# #    RearrangementShared
# #    ConnectivityShared
# #    StretchnessShared
# #    ExternalPotentialShared   
   
)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COMPUCELL3D_SOURCE_DIR}/core
    ${COMPUCELL3D_SOURCE_DIR}/core/CompuCell3D
    ${COMPUCELL3D_SOURCE_DIR}/core/CompuCell3D/plugins
    ${COMPUCELL3D_SOURCE_DIR}/core/pyinterface/PyPlugin
    # ${COMPUCELL3D_SOURCE_DIR}/BasicUtils
    # ${COMPUCELL3D_SOURCE_DIR}/XercescUtils
    # ${COMPUCELL3D_SOURCE_DIR}/XMLCereal
    # ${XERCESC_INCLUDE_DIR}
    #${PYINTERFACE_SRC_DIR}/PyPlugin
)

# configure compilation of modules for old and new player. Old player modules are compiled with ("threads"=0) option and new are compiled with ("threads"=1) option
# set(thread_option \(\"threads\"=1\))
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CompuCell.i.in ${CMAKE_CURRENT_SOURCE_DIR}/CompuCell.i)

# set(thread_option )
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CompuCell.i.in ${CMAKE_CURRENT_SOURCE_DIR}/CompuCellOld.i)




SET_SOURCE_FILES_PROPERTIES(CompuCell.i  PROPERTIES CPLUSPLUS ON)
# SET_SOURCE_FILES_PROPERTIES(CompuCellPython.i CompuCellAuxPython.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(CompuCell python CompuCell.i)


if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
  SET_TARGET_PROPERTIES(_CompuCell PROPERTIES SUFFIX ".pyd") # changes dll name to pyd sop that it is compatible with new Python standard
endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)

SWIG_LINK_LIBRARIES(CompuCell ${LIBS} ${LIBS_AUX})
#TARGET_LINK_LIBRARIES(_CompuCell ${LIBS})


install_targets(/lib/python _CompuCell)

set(python_files_path ${CMAKE_BINARY_DIR}/core/pyinterface/CompuCellPython)

#THIS IS EXAMPLE OF WORKING COMMAND 
# ADD_CUSTOM_COMMAND(
#     OUTPUT CompuCell.py.mod
#     COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/core/pyinterface/swigmodifier.py ${python_files_path}/CompuCell.py   
#     DEPENDS _CompuCell
# )
# 
# ADD_CUSTOM_TARGET(_swigmodifier ALL DEPENDS CompuCell.py.mod)

INSTALL(FILES ${python_files_path}/CompuCell.py 
	      DESTINATION lib/python)

# add_subdirectory(CompuCellPythonOld)

