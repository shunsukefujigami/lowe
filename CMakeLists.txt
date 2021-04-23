
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

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -mtune=native -march=native")

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


ROOT_GENERATE_DICTIONARY($ENV{MACRODIR}/src/macroRootDict $ENV{MACRODIR}/include/eventdisplay.hh $ENV{MACRODIR}/include/goodness_data.hh $ENV{MACRODIR}/include/likelihood_direction_data.hh $ENV{MACRODIR}/include/AnalizedData.hh $ENV{MACRODIR}/include/CSearch_range.hh LINKDEF $ENV{MACRODIR}/include/C4Number.hh $ENV{MACRODIR}/include/FileList.hh $ENV{MACRODIR}/include/efficiency.hh $ENV{MACRODIR}/include/HistByTree.hh $ENV{MACRODIR}/include/HistError.hh $ENV{MACRODIR}/include/HistBias.hh $ENV{MACRODIR}/include/OneRunAnalizeManager.hh $ENV{MACRODIR}/include/AngleRange.hh $ENV{MACRODIR}/include/Thitinfo.hh $ENV{MACRODIR}/include/TReconstructdata.hh $ENV{MACRODIR}/include/Tfunction.hh $ENV{MACRODIR}/include/Tafunction.hh $ENV{MACRODIR}/include/Tdistance_function.hh $ENV{MACRODIR}/include/Tfdirection.hh $ENV{MACRODIR}/include/Tlikelihood.hh $ENV{MACRODIR}/include/Ttheta_dir_i.hh $ENV{MACRODIR}/include/Ttheta_i_func.hh $ENV{MACRODIR}/include/Ttof.hh $ENV{MACRODIR}/include/Tfgoodnessdirection.hh $ENV{MACRODIR}/include/OneRunDataAnalizeManager.hh $ENV{MACRODIR}/include/OneRunGoodnessAnalizeManager.hh $ENV{MACRODIR}/include/OneRunLikelihoodAnalizeManager.hh $ENV{MACRODIR}/include/OneRunGoodnessMinimizeAnalizeManager.hh $ENV{MACRODIR}/include/OneDataParameters.hh $ENV{MACRODIR}/include/MyString.hh $ENV{MACRODIR}/include/MultiRunAnalizeManager.hh $ENV{MACRODIR}/include/OneGoodnessParameters.hh $ENV{MACRODIR}/include/OneLikelihoodParameters.hh $ENV{MACRODIR}/include/OneGoodnessMinimizeParameters.hh $ENV{MACRODIR}/include/TOption_minimize.hh $ENV{MACRODIR}/include/Tfgoodness.hh $ENV{MACRODIR}/include/Tfsumgoodness.hh $ENV{MACRODIR}/include/BiasError.hh macro/include/macroRootLinkDef.hh)

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
			     $ENV{MACRODIR}/src/AngleRange.cc
			     $ENV{MACRODIR}/src/Thitinfo.cc
			     $ENV{MACRODIR}/src/TReconstructdata.cc
			     $ENV{MACRODIR}/src/Tafunction.cc
			     $ENV{MACRODIR}/src/Tdistance_function.cc
			     $ENV{MACRODIR}/src/Tfdirection.cc
			     $ENV{MACRODIR}/src/Tlikelihood.cc
			     $ENV{MACRODIR}/src/Ttheta_dir_i.cc
			     $ENV{MACRODIR}/src/Ttheta_i_func.cc
			     $ENV{MACRODIR}/src/Ttof.cc
			     $ENV{MACRODIR}/src/OneRunDataAnalizeManager.cc
			     $ENV{MACRODIR}/src/OneRunGoodnessAnalizeManager.cc
			     $ENV{MACRODIR}/src/OneRunLikelihoodAnalizeManager.cc
			     $ENV{MACRODIR}/src/OneRunGoodnessMinimizeAnalizeManager.cc
			     $ENV{MACRODIR}/src/OneDataParameters.cc
			     $ENV{MACRODIR}/src/OneGoodnessParameters.cc
			     $ENV{MACRODIR}/src/OneLikelihoodParameters.cc
			     $ENV{MACRODIR}/src/OneGoodnessMinimizeParameters.cc
			     $ENV{MACRODIR}/src/MyString.cc
			     $ENV{MACRODIR}/src/TOption_minimize.cc
			     $ENV{MACRODIR}/src/BiasError.cc
			     $ENV{MACRODIR}/src/Tfgoodness.cc
			     $ENV{MACRODIR}/src/Tfgoodnessdirection.cc
			     $ENV{MACRODIR}/src/Tfsumgoodness.cc
			     $ENV{MACRODIR}/src/Tfunction.cc)
