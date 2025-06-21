# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NekrachiJadActivityTracker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NekrachiJadActivityTracker_autogen.dir\\ParseCache.txt"
  "NekrachiJadActivityTracker_autogen"
  )
endif()
