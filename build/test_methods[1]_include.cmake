if(EXISTS "/home/poyoyonland/projects/Hakoiricpp/build/test_methods[1]_tests.cmake")
  include("/home/poyoyonland/projects/Hakoiricpp/build/test_methods[1]_tests.cmake")
else()
  add_test(test_methods_NOT_BUILT test_methods_NOT_BUILT)
endif()