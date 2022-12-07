project(MUD-Server)

cmake_minimum_required(VERSION 3.24)

find_library(
        LIBHIREDIS
        NAMES libhiredis.so
        HINTS ../
        REQUIRED)

ADD_EXECUTABLE(server server/Server.cpp server/main.cpp server/utils/JsonParser.cpp server/logger/BasicLogger.cpp server/interface/IRepository.h server/EventHandler/BasicRequestHandler.cpp server/interface/IController.h server/interface/ILogger.h server/interface/IRequestHandler.h server/controller/BasicController.cpp server/header/BasicController.h server/interface/IRequestDTO.h server/interface/IResponseDTO.h server/dto/BasicRequestDto.cpp server/header/BasicRequestDto.h server/dto/BasicResponseDto.cpp server/header/BasicResponseDto.h server/utils/JsonBuilder.cpp server/header/JsonBuilder.h server/repository/RedisRepository.cpp server/header/RedisRepository.h)
target_link_libraries(server ${LIBHIREDIS})

ADD_EXECUTABLE(client client/src/NaiveLogger.cpp client/interface/Logger.h client/src/Client.cpp client/src/App.cpp server/interface/IController.h server/header/BasicRequestHandler.h)