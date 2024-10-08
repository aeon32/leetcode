SET (CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR x64)

FIND_PROGRAM(MY_C_COMPILER x86_64-linux-gnu-gcc-13 NAMES x86_64-linux-gnu-gcc-12  x86_64-linux-gnu-gcc-11 x86_64-linux-gnu-gcc-10 x86_64-linux-gnu-gcc-9)
FIND_PROGRAM(MY_CXX_COMPILER x86_64-linux-gnu-g++-13 NAMES x86_64-linux-gnu-g++-12 x86_64-linux-gnu-g++-11 x86_64-linux-gnu-g++-10 x86_64-linux-gnu-g++-9)
SET (CMAKE_C_COMPILER ${MY_C_COMPILER})
SET (CMAKE_CXX_COMPILER ${MY_CXX_COMPILER})