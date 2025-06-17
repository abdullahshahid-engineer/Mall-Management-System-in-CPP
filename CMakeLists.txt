cmake_minimum_required(VERSION 3.29)
project(2024_fall_itulahore_pf_se101t_project_2024_fall_a)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(2024_fall_itulahore_pf_se101t_project_2024_fall_a
    main.cpp
    registrationAndLoginSystem.cpp
    registrationAndLoginSystem.h
        employeeManagement.cpp
        employeeManagement.h
        SalesAndBillingSystem.cpp
        SalesAndBillingSystem.h
        customerManagement.cpp
        customerManagement.h)
