#include <unistd.h>

#include <cstddef>
#include <ostream>
#include <thread>
#include <vector>

#include "AEngine.hpp"
#include "ASocket.hpp"
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "DrawableComponent.hpp"
#include "ExecComponent.hpp"
#include "GameEntity/gameEntity.hpp"
#include "ProtocolParser.hpp"
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "button.hpp"
#include "exec.hpp"
#include "move.hpp"
#include "system.hpp"
#include "utils.hpp"

/**
 * \fn void accesSettings(registry& reg, AEngine& engine)
 * \brief Function to access the settings
 * \param reg The registry
 * \param engine The engine
 */
void accesEnd(size_t id, registry& reg, AEngine& engine)
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
 * \fn void accesEnd(registry& reg, AEngine& engine)
 * \brief Function to access the end of the game
 * \param reg The registry
 * \param engine The engine
 */
void accesSettings(size_t id, registry& reg, AEngine& engine)
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
 * \fn bool isValidIp(std::string string)
 * \brief Function to check if the ip is valid
 * \param string The string to check
 * \return true if the ip is valid, false otherwise
 */
bool isValidIp(std::string string)
{
    std::string token;
    std::string delimiter = ".";
    auto pos = string.find(delimiter);
    if (pos == std::string::npos
        || std::count(string.begin(), string.end(), '.') != 3)
        return false;
    while (pos != std::string::npos) {
        token = string.substr(0, pos);
        if (token.empty() || token.size() > 3)
            return false;
        if (token.find_first_not_of("0123456789") != std::string::npos)
            return false;
        string.erase(0, pos + delimiter.size());
        pos = string.find(delimiter);
    }
    if (string.empty() || string.size() > 3)
        return false;
    return string.find_first_not_of("0123456789") == std::string::npos;
}

/**
 * \fn bool isValidPort(std::string string)
 * \brief Function to check if the port is valid
 * \param string The string to check
 * \return true if the port is valid, false otherwise
 */
bool isValidPort(std::string string)
{
    if (string.empty() || string.size() > 5)
        return false;
    return string.find_first_not_of("0123456789") == std::string::npos;
}

/**
 * \fn void accesMenu(registry& reg, AEngine& engine)
 * \brief Function to access the menu
 * \param reg The registry
 * \param engine The engine
 */
void accesMenu(size_t id, registry& reg, AEngine& engine, ServerToken& token)
{
    auto& data_array = reg.get_components<DataComponent>();
    auto& scene_array = reg.get_components<SceneManager>();
    auto address = engine.getGraphics().getText("address");
    auto port = engine.getGraphics().getText("port");
    auto player_name = engine.getGraphics().getText("player_name");
    std::replace(address.begin(), address.end(), ',', '.');
    if (player_name.empty() || player_name.size() > 512) {
        engine.getGraphics().changeText("player_name", "Invalid name");
        return;
    }
    if (!isValidIp(address) || !isValidPort(port)) {
        if (!isValidIp(address))
            engine.getGraphics().changeText("address", "Invalid IP");
        if (!isValidPort(port))
            engine.getGraphics().changeText("port", "Invalid Port");
        return;
    }
    token.adress = address;
    token.port = stoi(port);
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(MENU);
            size_t mainEntityIndex = sceneManager->getEntityPos();
            auto& data = data_array[mainEntityIndex];
            if (data) {
                data->addValue("player_name", player_name);
            } else {
                auto& mainEnt = reg.getEntities().at(mainEntityIndex);
                auto newData =
                    reg.add_component(mainEnt.value(), DataComponent());
                newData->addValue("player_name", player_name);
            }
            return;
        }
    }
}

/**
 * \fn void accesWaitLobby(size_t id, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Function to access to the waiting room
 * \param id The id of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void accesWaitLobby(
    size_t id, registry& reg, AEngine& engine, ServerToken& token)
{
    size_t mainEntityIndex = -1;
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            mainEntityIndex = sceneManager->getEntityPos();
            sceneManager->changeScene(LOBBY);
        }
    }
    std::string name = engine.getGraphics().getText("player_name");
    u_int64_t header = ProtocolBuilder::createPacket(CREATE, 0, 0, 0, 0);
    std::string insetStr =
        engine.getGraphics().getText("lobby_name") + "\n" + name;
    char data[sizeof(header) + MAX_STR_LENGTH];
    std::memcpy(data, &header, sizeof(header));
    std::memcpy(data + sizeof(header), insetStr.c_str(), insetStr.size() + 1);
    if (token.socket.send(data, sizeof(data), token.adress, token.port)
        != ASocket::SUCCES) {
        std::cout << "can't send info" << std::endl;
        return;
    }
}

/**
 * \fn void accesGame(size_t id, registry& reg, AEngine& engine)
 * \brief Function to access the game
 * \param id The id of the entity
 * \param reg The registry
 * \param engine The engine
 */
