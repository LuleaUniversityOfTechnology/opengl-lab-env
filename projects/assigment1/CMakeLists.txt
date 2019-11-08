#--------------------------------------------------------------------------
# snowflake project
#--------------------------------------------------------------------------

FILE(GLOB snowflake_headers code/*.h)
FILE(GLOB snowflake_sources code/*.cc)

SET(files_snowflake ${snowflake_headers} ${snowflake_sources})
SOURCE_GROUP("snowflake" FILES ${files_snowflake})

ADD_EXECUTABLE(snowflake ${files_snowflake})
TARGET_LINK_LIBRARIES(snowflake core render)
ADD_DEPENDENCIES(snowflake core render)