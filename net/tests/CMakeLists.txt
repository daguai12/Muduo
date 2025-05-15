add_executable(inetAddress_test InetAddress_test.cc)
target_link_libraries(inetAddress_test mymuduo)
add_test(NAME InetAddressTest COMMAND inetAddress_test)