void accesGame(size_t id, registry& reg, AEngine& engine)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager)
            sceneManager->changeScene(GAME);
    }
}

/**
 * \fn void initStart(registry& reg, AEngine& engine)
 * \brief Function to init the start scene
 * \param reg The registry
 * \param engine The engine
 */
void initStart(registry& reg, AEngine& engine)
{
    engine.getGraphics().createTexture("background1", "assets/space.jpg");
    engine.getGraphics().createSprite("menuBackground", "background1");
    engine.getAudio().createSound("villager", "assets/sounds/Angry_villager.wav");
    engine.getAudio().createSound("music", "assets/sounds/MenuTheme.wav");
    engine.getAudio().createSound("click", "assets/sounds/click.wav");
    engine.getAudio().createSound("in-game", "assets/sounds/Adrenaline.ogg");
    engine.getAudio().createSound("shootEnemy", "assets/sounds/shoot.wav");
    engine.getAudio().createSound("shootPlayer", "assets/sounds/shoot.wav");
    engine.getAudio().setSoundVolume("music", 10);
    engine.getAudio().playSound("music");

    engine.getGraphics().createFont("beautiful", "assets/font/font.ttf");

    engine.getGraphics().createTexture("logo", "assets/logo_rtype.png");
    engine.getGraphics().createSprite("logoRtype", "logo");

    engine.getGraphics().createText(
        "WelcomeText", "Enter server address and press Enter", "beautiful", 20);

    engine.getGraphics().createText(
        "address", "Enter ip here", "beautiful", 20);

    engine.getGraphics().createText("port", "Enter port here", "beautiful", 20);
    engine.getGraphics().createText(
        "player_name", "Enter your name here", "beautiful", 20);

    engine.getGraphics().createRectangle("backButton", 300, 40);

    auto const& background = reg.spawn_entity();
    reg.add_component(background, DrawableComponent("menuBackground", SPRITE));
    reg.add_component(background, TransformComponent());
    sparse_array<KeyboardEventComponent>::reference_type controllable =
        reg.add_component(background, KeyboardEventComponent());

    auto const& ent = reg.spawn_entity();
    reg.add_component(ent, DrawableComponent("WelcomeText", TEXT));
    reg.add_component(ent, TransformComponent({800, 300, 0}));
    reg.add_component(ent, ClocksComponent(1));
    reg.add_component(ent, BlinkComponent(1));

    if (controllable) {
        controllable.value().addAction(Key::Enter, accesMenu);
    }

    auto const& rtypeLogo = reg.spawn_entity();
    reg.add_component(rtypeLogo, DrawableComponent("logoRtype", SPRITE));
    reg.add_component(rtypeLogo, TransformComponent({710, 100, 0}));

    auto const& input = reg.spawn_entity();
    reg.add_component(input, DrawableComponent("address", TEXT));
    reg.add_component(input, TransformComponent({800, 500, 1}));
    reg.add_component(input, CollideComponent(300, 40, -10, -10));
    reg.add_component(input, InputComponent("address", 20));
    auto const& rect = reg.spawn_entity();
    reg.add_component(rect, DrawableComponent("backButton", RECTANGLE));
    reg.add_component(rect, TransformComponent({790, 490, 0}));

    auto const& input2 = reg.spawn_entity();
    reg.add_component(input2, DrawableComponent("port", TEXT));
    reg.add_component(input2, TransformComponent({800, 550, 1}));
    reg.add_component(input2, CollideComponent(300, 40, -10, -10));
    reg.add_component(input2, InputComponent("port", 20));

    auto const& input3 = reg.spawn_entity();
    reg.add_component(input3, DrawableComponent("player_name", TEXT));
    reg.add_component(input3, TransformComponent({800, 600, 1}));
    reg.add_component(input3, CollideComponent(300, 40, -10, -10));
    reg.add_component(input3, InputComponent("player_name", 20));

    auto const& rect2 = reg.spawn_entity();
    reg.add_component(rect2, DrawableComponent("backButton", RECTANGLE));
    reg.add_component(rect2, TransformComponent({790, 540, 0}));

    auto const& rect3 = reg.spawn_entity();
    reg.add_component(rect3, DrawableComponent("backButton", RECTANGLE));
    reg.add_component(rect3, TransformComponent({790, 590, 0}));

    reg.add_system(blinkSystem);
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(KeyboardEventSystem);
    reg.add_system(clocksSystem);
    reg.add_system(inputSystem);
}

