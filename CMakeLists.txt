cmake_minimum_required(VERSION 3.1)
project(lowe_make)
option (USE_PERF "Use Google Profiler" OFF)

find_package(ROOT REQUIRED)
if(NOT ROOT_FOUND)
  message(STATUS "ROOT package not found.")
  return()
endif()

find_package(Geant4 REQUIRED)
if(NOT Geant4_FOUND)
  message(STATUS "Geant4 package not found.")
  return()
endif()
include(${ROOT_USE_FILE})
include_directories($ENV{WCSIMDIR}/include ${ROOT_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

ROOT_GENERATE_DICTIONARY($ENV{MACRODIR}/src/macroRootDict $ENV{MACRODIR}/include/eventdisplay.hh $ENV{MACRODIR}/include/goodness_data.hh $ENV{MACRODIR}/include/likelihood_direction_data.hh $ENV{MACRODIR}/include/AnalizedData.hh $ENV{MACRODIR}/include/CSearch_range.hh LINKDEF $ENV{MACRODIR}/include/C4Number.hh $ENV{MACRODIR}/include/FileList.hh $ENV{MACRODIR}/include/efficiency.hh $ENV{MACRODIR}/include/HistByTree.hh $ENV{MACRODIR}/include/HistError.hh $ENV{MACRODIR}/include/HistBias.hh $ENV{MACRODIR}/include/MultiRunAnalizeManager.hh $ENV{MACRODIR}/include/OneRunAnalizeManager.hh $ENV{MACRODIR}/include/AngleRange.hh macro/include/macroRootLinkDef.hh)

add_library(lowemacro SHARED $ENV{MACRODIR}/src/eventdisplay.cc
		      	     $ENV{MACRODIR}/src/goodness_data.cc
			     $ENV{MACRODIR}/src/likelihood_direction_data.cc
			     $ENV{MACRODIR}/src/AnalizedData.cc
			     $ENV{MACRODIR}/src/CSearch_range.cc
			     $ENV{MACRODIR}/src/C4Number.cc
			     $ENV{MACRODIR}/src/macroRootDict.cxx
			     $ENV{MACRODIR}/src/FileList.cc
			     $ENV{MACRODIR}/src/efficiency.cc
			     $ENV{MACRODIR}/src/HistByTree.cc
			     $ENV{MACRODIR}/src/HistError.cc
			     $ENV{MACRODIR}/src/HistBias.cc
			     $ENV{MACRODIR}/src/OneRunAnalizeManager.cc
			     $ENV{MACRODIR}/src/MultiRunAnalizeManager.cc
			     $ENV{MACRODIR}/src/AngleRange.cc)
target_include_directories(lowemacro PUBLIC $ENV{MACRODIR}/include
				             $ENV{WCSIMDIR}/include
					     ${ROOT_INCLUDE_DIRS})
target_link_libraries(lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_library(lowe SHARED ./goodness/src/WCGoodness_calculate.cc
			    ./general/src/config.cc
			    ./goodness/src/goodness_given_4Vector.cc
			    ./goodness/src/goodness_bias_err_func.cc
			    ./likelihood/src/get_function_direction_func.cc
			    ./general/src/wrapped_function.cc
			    ./general/src/funcmap.cc
			    ./others/src/test.cc
			    ./likelihood/src/acceptance_pmt.cc
			    ./likelihood/src/f_direction.cc
			    ./funcparts/src/theta_i_func.cc
			    ./funcparts/src/distance_function.cc
			    ./funcparts/src/fdirection.cc
			    ./funcparts/src/likelihood.cc
			    ./funcparts/src/theta_dir_i.cc
			    ./funcparts/src/tof.cc
			    ./goodness/src/goodness_x_f_direction.cc
			    ./goodness/src/GoodnessManager.cc
			    ./goodness/src/GoodnessRunAction.cc
			    ./goodness/src/GoodnessCalculateManager.cc
			    ./goodness/src/GoodnessEventManager.cc
			    ./goodness/src/GoodnessEvent.cc
			    ./goodness/src/GoodnessEventAction.cc
			    ./goodness/src/GoodnessParameters.cc
			    ./goodness/src/OneGoodnessCalculated.cc
			    ./goodness/src/OneGoodnessCalculateManager.cc
			    ./likelihood/src/LikelihoodDirectionManager.cc
			    ./likelihood/src/LikelihoodDirectionCalculateManager.cc
			    ./likelihood/src/LikelihoodDirectionRunAction.cc
			    ./likelihood/src/LikelihoodDirectionEventAction.cc
			    ./likelihood/src/LikelihoodDirectionEventManager.cc
			    ./likelihood/src/OneLikelihoodDirectionCalculateManager.cc
			    ./virtual/src/ProcessManager.cc
			    ./virtual/src/VAction.cc
			    )
target_include_directories(lowe PUBLIC ./goodness/include
				       ./likelihood/include
				       ./general/include
				       ./funcparts/include
				       ./others/include
				       ./virtual/include
				       ./interface/include
				       $ENV{MACRODIR}/include
				       $ENV{WCSIMDIR}/include
				       ${ROOT_INCLUDE_DIRS}
				       ${Geant4_INCLUDE_DIR})

target_link_libraries(lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so ${Geant4_LIBRARIES})

# set(ROOT_LIBRARIES ${ROOT_LIBRARIES} "/home/fujigami/retro/root_build/lib/libMinuit.so")

#add_executable(goodness_moment ./exe/goodness/goodness_moment.cc)
#target_compile_options(goodness_moment PRIVATE "-Wall")
#target_link_libraries(goodness_moment lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(convert ./exe/others/convert.cc)
target_compile_options(convert PRIVATE "-Wall")
target_link_libraries(convert lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(distance_image ./exe/others/distance_image.cc)
target_compile_options(distance_image PRIVATE "-Wall")
target_link_libraries(distance_image lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(minimize ./exe/others/NumericalMinimization.cc)
target_compile_options(minimize PRIVATE "-Wall")
target_link_libraries(minimize lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(goodness_minimize ./exe/goodness/goodness_minimize.cc)
target_compile_options(goodness_minimize PRIVATE "-Wall")
target_link_libraries(goodness_minimize lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(get_function_direction ./exe/likelihood/get_function_direction.cc)
target_compile_options(get_function_direction PRIVATE "-Wall")
target_link_libraries(get_function_direction lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(N200 ./exe/others/N200.cc)
target_compile_options(N200 PRIVATE "-Wall")
target_link_libraries(N200 lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(test1 ./exe/others/test.cc)

# Google Performance Analyzer
if (USE_PERF)
   find_library(GPERFTOOLS_LIBRARIES NAMES profiler HINTS $ENV{GPERFTOOLS})
   target_link_libraries (test1 ${GPERFTOOLS_LIBRARIES})
   message (STATUS "USE_PERF=${USE_PERF}")
   message (STATUS "GPERFTOOLS_LIBRARIES=${GPERFTOOLS_LIBRARIES}")
endif (USE_PERF)

target_compile_options(test1 PRIVATE "-Wall")
target_link_libraries(test1 lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(likelihood_direction_grid_search_exe ./exe/likelihood/likelihood_direction_grid_search_exe.cc)
target_compile_options(likelihood_direction_grid_search_exe PRIVATE "-Wall")
target_link_libraries(likelihood_direction_grid_search_exe lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(f_direction_use_fitting ./exe/likelihood/f_direction_use_fitting.cc)
target_compile_options(f_direction_use_fitting PRIVATE "-Wall")
target_link_libraries(f_direction_use_fitting ${ROOT_LIBRARIES})

add_executable(f_direction_define ./exe/likelihood/f_direction_define.cc)
target_compile_options(f_direction_define PRIVATE "-Wall")
target_link_libraries(f_direction_define lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(tof_exe ./exe/others/tof_exe.cc)
target_compile_options(tof_exe PRIVATE "-Wall")
target_link_libraries(tof_exe lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(Goodness ./exe/goodness/Goodness.cc)
# Google Performance Analyzer
if (USE_PERF)
   find_library(GPERFTOOLS_LIBRARIES NAMES profiler HINTS $ENV{GPERFTOOLS})
   target_link_libraries (Goodness ${GPERFTOOLS_LIBRARIES})
   message (STATUS "USE_PERF=${USE_PERF}")
   message (STATUS "GPERFTOOLS_LIBRARIES=${GPERFTOOLS_LIBRARIES}")
endif (USE_PERF)

target_compile_options(Goodness PRIVATE "-Wall")
target_link_libraries(Goodness lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(LikelihoodDirection ./exe/likelihood/LikelihoodDirection.cc)
target_compile_options(LikelihoodDirection PRIVATE "-Wall")
target_link_libraries(LikelihoodDirection lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)
