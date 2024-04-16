#pragma once
#include <sys/stat.h>
#include <sys/types.h>

#include <filesystem>

#include "ExecComponent.hpp"
#include "KeyboardEventComponent.hpp"
#include "MouseEventComponent.hpp"
#include "ScriptEngine.hpp"
#include "ScriptRegistry.hpp"
#include "chaiscript/chaiscript.hpp"
#include "chaiscript/language/chaiscript_algebraic.hpp"

/**
 * \class Script
 * \brief The script class
 */
class Script
{
  public:
    /**
     * \fn Script(registry& reg, AEngine& engine)
     * \brief Constructor
     * \param reg The registry
     * \param engine The engine
     */
    Script(registry& reg, AEngine& engine)
        : scriptAudioEngine(engine.getAudio())
        , scriptEventEngine(engine.getEvent())
        , scriptGraphicsEngine(engine.getGraphics())
        , scriptWindowEngine(engine.getWindow())
        , scriptRegistry(reg)
    {
        /*!< add SceneType */
        chai.add(chaiscript::const_var(SceneType::START), "START");
        chai.add(chaiscript::const_var(SceneType::MENU), "MENU");
        chai.add(chaiscript::const_var(SceneType::SETINGS), "SETINGS");
        chai.add(chaiscript::const_var(SceneType::GAME), "GAME");
        chai.add(chaiscript::const_var(SceneType::END), "END");
        chai.add(chaiscript::const_var(SceneType::STAT), "STAT");

        /*!< add DrawableType */
        chai.add(chaiscript::const_var(DrawableType::UNKNOWN_TYPE), "UNKNOWN");
        chai.add(chaiscript::const_var(DrawableType::SPRITE), "SPRITE");
        chai.add(chaiscript::const_var(DrawableType::RECTANGLE), "RECTANGLE");
        chai.add(chaiscript::const_var(DrawableType::CIRCLE), "CIRCLE");
        chai.add(chaiscript::const_var(DrawableType::TEXT), "TEXT");

        /*!< add EventType */
        chai.add(chaiscript::const_var(EventType::Other), "Other");
        chai.add(chaiscript::const_var(EventType::Closed), "Closed");
        chai.add(chaiscript::const_var(EventType::Resized), "Resized");
        chai.add(chaiscript::const_var(EventType::LostFocus), "LostFocus");
        chai.add(chaiscript::const_var(EventType::GainedFocus), "GainedFocus");
        chai.add(chaiscript::const_var(EventType::TextEntered), "TextEntered");
        chai.add(chaiscript::const_var(EventType::KeyPressed), "KeyPressed");
        chai.add(chaiscript::const_var(EventType::KeyReleased), "KeyReleased");
        chai.add(chaiscript::const_var(EventType::MouseMoved), "MouseMoved");
        chai.add(chaiscript::const_var(EventType::MouseButtonPressed),
            "MouseButtonPressed");
        chai.add(
            chaiscript::const_var(EventType::MouseEntered), "MouseEntered");
        chai.add(chaiscript::const_var(EventType::MouseButtonReleased),
            "MouseButtonReleased");
        chai.add(chaiscript::const_var(EventType::MouseWheelMoved),
            "MouseWheelMoved");
        chai.add(chaiscript::const_var(EventType::MouseWheelScrolled),
            "MouseWheelScrolled");
        chai.add(chaiscript::const_var(EventType::MouseLeft), "MouseLeft");
        chai.add(chaiscript::const_var(EventType::JoystickButtonPressed),
            "JoystickButtonPressed");
        chai.add(chaiscript::const_var(EventType::JoystickButtonReleased),
            "JoystickButtonReleased");
        chai.add(
            chaiscript::const_var(EventType::JoystickMoved), "JoystickMoved");
        chai.add(chaiscript::const_var(EventType::JoystickConnected),
            "JoystickConnected");
        chai.add(chaiscript::const_var(EventType::JoystickDisconnected),
            "JoystickDisconnected");
        chai.add(chaiscript::const_var(EventType::TouchBegan), "TouchBegan");
        chai.add(chaiscript::const_var(EventType::TouchMoved), "TouchMoved");
        chai.add(chaiscript::const_var(EventType::TouchEnded), "TouchEnded");
        chai.add(
            chaiscript::const_var(EventType::SensorChanged), "SensorChanged");
        chai.add(chaiscript::const_var(EventType::Count), "Count");

        /*!< add mouse_t */
        chai.add(chaiscript::user_type<mouse_t>(), "Mouse_t");
        chai.add(chaiscript::constructor<mouse_t()>(), "Mouse_t");
        chai.add(chaiscript::constructor<mouse_t(
                     float, float, bool, bool, bool, float)>(),
            "Mouse_t");
        chai.add(chaiscript::constructor<mouse_t(mouse_t)>(), "Mouse_t");
        chai.add(chaiscript::constructor<mouse_t(mouse_t&)>(), "Mouse_t");
        chai.add(chaiscript::fun(&mouse_t::x), "x");
        chai.add(chaiscript::fun(&mouse_t::y), "y");
        chai.add(chaiscript::fun(&mouse_t::left), "left");
        chai.add(chaiscript::fun(&mouse_t::right), "right");
        chai.add(chaiscript::fun(&mouse_t::middle), "middle");
        chai.add(chaiscript::fun(&mouse_t::wheel), "wheel");

        /*!< add Position3D_t */
        chai.add(chaiscript::user_type<Position3D_t>(), "Position3D_t");
        chai.add(chaiscript::constructor<Position3D_t()>(), "Position3D_t");
        chai.add(chaiscript::constructor<Position3D_t(float, float, float)>(),
            "Position3D_t");
        chai.add(chaiscript::constructor<Position3D_t(Position3D_t)>(),
            "Position3D_t");
        chai.add(chaiscript::constructor<Position3D_t(Position3D_t&)>(),
            "Position3D_t");
        chai.add(chaiscript::fun(&Position3D_t::x), "x");
        chai.add(chaiscript::fun(&Position3D_t::y), "y");
        chai.add(chaiscript::fun(&Position3D_t::z), "z");

        /*!< add Position2D_t */
        chai.add(chaiscript::user_type<Position2D_t>(), "Position2D_t");
        chai.add(chaiscript::constructor<Position2D_t()>(), "Position2D_t");
        chai.add(chaiscript::constructor<Position2D_t(float, float)>(),
            "Position2D_t");
        chai.add(chaiscript::constructor<Position2D_t(Position2D_t)>(),
            "Position2D_t");
        chai.add(chaiscript::constructor<Position2D_t(Position2D_t&)>(),
            "Position2D_t");
        chai.add(chaiscript::fun(&Position2D_t::x), "x");
        chai.add(chaiscript::fun(&Position2D_t::y), "y");

        /*!< add Size2D_t */
        chai.add(chaiscript::user_type<Size2D_t>(), "Size2D_t");
        chai.add(chaiscript::constructor<Size2D_t()>(), "Size2D_t");
        chai.add(chaiscript::constructor<Size2D_t(float, float)>(), "Size2D_t");
        chai.add(chaiscript::constructor<Size2D_t(Size2D_t)>(), "Size2D_t");
        chai.add(chaiscript::constructor<Size2D_t(Size2D_t&)>(), "Size2D_t");
        chai.add(chaiscript::fun(&Size2D_t::width), "width");
        chai.add(chaiscript::fun(&Size2D_t::height), "height");

        /*!< add CollideBox */
        chai.add(chaiscript::user_type<CollideBox>(), "CollideBox");
        chai.add(chaiscript::constructor<CollideBox()>(), "CollideBox");
        chai.add(
            chaiscript::constructor<CollideBox(float, float)>(), "CollideBox");
        chai.add(
            chaiscript::constructor<CollideBox(CollideBox)>(), "CollideBox");
        chai.add(
            chaiscript::constructor<CollideBox(CollideBox&)>(), "CollideBox");
        chai.add(chaiscript::fun(&CollideBox::width), "width");
        chai.add(chaiscript::fun(&CollideBox::height), "height");

        /*!< add BufferMethod */
        chai.add(chaiscript::user_type<u_int64_t>(), "u_int64_t");
        chai.add(chaiscript::vector_conversion<
            std::vector<ServerPropertiesComponent::BufferMethod>>());
        chai.add(chaiscript::bootstrap::standard_library::vector_type<
            std::vector<ServerPropertiesComponent::BufferMethod>>(
            "BufferMethodList"));
        chai.add(
            chaiscript::user_type<ServerPropertiesComponent::BufferMethod>(),
            "BufferMethod");
        chai.add(
            chaiscript::constructor<ServerPropertiesComponent::BufferMethod(
                u_int64_t, std::string)>(),
            "BufferMethod");
        chai.add(
            chaiscript::constructor<ServerPropertiesComponent::BufferMethod(
                ServerPropertiesComponent::BufferMethod)>(),
            "BufferMethod");
        chai.add(
            chaiscript::constructor<ServerPropertiesComponent::BufferMethod(
                ServerPropertiesComponent::BufferMethod&)>(),
            "BufferMethod");
        chai.add(
            chaiscript::fun(&ServerPropertiesComponent::BufferMethod::header),
            "header");
        chai.add(
            chaiscript::fun(&ServerPropertiesComponent::BufferMethod::buffer),
            "buffer");

        /*!< add enum Key from AEventEngine file */
        chai.add(chaiscript::const_var(Key::Unknown), "Unknown");
        chai.add(chaiscript::const_var(Key::A), "A");
        chai.add(chaiscript::const_var(Key::B), "B");
        chai.add(chaiscript::const_var(Key::C), "C");
        chai.add(chaiscript::const_var(Key::D), "D");
        chai.add(chaiscript::const_var(Key::E), "E");
        chai.add(chaiscript::const_var(Key::F), "F");
        chai.add(chaiscript::const_var(Key::G), "G");
        chai.add(chaiscript::const_var(Key::H), "H");
        chai.add(chaiscript::const_var(Key::I), "I");
        chai.add(chaiscript::const_var(Key::J), "J");
        chai.add(chaiscript::const_var(Key::K), "K");
        chai.add(chaiscript::const_var(Key::L), "L");
        chai.add(chaiscript::const_var(Key::M), "M");
        chai.add(chaiscript::const_var(Key::N), "N");
        chai.add(chaiscript::const_var(Key::O), "O");
        chai.add(chaiscript::const_var(Key::P), "P");
        chai.add(chaiscript::const_var(Key::Q), "Q");
        chai.add(chaiscript::const_var(Key::R), "R");
        chai.add(chaiscript::const_var(Key::S), "S");
        chai.add(chaiscript::const_var(Key::T), "T");
        chai.add(chaiscript::const_var(Key::U), "U");
        chai.add(chaiscript::const_var(Key::V), "V");
        chai.add(chaiscript::const_var(Key::W), "W");
        chai.add(chaiscript::const_var(Key::X), "X");
        chai.add(chaiscript::const_var(Key::Y), "Y");
        chai.add(chaiscript::const_var(Key::Z), "Z");
        chai.add(chaiscript::const_var(Key::Num0), "Num0");
        chai.add(chaiscript::const_var(Key::Num1), "Num1");
        chai.add(chaiscript::const_var(Key::Num2), "Num2");
        chai.add(chaiscript::const_var(Key::Num3), "Num3");
        chai.add(chaiscript::const_var(Key::Num4), "Num4");
        chai.add(chaiscript::const_var(Key::Num5), "Num5");
        chai.add(chaiscript::const_var(Key::Num6), "Num6");
        chai.add(chaiscript::const_var(Key::Num7), "Num7");
        chai.add(chaiscript::const_var(Key::Num8), "Num8");
        chai.add(chaiscript::const_var(Key::Num9), "Num9");
        chai.add(chaiscript::const_var(Key::Escape), "Escape");
        chai.add(chaiscript::const_var(Key::LControl), "LControl");
        chai.add(chaiscript::const_var(Key::LShift), "LShift");
        chai.add(chaiscript::const_var(Key::LAlt), "LAlt");
        chai.add(chaiscript::const_var(Key::LSystem), "LSystem");
        chai.add(chaiscript::const_var(Key::RControl), "RControl");
        chai.add(chaiscript::const_var(Key::RShift), "RShift");
        chai.add(chaiscript::const_var(Key::RAlt), "RAlt");
        chai.add(chaiscript::const_var(Key::RSystem), "RSystem");
        chai.add(chaiscript::const_var(Key::Menu), "Menu");
        chai.add(chaiscript::const_var(Key::LBracket), "LBracket");
        chai.add(chaiscript::const_var(Key::RBracket), "RBracket");
        chai.add(chaiscript::const_var(Key::Semicolon), "Semicolon");
        chai.add(chaiscript::const_var(Key::Comma), "Comma");
        chai.add(chaiscript::const_var(Key::Period), "Period");
        chai.add(chaiscript::const_var(Key::Quote), "Quote");
        chai.add(chaiscript::const_var(Key::Slash), "Slash");
        chai.add(chaiscript::const_var(Key::Backslash), "Backslash");
        chai.add(chaiscript::const_var(Key::Tilde), "Tilde");
        chai.add(chaiscript::const_var(Key::Equal), "Equal");
        chai.add(chaiscript::const_var(Key::Hyphen), "Hyphen");
        chai.add(chaiscript::const_var(Key::Space), "Space");
        chai.add(chaiscript::const_var(Key::Enter), "Enter");
        chai.add(chaiscript::const_var(Key::Backspace), "Backspace");
        chai.add(chaiscript::const_var(Key::Tab), "Tab");
        chai.add(chaiscript::const_var(Key::PageUp), "PageUp");
        chai.add(chaiscript::const_var(Key::PageDown), "PageDown");
        chai.add(chaiscript::const_var(Key::End), "End");
        chai.add(chaiscript::const_var(Key::Home), "Home");
        chai.add(chaiscript::const_var(Key::Insert), "Insert");
        chai.add(chaiscript::const_var(Key::Delete), "Delete");
        chai.add(chaiscript::const_var(Key::Add), "Add");
        chai.add(chaiscript::const_var(Key::Subtract), "Subtract");
        chai.add(chaiscript::const_var(Key::Multiply), "Multiply");
        chai.add(chaiscript::const_var(Key::Divide), "Divide");
        chai.add(chaiscript::const_var(Key::Left), "Left");
        chai.add(chaiscript::const_var(Key::Right), "Right");
        chai.add(chaiscript::const_var(Key::Up), "Up");
        chai.add(chaiscript::const_var(Key::Down), "Down");
        chai.add(chaiscript::const_var(Key::Numpad0), "Numpad0");
        chai.add(chaiscript::const_var(Key::Numpad1), "Numpad1");
        chai.add(chaiscript::const_var(Key::Numpad2), "Numpad2");
        chai.add(chaiscript::const_var(Key::Numpad3), "Numpad3");
        chai.add(chaiscript::const_var(Key::Numpad4), "Numpad4");
        chai.add(chaiscript::const_var(Key::Numpad5), "Numpad5");
        chai.add(chaiscript::const_var(Key::Numpad6), "Numpad6");
        chai.add(chaiscript::const_var(Key::Numpad7), "Numpad7");
        chai.add(chaiscript::const_var(Key::Numpad8), "Numpad8");
        chai.add(chaiscript::const_var(Key::Numpad9), "Numpad9");
        chai.add(chaiscript::const_var(Key::F1), "F1");
        chai.add(chaiscript::const_var(Key::F2), "F2");
        chai.add(chaiscript::const_var(Key::F3), "F3");
        chai.add(chaiscript::const_var(Key::F4), "F4");
        chai.add(chaiscript::const_var(Key::F5), "F5");
        chai.add(chaiscript::const_var(Key::F6), "F6");
        chai.add(chaiscript::const_var(Key::F7), "F7");
        chai.add(chaiscript::const_var(Key::F8), "F8");
        chai.add(chaiscript::const_var(Key::F9), "F9");
        chai.add(chaiscript::const_var(Key::F10), "F10");
        chai.add(chaiscript::const_var(Key::F11), "F11");
        chai.add(chaiscript::const_var(Key::F12), "F12");
        chai.add(chaiscript::const_var(Key::F13), "F13");
        chai.add(chaiscript::const_var(Key::F14), "F14");
        chai.add(chaiscript::const_var(Key::F15), "F15");

        /*!< add the AudioEngine as global in chaiscript */
        chai.add(
            chaiscript::user_type<ScriptAudioEngine()>(), "ScriptAudioEngine");
        chai.add(chaiscript::var(&scriptAudioEngine), "AudioEngine");
        chai.add(
            chaiscript::fun(&ScriptAudioEngine::createSound), "createSound");
        chai.add(chaiscript::fun(&ScriptAudioEngine::playSound), "playSound");
        chai.add(chaiscript::fun(&ScriptAudioEngine::stopSound), "stopSound");
        chai.add(chaiscript::fun(&ScriptAudioEngine::pauseSound), "pauseSound");
        chai.add(
            chaiscript::fun(&ScriptAudioEngine::resumeSound), "resumeSound");
        chai.add(chaiscript::fun(&ScriptAudioEngine::setSoundVolume),
            "setSoundVolume");
        chai.add(
            chaiscript::fun(&ScriptAudioEngine::setSoundLoop), "setSoundLoop");
        chai.add(chaiscript::fun(&ScriptAudioEngine::setSoundPitch),
            "setSoundPitch");
        chai.add(
            chaiscript::fun(&ScriptAudioEngine::createMusic), "createMusic");
        chai.add(chaiscript::fun(&ScriptAudioEngine::playMusic), "playMusic");
        chai.add(chaiscript::fun(&ScriptAudioEngine::stopMusic), "stopMusic");
        chai.add(chaiscript::fun(&ScriptAudioEngine::pauseMusic), "pauseMusic");
        chai.add(
            chaiscript::fun(&ScriptAudioEngine::resumeMusic), "resumeMusic");
        chai.add(chaiscript::fun(&ScriptAudioEngine::setMusicVolume),
            "setMusicVolume");
        chai.add(
            chaiscript::fun(&ScriptAudioEngine::setMusicLoop), "setMusicLoop");
        chai.add(chaiscript::fun(&ScriptAudioEngine::setMusicPitch),
            "setMusicPitch");

        /*!< add the EventEngine as global in chaiscript */
        chai.add(
            chaiscript::user_type<ScriptEventEngine()>(), "ScriptEventEngine");
        chai.add(chaiscript::var(&scriptEventEngine), "EventEngine");
        chai.add(chaiscript::fun(&ScriptEventEngine::update), "update");
        chai.add(chaiscript::fun(&ScriptEventEngine::getKeysPressed),
            "getKeysPressed");
        chai.add(chaiscript::fun(&ScriptEventEngine::getKeysReleased),
            "getKeysReleased");
        chai.add(chaiscript::fun(&ScriptEventEngine::getEvents), "getEvents");
        chai.add(
            chaiscript::fun(&ScriptEventEngine::isKeyPressed), "isKeyPressed");
        chai.add(chaiscript::fun(&ScriptEventEngine::isKeyReleased),
            "isKeyReleased");
        chai.add(chaiscript::fun(&ScriptEventEngine::isEvent), "isEvent");
        chai.add(chaiscript::fun(&ScriptEventEngine::getMouse), "getMouse");

        /*!< add the GraphicsEngine as global in chaiscript */
        chai.add(chaiscript::user_type<ScriptGraphicsEngine()>(),
            "ScriptGraphicsEngine");
        chai.add(chaiscript::var(&scriptGraphicsEngine), "GraphicsEngine");
        chai.add(chaiscript::fun(&ScriptGraphicsEngine::createTexture),
            "createTexture");
        chai.add(chaiscript::fun(&ScriptGraphicsEngine::createSprite),
            "createSprite");
        chai.add(
            chaiscript::fun(&ScriptGraphicsEngine::drawSprite), "drawSprite");
        chai.add(chaiscript::fun(&ScriptGraphicsEngine::createCircle),
            "createCircle");
        chai.add(
            chaiscript::fun(&ScriptGraphicsEngine::drawCircle), "drawCircle");
        chai.add(chaiscript::fun(&ScriptGraphicsEngine::createRectangle),
            "createRectangle");
        chai.add(chaiscript::fun(&ScriptGraphicsEngine::drawRectangle),
            "drawRectangle");
        chai.add(
            chaiscript::fun(&ScriptGraphicsEngine::createFont), "createFont");
        chai.add(
            chaiscript::fun(&ScriptGraphicsEngine::createText), "createText");
        chai.add(chaiscript::fun(&ScriptGraphicsEngine::drawText), "drawText");

        /*!< add the WindowEngine as global in chaiscript */
        chai.add(chaiscript::user_type<ScriptWindowEngine()>(),
            "ScriptWindowEngine");
        chai.add(chaiscript::var(&scriptWindowEngine), "WindowEngine");
        chai.add(
            chaiscript::fun(&ScriptWindowEngine::closeWindow), "closeWindow");
        chai.add(chaiscript::fun(&ScriptWindowEngine::isOpen), "isOpen");
        chai.add(chaiscript::fun(&ScriptWindowEngine::clear), "clear");
        chai.add(chaiscript::fun(&ScriptWindowEngine::display), "display");

        /*!< add registry */
        chai.add(chaiscript::user_type<ScriptRegistry()>(), "ScriptRegistry");
        chai.add_global(chaiscript::var(&scriptRegistry), "Registry");

        /*!< add Entity */
        chai.add(chaiscript::user_type<Entity()>(), "Entity");
        chai.add(chaiscript::fun(&Entity::id), "id");
        chai.add(
            chaiscript::fun(&ScriptRegistry::spawn_entity), "spawn_entity");
        chai.add(
            chaiscript::fun(&ScriptRegistry::entity_exists), "entity_exists");
        chai.add(chaiscript::fun(&ScriptRegistry::kill_entity), "kill_entity");

        /*!< add DataComponents */
        chai.add(chaiscript::var(scriptRegistry.getDataComponents()),
            "DataComponents");
        chai.add(chaiscript::fun(&ScriptDataComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptDataComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptDataComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptDataComponents::add), "add");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::addStringAt), "addStringAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::setStringAt), "setStringAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::getStringAt), "getStringAt");
        chai.add(chaiscript::fun(&ScriptDataComponents::addIntAt), "addIntAt");
        chai.add(chaiscript::fun(&ScriptDataComponents::setIntAt), "setIntAt");
        chai.add(chaiscript::fun(&ScriptDataComponents::getIntAt), "getIntAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::addFloatAt), "addFloatAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::setFloatAt), "setFloatAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::getFloatAt), "getFloatAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::addBoolAt), "addBoolAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::setBoolAt), "setBoolAt");
        chai.add(
            chaiscript::fun(&ScriptDataComponents::getBoolAt), "getBoolAt");

        /*!< add BlinkComponents */
        chai.add(chaiscript::var(scriptRegistry.getBlinkComponents()),
            "BlinkComponents");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::add), "add");
        chai.add(
            chaiscript::fun(&ScriptBlinkComponents::isBlinkAt), "isBlinkAt");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::setClockLoopsAt),
            "setClockLoopsAt");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::addActualLoopAt),
            "addActualLoopAt");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::getClockNameAt),
            "getClockNameAt");
        chai.add(chaiscript::fun(&ScriptBlinkComponents::setClockNameAt),
            "setClockNameAt");

        /*!< add ClockComponents */
        chai.add(chaiscript::var(scriptRegistry.getClocksComponents()),
            "ClocksComponents");
        chai.add(chaiscript::fun(&ScriptClocksComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptClocksComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptClocksComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptClocksComponents::add), "add");
        chai.add(
            chaiscript::fun(&ScriptClocksComponents::addClockAt), "addClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::removeClockAt),
            "removeClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::updateClocksAt),
            "updateClocksAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::pauseClockAt),
            "pauseClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::playClockAt),
            "playClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::isRunningClockAt),
            "isRunningClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::refreshClockAt),
            "refreshClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::resetClockAt),
            "resetClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::loopClockAt),
            "loopClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::isTickClockAt),
            "isTickClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::pauseDefaultClockAt),
            "pauseDefaultClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::playDefaultClockAt),
            "playDefaultClockAt");
        chai.add(
            chaiscript::fun(&ScriptClocksComponents::isRunningDefaultClockAt),
            "isRunningDefaultClockAt");
        chai.add(
            chaiscript::fun(&ScriptClocksComponents::refreshDefaultClockAt),
            "refreshDefaultClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::resetDefaultClockAt),
            "resetDefaultClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::loopDefaultClockAt),
            "loopDefaultClockAt");
        chai.add(chaiscript::fun(&ScriptClocksComponents::isTickDefaultClockAt),
            "isTickDefaultClockAt");

        /*!< add DrawableComponents */
        chai.add(chaiscript::var(scriptRegistry.getDrawableComponents()),
            "DrawableComponents");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::add), "add");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::isEnableAt),
            "isEnableAt");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::setEnableAt),
            "setEnableAt");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::setDisableAt),
            "setDisableAt");
        chai.add(
            chaiscript::fun(&ScriptDrawableComponents::getNameAt), "getNameAt");
        chai.add(
            chaiscript::fun(&ScriptDrawableComponents::getTypeAt), "getTypeAt");
        chai.add(chaiscript::fun(&ScriptDrawableComponents::changeDrawableAt),
            "changeDrawableAt");

        /*!< addSceneManagerComponents */
        chai.add(chaiscript::var(scriptRegistry.getSceneManagerComponents()),
            "SceneManagerComponents");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::at), "at");
        chai.add(
            chaiscript::fun(&ScriptSceneManagerComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::add), "add");
        chai.add(
            chaiscript::fun(&ScriptSceneManagerComponents::getCurrentSceneAt),
            "getCurrentSceneAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::changeSceneAt),
            "changeSceneAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::setUpdateAt),
            "setUpdateAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::isUpdatedAt),
            "isUpdatedAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::setEntityPosAt),
            "setEntityPosAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::getEntityPosAt),
            "getEntityPosAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::isStartAt),
            "isStartAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::isMenuAt),
            "isMenuAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::isSettingsAt),
            "isSettingsAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::isGameAt),
            "isGameAt");
        chai.add(
            chaiscript::fun(&ScriptSceneManagerComponents::isEndAt), "isEndAt");
        chai.add(chaiscript::fun(&ScriptSceneManagerComponents::isStatAt),
            "isStatAt");

        /*!< addVelocityComponents */
        chai.add(chaiscript::var(scriptRegistry.getVelocityComponents()),
            "VelocityComponents");
        chai.add(chaiscript::fun(&ScriptVelocityComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptVelocityComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptVelocityComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptVelocityComponents::add), "add");
        chai.add(chaiscript::fun(&ScriptVelocityComponents::setVelocityAt),
            "setVelocityAt");
        chai.add(chaiscript::fun(&ScriptVelocityComponents::getVelocityAt),
            "getVelocityAt");

        /*!< add TransformComponents */
        chai.add(chaiscript::var(scriptRegistry.getTransformComponents()),
            "TransformComponents");
        chai.add(chaiscript::fun(&ScriptTransformComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptTransformComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptTransformComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptTransformComponents::add), "add");
        chai.add(chaiscript::fun(&ScriptTransformComponents::setPositionAt),
            "setPositionAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::moveAt), "moveAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::setRotationAt),
            "setRotationAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::setSizeAt),
            "setSizeAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::rescaleAt),
            "rescaleAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::getPositionAt),
            "getPositionAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::getRotationAt),
            "getRotationAt");
        chai.add(chaiscript::fun(&ScriptTransformComponents::getSizeAt),
            "getSizeAt");

        /*!< add ServerPropertiesComponents */
        chai.add(
            chaiscript::var(scriptRegistry.getServerPropertiesComponents()),
            "ServerPropertiesComponents");
        chai.add(
            chaiscript::fun(&ScriptServerPropertiesComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptServerPropertiesComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptServerPropertiesComponents::exists),
            "exists");
        chai.add(
            chaiscript::fun(&ScriptServerPropertiesComponents::add), "add");
        chai.add(chaiscript::fun(&ScriptServerPropertiesComponents::isUpdateAt),
            "isUpdateAt");
        chai.add(
            chaiscript::fun(&ScriptServerPropertiesComponents::setMethodListAt),
            "setMethodListAt");
        chai.add(
            chaiscript::fun(&ScriptServerPropertiesComponents::addMethodAt),
            "addMethodAt");
        chai.add(chaiscript::fun(&ScriptServerPropertiesComponents::getIdAt),
            "getIdAt");

        /*!< add ColliderComponents */
        chai.add(chaiscript::var(scriptRegistry.getCollideComponents()),
            "CollideComponents");
        chai.add(chaiscript::fun(&ScriptCollideComponents::size), "size");
        chai.add(chaiscript::fun(&ScriptCollideComponents::at), "at");
        chai.add(chaiscript::fun(&ScriptCollideComponents::exists), "exists");
        chai.add(chaiscript::fun(&ScriptCollideComponents::add), "add");
        chai.add(chaiscript::fun(&ScriptCollideComponents::isEnableAt),
            "isEnableAt");
        chai.add(chaiscript::fun(&ScriptCollideComponents::getCollideBoxAt),
            "getCollideBoxAt");
        chai.add(chaiscript::fun(&ScriptCollideComponents::isCollideAt),
            "isCollideAt");
    }

    ~Script() = default; /*!< Destructor */

    /**
     * \fn void add_script(std::string script)
     * \brief Add a script to the script engine
     * \param script the script to add
     */
    void add_script(std::string script)
    {
        scripts.push_back(script);
    }

    /**
     * \fn void add_script_from_file(std::string path)
     * \brief Add a script from a file to the script engine
     * \param path the path to the file
     */
    void add_script_from_file(std::string path)
    {
        std::ifstream file(path);
        if (!file)
            return;
        std::string str((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        scripts.push_back(str);
    }

    /**
     * \fn void add_scripts_from_folder(std::string path)
     * \brief Add all scripts from a folder to the script engine
     * \param path the path to the folder
     */
    void add_scripts_from_folder(std::string path)
    {
        if (!isDirectory(path)) {
            std::cout << "Error: " << path << " is not a directory"
                      << std::endl;
            return;
        }
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::cout << entry.path() << std::endl;
            if (entry.path().extension() == ".chai") {
                std::ifstream file(entry.path());
                std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
                scripts.push_back(str);
            }
        }
    }

    /**
     * \fn void update_scripts()
     * \brief Update all the scripts
     */
    void update_scripts()
    {
        for (auto& script : scripts) {
            chai.eval(script);
        }
    }

  private:
    /**
     * \fn bool isDirectory(const std::string& path)
     * \brief Check if a path is a directory
     * \param path the path to check
     * \return true if the path is a directory, false otherwise
     */
    bool isDirectory(const std::string& path)
    {
        struct stat info;
        return stat(path.c_str(), &info) == 0 && info.st_mode & S_IFDIR;
    }
    chaiscript::ChaiScript chai; /*!< ChaiScript object */
    std::vector<std::string> scripts; /*!< Vector of scripts */
    ScriptAudioEngine scriptAudioEngine; /*!< ScriptAudioEngine object */
    ScriptEventEngine scriptEventEngine; /*!< ScriptEventEngine object */
    ScriptGraphicsEngine scriptGraphicsEngine; /*!< ScriptGraphicsEngine object */
    ScriptWindowEngine scriptWindowEngine; /*!< ScriptWindowEngine object */
    ScriptRegistry scriptRegistry; /*!< ScriptRegistry */
};