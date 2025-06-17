cmake_minimum_required(VERSION 3.29)
project(spring2025_se102_oop_project__j)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(spring2025_se102_oop_project__j
        Mall.cpp
    Mall.h
    Product.cpp
    Product.h
        Store.h
        Store.cpp
        Inventory.h
        Inventory.cpp
        main.cpp
        NonPerishableProduct.h
        NonPerishableProduct.cpp
        PerishableProduct.h
        PerishableProduct.cpp
        StoreStockStats.h
        StoreStats.h
        StoreStats.cpp
        Employee.cpp
        LogManager.cpp
        SecuritySystem.cpp
        AccessController.cpp
        Manager.h
        Manager.cpp
        Security.h
        Security.cpp
        Cashier.cpp
        CustomerSalesSystem.cpp
        VIPCustomer.cpp
        Transaction.cpp
        RegularCustomer.cpp
        PaymentMethod.cpp
        Invoice.cpp
        Feedback.cpp
        Customer.cpp)
