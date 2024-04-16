#include "button.hpp"

#include <sys/types.h>

#include <cstddef>
#include <cstring>
#include <ostream>

#include "DataComponent.hpp"
#include "ProtocolParser.hpp"
#include "SceneManager.hpp"
#include "utils.hpp"

/**
 * \fn void buttonClick(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to click on a button
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void buttonDeny(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    engine.getAudio().playSound("villager");
}

/**
 * \fn void hostLobby(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to host a lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void hostLobby(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(CREATE_LOBBY);
            return;
        }
    }
}

/**
 * \fn void joinLobbies(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to join a lobby
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void joinLobbies(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(LOBBIES);
            return;
        }
    }
}

/**
 * \fn void joinLobby(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to join a lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void joinLobby(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    size_t mainEntityIndex = -1;
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        mainEntityIndex = sceneManager->getEntityPos();
        sceneManager->changeScene(LOBBY);
    }
    auto& data_array = reg.get_components<DataComponent>();
    std::string name = "Player";
    if (mainEntityIndex != -1) {
        auto& mainData = data_array[mainEntityIndex];
        if (mainData)
            name = mainData->getValue<std::string>("player_name");
    }
    auto& dataP = data_array[index];
    if (dataP) {
        int port = dataP.value().getValue<int>("port");
        uint64_t header = ProtocolBuilder::createPacket(CONNECT, 0, 0, 0, 0);
        char data[sizeof(header) + MAX_STR_LENGTH];
        memcpy(data, &header, sizeof(header));
        memcpy(data + sizeof(header), name.c_str(), name.length() + 1);
        if (serverToken.socket.send(
                data, sizeof(data), serverToken.adress, port)
            != ASocket::SUCCES) {
            std::cout << "Send Connect error" << std::endl;
        }
    }
}

/**
 * \fn void settings(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to access the settings
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void settings(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(SETINGS);
            return;
        }
    }
}

/**
 * \fn void quit(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to quit the game
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void quit(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(END);
            return;
        }
    }
}

/**
 * \fn void back(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to go back to the main menu
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void back (
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            if (sceneManager->getCurrentScene() == WAIT_IN_LOBBY) {
                auto& data_array = reg.get_components<DataComponent>();
                auto& dataP = data_array[sceneManager->getEntityPos()];
                int port = 0;
                if (dataP) {
                    port = dataP.value().getValue<int>("connectPort");
                }
                u_int64_t header =
                    ProtocolBuilder::createPacket(PLAYER_LEAVE, 0, 0, 0, 0);
                char data[sizeof(header)];
                memcpy(data, &header, sizeof(header));
                if (serverToken.socket.send(
                        data, sizeof(data), serverToken.adress, port)
                    != ASocket::SUCCES) {
                    std::cout << "Send leave error" << std::endl;
                    return;
                }
            }
            sceneManager->changeScene(MENU);
            return;
        }
    }
}

/**
 * \fn void local(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to play locally
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void local (
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(GAME);
            return;
        }
    }
}

/**
 * \fn void buttonClick(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to click on a button
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void buttonClick(size_t index,
    registry& reg /*unused*/,
    AEngine& engine,
    ServerToken& serverToken)
{
    engine.getAudio().playSound("click");
}

/**
 * \fn void switchReady(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to switch the ready state of a player
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void switchReady(size_t index,
    registry& reg /*unused*/,
    AEngine& engine,
    ServerToken& serverToken)
{
    size_t mainEntityIndex = -1;
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            mainEntityIndex = sceneManager->getEntityPos();
            break;
        }
    }
    auto& data_array = reg.get_components<DataComponent>();
    auto& dataP = data_array[mainEntityIndex];
    int port = 0;
    if (dataP) {
        port = dataP.value().getValue<int>("connectPort");
    }
    std::cout << "Send ready switch to " << port << " with" << serverToken.adress << std::endl;
    u_int64_t header = ProtocolBuilder::createPacket(PLAYER_READY, 0, 0, 0, 0);
    char data[sizeof(header)];
    memcpy(data, &header, sizeof(header));
    if (serverToken.socket.send(data, sizeof(data), serverToken.adress, port)
        != ASocket::SUCCES) {
        std::cout << "Send ready error" << std::endl;
        return;
    }
    if (engine.getGraphics().getText("readyText") != "Ready")
        engine.getGraphics().changeText("readyText", "Ready");
    else
        engine.getGraphics().changeText("readyText", "Not Ready");
}

/**
 * \fn void sendMessage(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to send a message
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void sendMessage(size_t index,
    registry& reg /*unused*/,
    AEngine& engine /*unused*/,
    ServerToken& serverToken)
{
    std::cout << "Mouse clicked On button" << std::endl;
}