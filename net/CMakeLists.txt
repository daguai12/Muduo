aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} NET_SRC)

list(APPEND NET_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/poller/DefaultPoller.cc
)

set(NET_SRC ${NET_SRC} PARENT_SCOPE)

add_subdirectory(tests)


