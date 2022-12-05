project(MUD-Server)
ADD_EXECUTABLE(server server/src/Server.cpp server/src/App.cpp server/interface/Logger.h server/src/NaiveLogger.cpp server/header/NaiveLogger.h)
ADD_EXECUTABLE(client client/src/NaiveLogger.cpp client/interface/Logger.h client/src/Client.cpp client/src/App.cpp)