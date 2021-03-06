cmake_minimum_required (VERSION 3.0)
project (EvoSim)

########################################
######## Version

set(VERSION_MAJOR="1")
set(VERSION_MINOR="0")
set(VERSION_PATCH="0")

add_definitions (-DVERSION_MAJOR=1 -DVERSION_MINOR=0 -DVERSION_PATCH=0)


#########################################
####### Find packages

####### eigen3
find_package (Eigen3 3.3.4 REQUIRED NO_MODULE)

####### booost
find_package (Boost 1.58.0 COMPONENTS system filesystem unit_test_framework REQUIRED)

####### opencv
find_package (OpenCV REQUIRED)

####### ros
find_package (catkin COMPONENTS roscpp rospy std_msgs)
#catkin_package (roscpp rospy std_msgs)


#########################################
#######

set(CMAKE_CXX_FLAGS "-std=c++14")


######

include_directories(
	${Boost_INCLUDE_DIRS}
	#${catkin_INCLUDE_DIRS}
	)


##########################################
#######

set(SRC_FILES 
	"src/EvoSim.cpp"
	"src/agents/Agent.cpp"
	"src/agents/Brain.cpp"
	"src/agents/Neuron.cpp"
	"src/worlds/World.cpp"
	"src/Display.cpp"
	)
set(UNIT_TESTS 
	"unit-tests/main.cpp" 
	"unit-tests/TemplateUnit.cpp"
	)

###########################################
### main binary
add_executable(EvoSim "src/main.cpp" ${SRC_FILES})
target_link_libraries (EvoSim
       	Eigen3::Eigen
       	${Boost_LIBRARIES}
		${OpenCV_LIBS}
		-lpthread
	#${catkin_LIBRARIES}
	)

###########################################
######
#add_dependencies(Template templatedependency)



############################################
####### unit tests
#add_executable(unit-tests ${UNIT_TESTS} ${SRC_FILES})
#target_link_libraries (unit-tests Eigen3::Eigen ${Boost_LIBRARIES} ${OpenCV_LIBS})

#include(${CMAKE_CURRENT_SOURCE_DIR}/unit-tests/CMakeLists.txt)




