cmake_minimum_required(VERSION 3.0) # setting this is required
project(VerkkopeliServer)            # this sets the project name

###############################################################################
## files ##############################################################
###############################################################################

file(GLOB_RECURSE sources      *.cpp *.h)

add_executable(VerkkopeliServer main.cpp)

###############################################################################
## dependencies ###############################################################
###############################################################################

# This defines the variables Boost_LIBRARIES that containts all library names
# that we need to link into the program.
find_package(Boost 1.78.0 COMPONENTS filesystem system REQUIRED)

target_link_libraries(example PUBLIC
  ${Boost_LIBRARIES}
  # here you can add any library dependencies
)

###############################################################################
## packaging ##################################################################
###############################################################################

# Now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here.
set(CPACK_PACKAGE_NAME "VerkkopeliServer")
set(CPACK_PACKAGE_VERSION "1.0.0")

# We don't want to split our program up into several incomplete pieces.
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)