/*
** EPITECH PROJECT, 2022
** R_type
** File description:
** core
*/

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

#include "AEngine.hpp"
#include "ASocket.hpp"
#include "ClocksComponent.hpp"
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "DrawableComponent.hpp"
#include "ExecComponent.hpp"
#include "KeyboardEventComponent.hpp"
#include "Registry.hpp"
#include "SFMLEngine.hpp"
#include "SFMLSocket.hpp"
#include "Script.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "button.hpp"
#include "exec.hpp"
#include "move.hpp"
#include "system.hpp"

/**
 * \class Core
 * \brief The core of the game.
 * Used to initialize the game
 */
class Core
{
  public:
    /**
     * \fn explicit Core(int windowX = 1920, int windowY = 1080)
     * \brief Constructor of the core
     * \param windowX The width of the window
     * \param windowY The height of the window
     */
    explicit Core(int windowX = 1920, int windowY = 1080)
        : engine(std::make_unique<SFMLEngine>(windowX, windowY))
    {
        script = std::make_unique<Script>(_registry, *engine);
        script->add_scripts_from_folder("./Scripts");
    };

    ~Core() = default; /*!< Default destructor */

    /**
     * \fn int Core::loop()
     * \brief The loop of the core
     * \return Error code
     */
    int loop();

    /**
     * \fn void Core::initStart()
     * \brief Init the start of the core
     */
    void initStart();

    /**
     * \fn ServerToken& getServerToken();
     * \brief Get the server token
     * \return The server token
     */
    ServerToken& getServerToken();

    /**
     * \fn void updateRequests();
     * \brief Update the requests
     */
    void updateRequests();

  private:
    std::vector<Request> requestList; /*!< List of requests */
    std::unique_ptr<ASocket> socket = std::make_unique<SFMLSocket>(); /*!< Socket */
    size_t mainEntityIndex = 0; /*!< Index of the main entity */
    ServerToken serverToken = {*socket, "", 2312};  /*!< Server token */
    registry _registry; /*!< Registry of the core */
    std::unique_ptr<Script> script; /*!< Script of the core */
    std::unique_ptr<AEngine> engine;     /*!< Engine of the core */
    std::vector<Entity> entityList = {}; /*!< List of the entities */
};