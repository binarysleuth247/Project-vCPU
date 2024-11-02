# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Assembler_autogen"
  "CMakeFiles\\Assembler_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Assembler_autogen.dir\\ParseCache.txt"
  )
endif()
