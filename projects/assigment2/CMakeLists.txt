#--------------------------------------------------------------------------
# 3dtriangulation project
#--------------------------------------------------------------------------

FILE(GLOB 3dtriangulation_headers code/*.h)
FILE(GLOB 3dtriangulation_sources code/*.cc)

SET(files_3dtriangulation ${3dtriangulation_headers} ${3dtriangulation_sources})
SOURCE_GROUP("3dtriangulation" FILES ${files_3dtriangulation})

ADD_EXECUTABLE(3dtriangulation ${files_3dtriangulation})
TARGET_LINK_LIBRARIES(3dtriangulation core render)
ADD_DEPENDENCIES(3dtriangulation core render)