/**
 * \fn void initMenuSprites(registry& reg, AEngine& engine)
 * \brief Function to init the menu sprites
 * \param reg The registry
 * \param engine The engine
 */
void initMenuSprites(registry& reg, AEngine& engine)
{
    engine.getGraphics().createTexture(
        "background2", "assets/MenuBackground2.png");
    engine.getGraphics().createSprite("menuBackground2", "background2");
    engine.getGraphics().createTexture("logo", "assets/logo_rtype.png");
    engine.getGraphics().createSprite("logoRtype", "logo");

    auto const& rtypeLogo = reg.spawn_entity();
    reg.add_component(rtypeLogo, DrawableComponent("logoRtype", SPRITE));
    reg.add_component(rtypeLogo, TransformComponent({710, 100, 6}));

    engine.getGraphics().createTexture("button", "assets/button.png");
    engine.getGraphics().createSprite("menuHostBtn", "button");
    engine.getGraphics().createText("BackText", "BACK", "beautiful", 20);
    engine.getGraphics().createSprite("menuBackBtn", "button");
    engine.getGraphics().createSprite("menuJoinBtn", "button");
    engine.getGraphics().createText("HostText", "HOST", "beautiful", 20);
    engine.getGraphics().createText("JoinText", "JOIN", "beautiful", 20);
    engine.getGraphics().createSprite("menuLocalBtn", "button");
    engine.getGraphics().createText("LocalText", "LOCAL", "beautiful", 20);
    engine.getGraphics().createSprite("menuSettingsBtn", "button");
    engine.getGraphics().createText(
        "SettingsText", "SETTINGS", "beautiful", 20);
    engine.getGraphics().createSprite("menuQuitBtn", "button");
    engine.getGraphics().createText("QuitText", "QUIT", "beautiful", 20);
}

/**
 * \fn void initLobbiesSprites(registry &reg, AEngine &engine)
 * \brief Function to init the lobbies sprites
 * \param reg The registry
 * \param engine The engine
 */
/*void initLobbiesSprites(registry &reg, AEngine &engine) {
    engine.getGraphics().createTexture("background2",
"assets/MenuBackground2.png");
    engine.getGraphics().createSprite("menuBackground2", "background2");
    engine.getGraphics().createTexture("logo", "assets/logo_rtype.png");
    engine.getGraphics().createSprite("logoRtype", "logo");

    auto const &rtypeLogo = reg.spawn_entity();
    reg.add_component(rtypeLogo, DrawableComponent("logoRtype", SPRITE));
    reg.add_component(rtypeLogo, TransformComponent({710, 100, 6}));

    engine.getGraphics().createTexture("button", "assets/button.png");

    //for (auto port : ports) {
    //    engine.getGraphics().createText((port + "Text"), "Lobby", "beautiful",
20);
    //    engine.getGraphics().createSprite(port, "button");
    //}
}*/

/**
 * \fn void initGameSprites(registry& reg, AEngine& engine)
 * \brief Function to init the game sprites
 * \param reg The registry
 * \param engine The engine
 */
void initGameSprites(AEngine& engine)
{
    engine.getGraphics().createTexture("wall1", "assets/wall.png");
    engine.getGraphics().createSprite("wall", "wall1");

    engine.getGraphics().createTexture("bullet1", "assets/bullet.png");
    engine.getGraphics().createSprite("bullet", "bullet1");

    engine.getGraphics().createTexture("parallax", "assets/para-bg9.png");
    engine.getGraphics().createSprite("para-bg", "parallax");
    engine.getGraphics().createSprite("para-bg2", "parallax");

    engine.getGraphics().createTexture("enemy1", "assets/enemyShip.png");
    engine.getGraphics().createSprite("enemySprite", "enemy1");

    engine.getGraphics().createTexture("player1", "assets/playerShip.png");
    engine.getGraphics().createSprite("playerSprite", "player1");
}


