project(MUD-Server)

cmake_minimum_required(VERSION 3.24)

find_library(
        LIBHIREDIS
        NAMES libhiredis.so
        HINTS ../
        REQUIRED)

ADD_EXECUTABLE(server server/Server.cpp server/main.cpp server/utils/JsonParser.cpp server/logger/BasicLogger.cpp server/interface/IDataRepository.h server/EventHandler/BasicRequestHandler.cpp server/interface/IController.h server/interface/ILogger.h server/interface/IRequestHandler.h server/controller/BasicController.cpp server/header/BasicController.h server/interface/IRequestDTO.h server/interface/IResponseDTO.h server/dto/BasicRequestDto.cpp server/header/BasicRequestDto.h server/dto/BasicResponseDto.cpp server/header/BasicResponseDto.h server/utils/JsonBuilder.cpp server/header/JsonBuilder.h server/repository/RedisRepository.cpp server/header/RedisRepository.h server/domain/User.cpp server/header/User.h server/utils/Coordinate.cpp server/header/Coordinate.h server/domain/Slime.cpp server/header/Slime.h server/domain/Potion_hp.cpp server/header/Potion_hp.h server/domain/Potion_str.cpp server/header/Potion_str.h server/interface/IPotion.h)
target_link_libraries(server ${LIBHIREDIS})

ADD_EXECUTABLE(client client/src/NaiveLogger.cpp client/interface/Logger.h client/src/Client.cpp client/src/App.cpp server/interface/IController.h server/header/BasicRequestHandler.h)