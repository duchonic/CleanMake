# CMake generated Testfile for 
# Source directory: W:/Work/evatec_GSM/gsm1102/CleanMake/CleanMake
# Build directory: W:/Work/evatec_GSM/gsm1102/CleanMake/CleanMake/out/build/x86-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TEST1 "catch_test" "COMMAND" "$<TARGET_FILE:testing>" "--success")
set_tests_properties(TEST1 PROPERTIES  _BACKTRACE_TRIPLES "W:/Work/evatec_GSM/gsm1102/CleanMake/CleanMake/CMakeLists.txt;52;add_test;W:/Work/evatec_GSM/gsm1102/CleanMake/CleanMake/CMakeLists.txt;0;")
subdirs("source")
subdirs("customLibs")
subdirs("demo")
subdirs("test")
