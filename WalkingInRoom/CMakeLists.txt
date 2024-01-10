add_executable (WalkingInRoom "main.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WalkingInRoom PROPERTY CXX_STANDARD 20)
endif()