cmake_minimum_required(VERSION 3.4)

project(Downloader)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/tftp)
include_directories(${PROJECT_SOURCE_DIR}/tools)
include_directories(${PROJECT_SOURCE_DIR}/common)
include_directories(${PROJECT_SOURCE_DIR}/streams)
include_directories(${PROJECT_SOURCE_DIR}/ymodem)
include_directories(${PROJECT_SOURCE_DIR}/transferers)
include_directories(${PROJECT_SOURCE_DIR}/serial/src)
include_directories(${PROJECT_SOURCE_DIR}/serial/include)
include_directories(${PROJECT_SOURCE_DIR}/serial/src/impl)
include_directories(${PROJECT_SOURCE_DIR}/serial/src/impl/list_ports)

set(PLATFORM_SRC )
if(APPLE)
	# If OSX
	list(APPEND PLATFORM_SRC serial/src/impl/unix.cc)
	list(APPEND PLATFORM_SRC serial/src/impl/list_ports/list_ports_osx.cc)
	find_library(IOKIT_LIBRARY IOKit)
	find_library(FOUNDATION_LIBRARY Foundation)

	set(PLATFORM_LIB ${IOKIT_LIBRARY} ${FOUNDATION_LIBRARY})
	ADD_DEFINITIONS(-g -W -Wall)
elseif(UNIX)
    # If unix
    list(APPEND PLATFORM_SRC serial/src/impl/unix.cc)
    list(APPEND PLATFORM_SRC serial/src/impl/list_ports/list_ports_linux.cc)
	ADD_DEFINITIONS(-g -W -Wall)
else()
    # If windows
    list(APPEND PLATFORM_SRC serial/src/impl/win.cc)
    list(APPEND PLATFORM_SRC serial/src/impl/list_ports/list_ports_win.cc)
	ADD_DEFINITIONS(-W0)
endif()


set(COMMON_SRC
   tftp/server_lib.c 
   tftp/work_thread.c
   serial/src/serial.cc 
   streams/stream_serial.cpp 
   ymodem/fymodem.c 
   streams/stream_tcp.c 
   transferers/transferer_tcp.c 
   transferers/transferer_serial.cpp 
   transferers/transferer_factory.c 
   transferers/transferer_tftp_server.c
   common/common.c 
   common/progress.c 
   common/platform.c 
   common/url.c
)

add_library(${PROJECT_NAME} ${PLATFORM_SRC} ${COMMON_SRC})
if(APPLE)
	target_link_libraries(${PROJECT_NAME} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
	target_link_libraries(${PROJECT_NAME} rt pthread)
else()
	target_link_libraries(${PROJECT_NAME} setupapi ws2_32)
endif()

set(TCP_SERVER_SRC tools/server.c)
add_executable(tcpserver ${TCP_SERVER_SRC})
target_link_libraries(tcpserver ${PROJECT_NAME})

set(TCP_CLIENT_SRC tools/client.c)
add_executable(tcpclient ${TCP_CLIENT_SRC})
target_link_libraries(tcpclient ${PROJECT_NAME})

set(TRANSFERER_SRC tools/dloader.c)
add_executable(dloader ${TRANSFERER_SRC})
target_link_libraries(dloader ${PROJECT_NAME})

set(LIST_SERIAL_SRC tools/list_serial.cpp)
add_executable(list_serial ${LIST_SERIAL_SRC})
target_link_libraries(list_serial ${PROJECT_NAME})

set(TFTP_CLIENT_SRC tftp/client.c)
add_executable(tftpclient ${TFTP_CLIENT_SRC})
target_link_libraries(tftpclient ${PROJECT_NAME})

set(READ_SERIAL_SRC tools/read_serial.cpp)
add_executable(read_serial ${READ_SERIAL_SRC})
target_link_libraries(read_serial ${PROJECT_NAME})

