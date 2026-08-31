#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ads::AdsLib" for configuration "Debug"
set_property(TARGET Ads::AdsLib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ads::AdsLib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/AdsLib.lib"
  )

list(APPEND _cmake_import_check_targets Ads::AdsLib )
list(APPEND _cmake_import_check_files_for_Ads::AdsLib "${_IMPORT_PREFIX}/lib/AdsLib.lib" )

# Import target "Ads::AdsTool" for configuration "Debug"
set_property(TARGET Ads::AdsTool APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ads::AdsTool PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/adstool.exe"
  )

list(APPEND _cmake_import_check_targets Ads::AdsTool )
list(APPEND _cmake_import_check_files_for_Ads::AdsTool "${_IMPORT_PREFIX}/bin/adstool.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
