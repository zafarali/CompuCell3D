ADD_EXECUTABLE(TestsSimthread TestsSimthread.cpp)
TARGET_LINK_LIBRARIES(TestsSimthread cppunit simthreadShared)
ADD_TEST(SimthreadTests TestsSimthread)