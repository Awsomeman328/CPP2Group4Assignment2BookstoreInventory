# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BSI_autogen"
  "CMakeFiles\\BSI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BSI_autogen.dir\\ParseCache.txt"
  )
endif()