target_include_directories(lowemacro PUBLIC $ENV{MACRODIR}/include
				             $ENV{WCSIMDIR}/include
					     ${ROOT_INCLUDE_DIRS})
target_link_libraries(lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_library(lowe SHARED     ./general/src/config.cc
			    ./general/src/funcmap.cc
			    ./others/src/test.cc
			    ./funcparts/src/theta_i_func.cc
			    ./funcparts/src/distance_function.cc
			    ./funcparts/src/fdirection.cc
			    ./funcparts/src/likelihood.cc
			    ./funcparts/src/theta_dir_i.cc
			    ./funcparts/src/tof.cc
			    ./funcparts/src/fgoodness.cc
			    ./funcparts/src/fgoodnessdirection.cc
			    ./funcparts/src/fsumgoodness.cc
			    ./funcparts/src/onelikelihoodtof.cc
			    ./goodness/src/GoodnessManager.cc
			    ./goodness/src/GoodnessRunAction.cc
			    ./goodness/src/GoodnessEventManager.cc
			    ./goodness/src/GoodnessEvent.cc
			    ./goodness/src/GoodnessEventAction.cc
			    ./goodness/src/GoodnessParameters.cc
			    ./goodness/src/GoodnessVerboseManager.cc
			    ./goodness/src/GoodnessVerboseEventManager.cc
			    ./goodness/src/GoodnessVerboseCalculateManager.cc
			    ./goodness/src/GoodnessVerboseCalculateAction.cc
			    ./goodness/src/GoodnessMinimizeManager.cc
			    ./goodness/src/GoodnessMinimizeEventManager.cc
			    ./goodness/src/GoodnessMinimizeRunAction.cc
			    ./goodness/src/GoodnessMinimizeEventAction.cc
			    ./likelihood/src/LikelihoodDirectionManager.cc
#			    ./likelihood/src/LikelihoodDirectionCalculateManager.cc
			    ./likelihood/src/LikelihoodDirectionRunAction.cc
			    ./likelihood/src/LikelihoodDirectionEventAction.cc
			    ./likelihood/src/LikelihoodDirectionEventManager.cc
#			    ./likelihood/src/OneLikelihoodDirectionCalculateManager.cc
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
				       ../../fmath
				       ${ROOT_INCLUDE_DIRS}
				       ${Geant4_INCLUDE_DIR})

target_link_libraries(lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so ${Geant4_LIBRARIES})

set(ROOT_LIBRARIES ${ROOT_LIBRARIES} "/home/fujigami/retro/root_build/lib/libMinuit.so")

#add_executable(goodness_moment ./exe/goodness/goodness_moment.cc)
#target_compile_options(goodness_moment PRIVATE "-Wall")
#target_link_libraries(goodness_moment lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(convert ./exe/others/convert.cc)
target_compile_options(convert PRIVATE "-Wall")
target_link_libraries(convert lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

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

add_executable(f_direction_use_fitting ./exe/likelihood/f_direction_use_fitting.cc)
target_compile_options(f_direction_use_fitting PRIVATE "-Wall")
target_link_libraries(f_direction_use_fitting ${ROOT_LIBRARIES})

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

# Google Performance Analyzer
if (USE_PERF)
   find_library(GPERFTOOLS_LIBRARIES NAMES profiler HINTS $ENV{GPERFTOOLS})
   target_link_libraries (LikelihoodDirection ${GPERFTOOLS_LIBRARIES})
   message (STATUS "USE_PERF=${USE_PERF}")
   message (STATUS "GPERFTOOLS_LIBRARIES=${GPERFTOOLS_LIBRARIES}")
endif (USE_PERF)

target_compile_options(LikelihoodDirection PRIVATE "-Wall")
target_link_libraries(LikelihoodDirection lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(GoodnessMinimize ./exe/goodness/GoodnessMinimize.cc)
target_compile_options(GoodnessMinimize PRIVATE "-Wall")
target_link_libraries(GoodnessMinimize lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)

add_executable(printxyzbias ./exe/macro/printxyzbias.cc)
target_compile_options(printxyzbias PRIVATE "-Wall")
target_link_libraries(printxyzbias lowe lowemacro ${ROOT_LIBRARIES} $ENV{WCSIMBUILD}/libWCSimRoot.so)
