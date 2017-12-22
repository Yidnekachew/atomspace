INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Compile
ADD_EXECUTABLE(reductexample
        ReductExample)

TARGET_LINK_LIBRARIES(reductexample
        ${COGUTIL_LIBRARY}
        atomspace
        ruleengine)

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/examples/reduct/involution/involution_rule.scm
        ${PROJECT_BINARY_DIR}/examples/reduct/involution/involution_rule.scm)

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/examples/reduct/involution/reduct.scm
        ${PROJECT_BINARY_DIR}/examples/reduct/involution/reduct.scm)

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/examples/reduct/involution/test.scm
        ${PROJECT_BINARY_DIR}/examples/reduct/involution/test.scm)
