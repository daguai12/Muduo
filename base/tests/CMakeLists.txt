# 测试Timestamp类
add_executable(timestamp_test Timestamp_test.cc)
target_link_libraries(timestamp_test mymuduo)
add_test(NAME TimestampTest COMMAND timestamp_test)

# 测试Logger类
add_executable(logger_test Logger_test.cc)
target_link_libraries(logger_test mymuduo)
add_test(NAME LoggerTest COMMAND logger_test)