/**
 * \fn void createMenuBackground(registry& reg)
 * \brief Function to create the menu background
 * \param reg The registry
 */
void createMenuBackground(registry& reg)
{
    auto const& menuBackground = reg.spawn_entity();
    reg.add_component(
        menuBackground, DrawableComponent("menuBackground2", SPRITE));
    reg.add_component(menuBackground, TransformComponent({0, 0, 1}));
    reg.add_component(menuBackground, VelocityComponent(0));
    reg.add_component(menuBackground, ClocksComponent(0));
}

/**
 * \fn void createGameBackground(registry& reg)
 * \brief Function to create the game background
 * \param reg The registry
 */
void createGameBackground(registry& reg)
{
    auto const& paraBackground2 = reg.spawn_entity();
    reg.add_component(paraBackground2, DrawableComponent("para-bg2", SPRITE));
    reg.add_component(paraBackground2, TransformComponent({-1920, 0, 1}));
    reg.add_component(paraBackground2, VelocityComponent(3));
    reg.add_component(paraBackground2, ClocksComponent(0.017));

    sparse_array<ExecComponent>::reference_type exec3 =
        reg.add_component(paraBackground2, ExecComponent());
    if (exec3) {
        exec3.value().addFunction(moveLeftSecondPara);
    }

    auto const& paraBackground1 = reg.spawn_entity();
    reg.add_component(paraBackground1, DrawableComponent("para-bg", SPRITE));
    reg.add_component(paraBackground1, TransformComponent({0, 0, 1}));
    reg.add_component(paraBackground1, VelocityComponent(3));
    reg.add_component(paraBackground1, ClocksComponent(0.017));

    sparse_array<ExecComponent>::reference_type exec2 =
        reg.add_component(paraBackground1, ExecComponent());
    if (exec2) {
        exec2.value().addFunction(moveLeftFirstPara);
    }
}

/**
 * \fn void addMenuSystems(registry& reg)
 * \brief Function to add the menu systems
 * \param reg The registry
 */
void addMenuSystems(registry& reg)
{
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(KeyboardEventSystem);
    reg.add_system(execSystem);
    reg.add_system(clocksSystem);
    reg.add_system(MouseEventSystem);
}

/**
 * \fn void addGameSystems(registry& reg)
 * \brief Function to add the game systems
 * \param reg The registry
 */
void addGameSystems(registry& reg)
{
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(KeyboardEventSystem);
    reg.add_system(execSystem);
    reg.add_system(clocksSystem);
    reg.add_system(MouseEventSystem);
}

/**
 * \fn void getLobby(registry& reg, AEngine& engine, ServerToken& serverToken, size_t mainEntityIndex)
 * \brief Function to get the lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 * \param mainEntityIndex The main entity index
 */
void getLobby(registry& reg,
    AEngine& engine,
    ServerToken& serverToken,
    size_t mainEntityIndex)
{
    uint64_t header = ProtocolBuilder::createPacket(GET_HUB_LIST, 0, 0, 0, 0);
    char data[sizeof(header)];
    memcpy(data, &header, sizeof(header));
    if (serverToken.socket.send(
            data, sizeof(data), serverToken.adress, serverToken.port)
        != ASocket::SUCCES) {
        std::cout << "Send error when asking lobby" << std::endl;
    }
    usleep(10);
}

/**
 * \fn void initLobby(registry& reg, AEngine& engine, ServerToken& serverToken, size_t mainEntityIndex)
 * \brief Function to init the lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 * \param mainEntityIndex The main entity index
 */
void initLobby(registry& reg,
    AEngine& engine,
    ServerToken& serverToken,
    size_t mainEntityIndex)
{
    createMenuBackground(reg);
    engine.getGraphics().createText(
        "Waiting", "Waiting for connection", "beautiful", 25);
    auto const& waintingText = reg.spawn_entity();
    reg.add_component(waintingText, DrawableComponent("Waiting", TEXT));
    reg.add_component(waintingText, TransformComponent({700, 600, 1}));
    createMenuBtn(reg, BACK, {100, 900, 5});
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(MouseEventSystem);
    reg.add_system(execSystem);
    reg.add_system(clocksSystem);
    reg.add_system(ServerSystem);
}

