# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NekrachiJadActivityTracker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NekrachiJadActivityTracker_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\core_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\core_autogen.dir\\ParseCache.txt"
  "NekrachiJadActivityTracker_autogen"
  "core_autogen"
  "test\\CMakeFiles\\runAllTests_autogen.dir\\AutogenUsed.txt"
  "test\\CMakeFiles\\runAllTests_autogen.dir\\ParseCache.txt"
  "test\\lib\\googletest\\googlemock\\CMakeFiles\\gmock_autogen.dir\\AutogenUsed.txt"
  "test\\lib\\googletest\\googlemock\\CMakeFiles\\gmock_autogen.dir\\ParseCache.txt"
  "test\\lib\\googletest\\googlemock\\CMakeFiles\\gmock_main_autogen.dir\\AutogenUsed.txt"
  "test\\lib\\googletest\\googlemock\\CMakeFiles\\gmock_main_autogen.dir\\ParseCache.txt"
  "test\\lib\\googletest\\googlemock\\gmock_autogen"
  "test\\lib\\googletest\\googlemock\\gmock_main_autogen"
  "test\\lib\\googletest\\googletest\\CMakeFiles\\gtest_autogen.dir\\AutogenUsed.txt"
  "test\\lib\\googletest\\googletest\\CMakeFiles\\gtest_autogen.dir\\ParseCache.txt"
  "test\\lib\\googletest\\googletest\\CMakeFiles\\gtest_main_autogen.dir\\AutogenUsed.txt"
  "test\\lib\\googletest\\googletest\\CMakeFiles\\gtest_main_autogen.dir\\ParseCache.txt"
  "test\\lib\\googletest\\googletest\\gtest_autogen"
  "test\\lib\\googletest\\googletest\\gtest_main_autogen"
  "test\\runAllTests_autogen"
  )
endif()
