project(MUD-Server)

#cmake_minimum_required(VERSION 3.24)

find_library(
        LIBHIREDIS
        NAMES libhiredis.so
        HINTS ../
        REQUIRED)


ADD_EXECUTABLE(server server/Server.cpp server/main.cpp server/utils/JsonParser.cpp server/logger/BasicLogger.cpp server/interface/IDataRepository.h server/EventHandler/ProcessRequestHandler.cpp server/interface/IController.h server/interface/ILogger.h server/interface/IRequestHandler.h server/controller/BasicController.cpp server/header/BasicController.h server/interface/IRequestDTO.h server/interface/IResponseDTO.h server/dto/RequestDto.cpp server/header/RequestDto.h server/dto/ResponseDto.cpp server/header/ResponseDto.h server/utils/JsonBuilder.cpp server/header/JsonBuilder.h server/repository/RedisRepository.cpp server/header/RedisRepository.h server/domain/User.cpp server/header/User.h server/utils/Coordinate.cpp server/header/Coordinate.h server/domain/Slime.cpp server/header/Slime.h server/domain/Potion_hp.cpp server/header/HpPotion.h server/domain/Potion_str.cpp server/header/StrPotion.h server/interface/IPotion.h server/interface/IUserRepository.h server/repository/UserRepository.cpp server/header/UserRepository.h server/controller/UserController.cpp server/header/UserController.h server/interface/IUserService.h server/service/UserService.cpp server/header/UserService.h server/interface/IUserController.h server/utils/RandomGridGenerator.cpp server/header/RandomGridGenerator.h server/EventHandler/EpollEventHandler.cpp server/header/EpollEventHandler.h server/controller/HealthController.cpp server/header/HealthController.h)
target_link_libraries(server ${LIBHIREDIS})


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
ADD_EXECUTABLE(client client/src/NaiveLogger.cpp client/interface/Logger.h client/src/Client.cpp client/src/App.cpp server/interface/IController.h server/header/ProcessRequestHandler.h)
target_link_libraries(client ${CURSES_LIBRARIES})

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test test/main.cpp test/test_controller.cpp test/test_UserService.cpp server/utils/JsonBuilder.cpp server/utils/JsonParser.cpp server/domain/User.cpp server/domain/Potion_str.cpp server/domain/Potion_hp.cpp server/utils/Coordinate.cpp server/utils/RandomGridGenerator.cpp test/test_HealthController.cpp)
target_link_libraries(test gtest_main)
add_test(NAME example_test COMMAND test)