/**
 * \fn void resetListListen(registry& reg, size_t mainEntityIndex)
 * \brief Function to reset the list listen
 * \param reg The registry
 * \param mainEntityIndex The main entity index
 */
void resetListListen(registry& reg, size_t mainEntityIndex)
{
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[mainEntityIndex];
    if (data) {
        std::vector<int> emptyList{};
        data.value().addValue("lobbyPort", emptyList);
    }
}

/**
 * \fn void initLobbies(registry& reg, AEngine& engine, ServerToken& serverToken, size_t mainEntityIndex)
 * \brief Function to init the lobbies
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 * \param mainEntityIndex The main entity index
 */
void initLobbies(registry& reg,
    AEngine& engine,
    ServerToken& serverToken,
    size_t mainEntityIndex)
{
    createMenuBackground(reg);
    resetListListen(reg, mainEntityIndex);
    auto& lobbyList = reg.spawn_entity();
    auto& lobbyData = reg.add_component(lobbyList, DataComponent());
    lobbyData->addValue<std::vector<size_t>>("idLobbyList", {});
    getLobby(reg, engine, serverToken, mainEntityIndex);

    auto const& input_lobby = reg.spawn_entity();
    engine.getGraphics().createText("lobbies",
        "All Lobby are above (if nothing then no lobby):",
        "beautiful",
        20);
    reg.add_component(input_lobby, DrawableComponent("lobbies", TEXT));
    reg.add_component(input_lobby, TransformComponent({400, 300, 1}));
    createMenuBtn(reg, BACK, {100, 900, 5});
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(MouseEventSystem);
    reg.add_system(execSystem);
    reg.add_system(clocksSystem);
    reg.add_system(ServerSystem);
}

/**
 * \fn void initSettings(registry& reg, AEngine& engine)
 * \brief Function to init the settings
 * \param reg The registry
 * \param engine The engine
 */
void initSettings(registry& reg, AEngine& engine)
{
    createMenuBackground(reg);
    auto const& input_lobby = reg.spawn_entity();
    //engine.getGraphics().createText("settings",
    //    "Settings",
    //    "beautiful",
    //    20);
    //reg.add_component(input_lobby, DrawableComponent("settings", TEXT));
    //reg.add_component(input_lobby, TransformComponent({400, 300, 1}));
    createMenuBtn(reg, BACK, {100, 900, 5});
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(MouseEventSystem);
    reg.add_system(execSystem);
    reg.add_system(clocksSystem);
}

/**
 * \fn void initMenu(registry& reg, AEngine& engine)
 * \brief Function to init the menu
 * \param reg The registry
 * \param engine The engine
 */
void initMenu(registry& reg, AEngine& engine)
{
    initMenuSprites(reg, engine);
    createMenuBackground(reg);
    createMenuBtn(reg, HOST_LOBBY, {850, 380, 5});
    createMenuBtn(reg, JOIN_LOBBY, {850, 430, 5});
    createMenuBtn(reg, LOCAL, {850, 480, 5});
    createMenuBtn(reg, SETTINGS, {850, 530, 5});
    createMenuBtn(reg, QUIT, {850, 580, 5});
    addMenuSystems(reg);
}

/**
 * \fn void initGame(registry& reg, AEngine& engine)
 * \brief Function to init the game
 * \param reg The registry
 * \param engine The engine
 */
void initGame(registry& reg, AEngine& engine)
{
    engine.getGraphics().createText("score", "Score : 0", "beautiful", 20);

    auto const& input = reg.spawn_entity();
    reg.add_component(input, DrawableComponent("score", TEXT));
    reg.add_component(input, TransformComponent({100, 100, 5}));

    engine.getAudio().stopSound("music");
    engine.getAudio().setSoundVolume("in-game", 10);
    engine.getAudio().playSound("in-game");
    initGameSprites(engine);
    createGameBackground(reg);
    createEntity(reg, ENTITY_PLAYER, {100, 100, 5}, -1, "dumb", "");
    createEntity(reg, BASIC_WALL, {512, 512, 5}, -1, "dumb", "");
    createEntity(reg, BASIC_ENEMY, {1500, 400, 5}, -1, "dumb", "basic");
    createEntity(reg, BASIC_ENEMY, {1500, 800, 5}, -1, "dumb", "advanced");
    addGameSystems(reg);
}

