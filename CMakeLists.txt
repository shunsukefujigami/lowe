cmake_minimum_required(VERSION 3.1)
project(lowe_make CXX)
find_package(ROOT REQUIRED)
include_directories($ENV{WCSIMDIR}/include ${ROOT_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)
add_library(lowe SHARED ./src/goodness/WCGoodness_calculate.cc
		            ./src/goodness/goodness_data.cc
			    ./src/general/config.cc
			    ./src/general/CSearch_range.cc
			    ./src/general/C4Number.cc
			    ./src/goodness/goodness_given_4Vector.cc
			    ./src/goodness/one_goodness.cc
			    ./src/funcparts/distance_pmt.cc
			    ./src/funcparts/tof.cc
			    ./src/general/runoption.cc
			    ./src/goodness/goodness_bias_err_func.cc
			    ./src/funcparts/eventdisplay_func.cc
			    ./src/likelihood/get_function_direction_func.cc
			    ./src/general/wrapped_function.cc
			    ./src/others/test.cc
			    ./src/likelihood/acceptance_pmt.cc
			    ./src/likelihood/f_direction.cc
			    ./src/likelihood/likelihood_direction.cc
			    ./src/likelihood/likelihood_direction_grid_search.cc
			    ./src/likelihood/likelihood_direction_data.cc
			    ./src/funcparts/theta_i_func.cc
			    ./src/funcparts/numberofhit.cc
			    ./src/goodness/goodness_x_f_direction.cc)
target_include_directories(lowe PUBLIC ./include
				       ./include/goodness
				       ./include/likelihood
				       ./include/general
				       ./include/funcparts
				       ./include/others)

# set(ROOT_LIBRARIES ${ROOT_LIBRARIES} "/home/fujigami/retro/root_build/lib/libMinuit.so")

add_executable(goodness_time_and_position ./exe/goodness/goodness_time_and_position_exe.cc)
target_compile_options(goodness_time_and_position PRIVATE "-Wall")
target_link_libraries(goodness_time_and_position lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

#add_executable(goodness_moment ./exe/goodness/goodness_moment.cc)
#target_compile_options(goodness_moment PRIVATE "-Wall")
#target_link_libraries(goodness_moment lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(convert ./exe/others/convert.cc)
target_compile_options(convert PRIVATE "-Wall")
target_link_libraries(convert lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(imagegoodness ./exe/goodness/imagegoodness.cc)
target_compile_options(imagegoodness PRIVATE "-Wall")
target_link_libraries(imagegoodness lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(eventdisplay ./exe/eventdisplay/eventdisplay.cc)
target_compile_options(eventdisplay PRIVATE "-Wall")
target_link_libraries(eventdisplay lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(eventdisplay_image ./exe/eventdisplay/eventdisplay_image.cc)
target_compile_options(eventdisplay_image PRIVATE "-Wall")
target_link_libraries(eventdisplay_image lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(goodness_bias_err ./exe/goodness/goodness_bias_err.cc)
target_compile_options(goodness_bias_err PRIVATE "-Wall")
target_link_libraries(goodness_bias_err lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(distance_image ./exe/others/distance_image.cc)
target_compile_options(distance_image PRIVATE "-Wall")
target_link_libraries(distance_image lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(eventdisplay_sum ./exe/eventdisplay/eventdisplay_sum.cc)
target_compile_options(eventdisplay_sum PRIVATE "-Wall")
target_link_libraries(eventdisplay_sum lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(eventdisplay_moment ./exe/eventdisplay/eventdisplay_moment.cc)
target_compile_options(eventdisplay_moment PRIVATE "-Wall")
target_link_libraries(eventdisplay_moment lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(minimize ./exe/others/NumericalMinimization.cc)
target_compile_options(minimize PRIVATE "-Wall")
target_link_libraries(minimize lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(goodness_minimize ./exe/goodness/goodness_minimize.cc)
target_compile_options(goodness_minimize PRIVATE "-Wall")
target_link_libraries(goodness_minimize lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(efficiency ./exe/others/efficiency.cc)
target_compile_options(efficiency PRIVATE "-Wall")
target_link_libraries(efficiency lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(get_function_direction ./exe/likelihood/get_function_direction.cc)
target_compile_options(get_function_direction PRIVATE "-Wall")
target_link_libraries(get_function_direction lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(N200 ./exe/others/N200.cc)
target_compile_options(N200 PRIVATE "-Wall")
target_link_libraries(N200 lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(test1 ./exe/others/test.cc)
target_compile_options(test1 PRIVATE "-Wall")
target_link_libraries(test1 ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(likelihood_direction_grid_search_exe ./exe/likelihood/likelihood_direction_grid_search_exe.cc)
target_compile_options(likelihood_direction_grid_search_exe PRIVATE "-Wall")
target_link_libraries(likelihood_direction_grid_search_exe lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(f_direction_use_fitting ./exe/likelihood/f_direction_use_fitting.cc)
target_compile_options(f_direction_use_fitting PRIVATE "-Wall")
target_link_libraries(f_direction_use_fitting ${ROOT_LIBRARIES})

add_executable(f_direction_define ./exe/likelihood/f_direction_define.cc)
target_compile_options(f_direction_define PRIVATE "-Wall")
target_link_libraries(f_direction_define lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(tof_exe ./exe/others/tof_exe.cc)
target_compile_options(tof_exe PRIVATE "-Wall")
target_link_libraries(tof_exe lowe ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)
