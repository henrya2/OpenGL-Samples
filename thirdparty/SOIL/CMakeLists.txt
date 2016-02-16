cmake_minimum_required (VERSION 2.8)
PROJECT("SOIL")

SET( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
SET( INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# -------------------------------------------
# Files
# -------------------------------------------

# Source Files
SET(SOIL_SRCS
	${SRC_DIR}/image_helper.c
    ${SRC_DIR}/stb_image_aug.c
    ${SRC_DIR}/image_DXT.c
    ${SRC_DIR}/SOIL.c
)

# Header Files
SET(SOIL_HDRS
	${INCLUDE_DIR}/image_helper.h
    ${INCLUDE_DIR}/stb_image_aug.h
    ${INCLUDE_DIR}/image_DXT.h
    ${INCLUDE_DIR}/stbi_DDS_aug_c.h
    ${INCLUDE_DIR}/stbi_DDS_aug.h
    ${INCLUDE_DIR}/SOIL.h
)

INCLUDE_DIRECTORIES( ${INCLUDE_DIR} )

# -------------------------------------------
# Static Library
# -------------------------------------------
ADD_LIBRARY(SOIL_Static STATIC ${SOIL_SRCS} ${SOIL_HDRS})

# Build Settings
SET_PROPERTY(TARGET SOIL_Static PROPERTY OUTPUT_NAME "SOIL")