/**
 * \fn void initMultiplayer(registry& reg, AEngine& engine) 
 * \brief Function to init the multiplayer
 * \param reg The registry
 * \param engine The engine
 */
void initMultiplayer(registry& reg, AEngine& engine)
{
    engine.getAudio().stopSound("music");
    engine.getAudio().setSoundVolume("in-game", 10);
    engine.getAudio().playSound("in-game");
    initGameSprites(engine);
    createGameBackground(reg);
    addGameSystems(reg);
    reg.add_system(ServerSystem);
}

/**
 * \fn void initEnd(registry& reg, AEngine& engine)
 * \brief Function to init the end
 * \param reg The registry
 * \param engine The engine
 */
void initEnd(registry& reg, AEngine& engine)
{
    engine.getWindow().closeWindow();
    engine.stop();
}

/**
 * \fn void initStat(registry& reg, AEngine& engine)
 * \brief Function to init the stat
 * \param reg The registry
 * \param engine The engine
 */
void initStat(registry& reg, AEngine& engine)
{
}

/**
 * \fn void initCreateLobby(registry& reg, AEngine& engine, ServerToken& serverToken, size_t mainEntityIndex)
 * \brief Function to init the create lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 * \param mainEntityIndex The main entity index
 */
void initCreateLobby(registry& reg,
    AEngine& engine,
    ServerToken& serverToken,
    size_t mainEntityIndex)
{
    engine.getGraphics().createTexture("background1", "assets/space.jpg");
    engine.getGraphics().createSprite("menuBackground", "background1");

    engine.getGraphics().createFont("beautiful", "assets/font/font.ttf");
    engine.getGraphics().createTexture("logo", "assets/logo_rtype.png");
    engine.getGraphics().createSprite("logoRtype", "logo");
    engine.getGraphics().createText(
        "WelcomeText", "Enter lobby name and press Enter", "beautiful", 20);
    engine.getGraphics().createText(
        "lobby_name", "Enter lobby name here", "beautiful", 20);
    engine.getGraphics().createRectangle("backButton", 300, 40);

    auto const& background = reg.spawn_entity();
    reg.add_component(background, DrawableComponent("menuBackground", SPRITE));
    reg.add_component(background, TransformComponent());
    sparse_array<KeyboardEventComponent>::reference_type controllable =
        reg.add_component(background, KeyboardEventComponent());

    auto const& ent = reg.spawn_entity();
    reg.add_component(ent, DrawableComponent("WelcomeText", TEXT));
    reg.add_component(ent, TransformComponent({800, 300, 0}));
    reg.add_component(ent, ClocksComponent(1));

    if (controllable) {
        controllable.value().addAction(Key::Enter, accesWaitLobby);
    }

    auto const& rtypeLogo = reg.spawn_entity();
    reg.add_component(rtypeLogo, DrawableComponent("logoRtype", SPRITE));
    reg.add_component(rtypeLogo, TransformComponent({710, 100, 0}));

    auto const& rect = reg.spawn_entity();
    reg.add_component(rect, DrawableComponent("backButton", RECTANGLE));
    reg.add_component(rect, TransformComponent({790, 490, 0}));

    auto const& input_lobby = reg.spawn_entity();
    reg.add_component(input_lobby, DrawableComponent("lobby_name", TEXT));
    reg.add_component(input_lobby, TransformComponent({800, 500, 1}));
    reg.add_component(input_lobby, CollideComponent(300, 40, -10, -10));
    reg.add_component(input_lobby, InputComponent("lobby_name", 20));
    createMenuBtn(reg, BACK, {100, 900, 5});
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(MouseEventSystem);
    reg.add_system(KeyboardEventSystem);
    reg.add_system(clocksSystem);
    reg.add_system(inputSystem);
}

/**
 * \fn void initWaitLobby(registry& reg, AEngine& engine, ServerToken& serverToken, size_t mainEntityIndex)
 * \brief Function to init the wait lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 * \param mainEntityIndex The main entity index
 */
