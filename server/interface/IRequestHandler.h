//
// Created by BEMELON on 22. 12. 5.
//

#ifndef MUD_SERVER_IREQUESTHANDLER_H
#define MUD_SERVER_IREQUESTHANDLER_H
#define interface class
#include "ILogger.h"
#include "IController.h"
#include "../header/rapidjson/document.h"
#include <ext/hash_map>
class IController;
// for GNU HashMap
namespace __gnu_cxx {
    template<>
    struct hash<std::string > {
        size_t operator( )(std::string const & s ) const {
            return __stl_hash_string( s.c_str( ) );
        }
    };
}
typedef __gnu_cxx::hash_map<std::string,  void (IController::*)(rapidjson::Document *)> ROUTER_HASHMAP;
typedef __gnu_cxx::hash_map<std::string, IController *> CONTROLLER_HASHMAP;

interface IRequestHandler {
protected:
    int port;
    ILogger *logger;
    ROUTER_HASHMAP router;
    CONTROLLER_HASHMAP controller;
public:
    virtual void setLogger(ILogger *logger) = 0;
    virtual void addRoute(std::string path, void (IController::*fn_router)(rapidjson::Document *parser), IController *caller) = 0;
    virtual void listen(int port) = 0;
};

#endif //MUD_SERVER_IREQUESTHANDLER_H