/*
** EPITECH PROJECT, 2022
** R_Type
** File description:
** A game
*/

#include "Core.hpp"

#include <ostream>
#include <type_traits>

#include "ASocket.hpp"
#include "Registry.hpp"
#include "VelocityComponent.hpp"

/**
 * \fn void Core::initStart()
 * \brief Initialize the start of the core
 */
void Core::initStart()
{
    auto const& mainScene = _registry.spawn_entity();
    mainEntityIndex = mainScene.id;
    auto& sceneManager = _registry.add_component(mainScene, SceneManager());
    _registry.add_component(mainScene, DataComponent());
    sceneManager->setUpdate(true);
    if (socket->bind(0) != ASocket::SUCCES) {
        std::cout << "Can't bind socket, unable to connect" << std::endl;
        // TODO(bilj): handle mieux la sécurité
    }
    _registry.add_system(gameSystem);
}

/**
 * \fn int Core::loop()
 * \brief Update the core
 * \return Error code
 */
int Core::loop()
{
    std::thread listenThread{&listen,
        std::ref(_registry),
        std::ref(*engine),
        std::ref(serverToken),
        std::ref(requestList)};
    usleep(10);
    while (engine->isRunning()) {
        updateRequests();
        engine->update();
        engine->getWindow().clear();
        script->update_scripts();
        _registry.run_systems(*engine, getServerToken());
        engine->getWindow().display();
    }
    listenThread.join();
    return 0;
}

/**
 * \fn ServerToken& Core::getServerToken()
 * \brief Get the server token
 * \return The server token
 */
ServerToken& Core::getServerToken()
{
    return serverToken;
}

/**
 * \fn void Core::updateRequests()
 * \brief Update the requests
 */
void Core::updateRequests()
{
    auto scene_array = _registry.get_components<SceneManager>();
    for (auto sceneManager : scene_array) {
        if (!sceneManager)
            continue;
        for (auto request : requestList) {
            handleRequest(_registry,
                request.header,
                request.strArgs,
                sceneManager->getEntityPos(),
                serverToken,
                request.senderPort,
                *engine);
        }
        requestList = {};
    }
}