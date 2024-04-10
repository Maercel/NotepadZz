# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Notepad_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Notepad_autogen.dir\\ParseCache.txt"
  "Notepad_autogen"
  )
endif()
