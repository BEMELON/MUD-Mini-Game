//
// Created by BEMELON on 22. 12. 15.
//

#include "../header/HealthController.h"

void HealthController::setLogger(ILogger *iLogger) {
    this->logger = iLogger;
}

void HealthController::addRoute(IRequestHandler *handler) {
    handler->addRoute("/health", &IController::get, this);
}

IResponseDTO *HealthController::get(IRequestDTO *body, IResponseDTO *resp) {
    this->logger->logInfoMsg("[DEBUG] HealthController has been called");

    return resp->setStatus("success");
}
