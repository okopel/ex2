cmake_minimum_required(VERSION 3.12)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2 MyImplementation.cpp MyImplementation.h MyReservation.cpp MyCustomer.cpp MyFlight.cpp MyPlane.cpp MyDate.cpp myTable.cpp MyEmployee.cpp IDgenerator.cpp main.cpp MyFlight.h MyPlane.h MyReservation.h MyEmployee.h MyCustomer.h MyTabels.h IDgenerator.h)