# Detecting-Memory-Leaks-in-C-C-Applications
This repository will follow the Udemy course for detecting memory leaks in C/C++ applications.


# How to compile
- The code requires at least C++ 11. For handling_new_failure.cpp it requires C++14 because use of namespace chrono literals. 
- The file c_dynamic_allocation.cpp requires a Linux based system in order malloc_usable_size function to work.
- Personally I use g++ compiler with the following flags:    g++ -std=c++17 file_you_want_to_compile.cpp -o name_of_object_file 
