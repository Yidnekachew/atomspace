INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Compile
ADD_EXECUTABLE(reductexample
        ReductExample)

TARGET_LINK_LIBRARIES(reductexample
        ${COGUTIL_LIBRARY}
        atomspace
        ruleengine)
