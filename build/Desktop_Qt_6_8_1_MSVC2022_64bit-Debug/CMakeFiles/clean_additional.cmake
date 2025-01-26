# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ShapeRecognition_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ShapeRecognition_autogen.dir\\ParseCache.txt"
  "ShapeRecognition_autogen"
  )
endif()