void initWaitInLobby(registry& reg,
    AEngine& engine,
    ServerToken& serverToken,
    size_t mainEntityIndex)
{
    engine.getGraphics().createTexture("background1", "assets/space.jpg");
    engine.getGraphics().createSprite("menuBackground", "background1");

    engine.getGraphics().createFont("beautiful", "assets/font/font.ttf");
    engine.getGraphics().createTexture("logo", "assets/logo_rtype.png");
    engine.getGraphics().createSprite("logoRtype", "logo");

    engine.getGraphics().createRectangle("readyBack", 100, 40);
    engine.getGraphics().createText("readyText", "Not Ready", "beautiful", 20);

    engine.getGraphics().createText("WelcomeText",
        engine.getGraphics()
            .getText("lobby_name")
            .append(" : Waiting for players..."),
        "beautiful",
        20);

    auto const& background = reg.spawn_entity();
    reg.add_component(background, DrawableComponent("menuBackground", SPRITE));
    reg.add_component(background, TransformComponent());
    sparse_array<KeyboardEventComponent>::reference_type controllable =
        reg.add_component(background, KeyboardEventComponent());

    auto const& ent = reg.spawn_entity();
    reg.add_component(ent, DrawableComponent("WelcomeText", TEXT));
    reg.add_component(ent, TransformComponent({800, 300, 0}));
    reg.add_component(ent, ClocksComponent(1));
    reg.add_component(ent, BlinkComponent(1));

    auto const& readyText = reg.spawn_entity();
    reg.add_component(readyText, DrawableComponent("readyText", TEXT));
    reg.add_component(readyText, TransformComponent({1500, 400, 2}));

    auto const& readyBack = reg.spawn_entity();
    reg.add_component(readyBack, DrawableComponent("readyBack", RECTANGLE));
    reg.add_component(readyBack, TransformComponent({1490, 390, 1}));
    reg.add_component(readyBack, CollideComponent(100, 40, 0, 0));
    sparse_array<MouseEventComponent>::reference_type readyMouseEvent =
        reg.add_component(readyBack, MouseEventComponent());
    createMenuBtn(reg, BACK, {100, 900, 5});
    if (readyMouseEvent) {
        readyMouseEvent->setOnClick(switchReady);
    }

    auto const& rtypeLogo = reg.spawn_entity();
    reg.add_component(rtypeLogo, DrawableComponent("logoRtype", SPRITE));
    reg.add_component(rtypeLogo, TransformComponent({710, 100, 0}));

    reg.add_system(blinkSystem);
    reg.add_system(gameSystem);
    reg.add_system(drawSystem);
    reg.add_system(MouseEventSystem);
    reg.add_system(KeyboardEventSystem);
    reg.add_system(clocksSystem);
}

/**
 * \fn void deleteAllComponents(registry& reg, size_t mainEntityIndex)
 * \brief Function to delete all components
 * \param reg The registry
 * \param mainEntityIndex The main entity index
 */
void deleteAllComponents(registry& reg, size_t mainEntityIndex)
{
    for (auto& entity : reg.getEntities()) {
        if (entity && entity->id != mainEntityIndex) {
            reg.kill_entity(entity.value());
        }
    }
    reg.clearAllSystems();
}

/**
 * \fn void gameSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to update the game
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void gameSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager && sceneManager->isUpdated()) {
            size_t mainEntityIndex = sceneManager->getEntityPos();
            deleteAllComponents(reg, mainEntityIndex);
            sceneManager->setUpdate(false);
            switch (sceneManager->getCurrentScene()) {
                case START:
                    initStart(reg, engine); break;
                case MENU:
                    initMenu(reg, engine); break;
                case LOBBY:
                    initLobby(reg, engine, serverToken, mainEntityIndex);
                    break;
                case LOBBIES:
                    initLobbies(reg, engine, serverToken, mainEntityIndex);
                    break;
                case SETINGS:
                    initSettings(reg, engine); break;
                case GAME:
                    initGame(reg, engine); break;
                case END:
                    initEnd(reg, engine); break;
                case STAT:
                    initStat(reg, engine); break;
                case CREATE_LOBBY:
                    initCreateLobby(reg, engine, serverToken, mainEntityIndex);
                    break;
                case WAIT_IN_LOBBY:
                    initWaitInLobby(reg, engine, serverToken, mainEntityIndex);
                    break;
                case MULTIPLAYER:
                    initMultiplayer(reg, engine);
                break;
            }
        }
    }
}