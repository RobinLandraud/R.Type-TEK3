#include <iostream>
#include <vector>

#pragma once

/**
 * \enum Key
 * \brief Enum for keys.
 * Used to know which key is pressed
 */
enum Key {
    Unknown = -1,
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Escape,
    LControl,
    LShift,
    LAlt,
    LSystem,
    RControl,
    RShift,
    RAlt,
    RSystem,
    Menu,
    LBracket,
    RBracket,
    Semicolon,
    Comma,
    Period,
    Quote,
    Slash,
    Backslash,
    Tilde,
    Equal,
    Hyphen,
    Space,
    Enter,
    Backspace,
    Tab,
    PageUp,
    PageDown,
    End,
    Home,
    Insert,
    Delete,
    Add,
    Subtract,
    Multiply,
    Divide,
    Left,
    Right,
    Up,
    Down,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15
};

/**
 * \enum EventType
 * \brief Enum for events.
 * Used to know which event is triggered
 */
enum EventType {
    Other = -1,
    Closed = 0,
    Resized,
    LostFocus,
    GainedFocus,
    TextEntered,
    KeyPressed,
    KeyReleased,
    MouseMoved,
    MouseButtonPressed,
    MouseEntered,
    MouseButtonReleased,
    MouseWheelMoved,
    MouseWheelScrolled,
    MouseLeft,
    JoystickButtonPressed,
    JoystickButtonReleased,
    JoystickMoved,
    JoystickConnected,
    JoystickDisconnected,
    TouchBegan,
    TouchMoved,
    TouchEnded,
    SensorChanged,
    Count
};

/**
 * \struct mouse_t
 * \brief Struct for mouse.
 * Used to know the mouse informations
 */
struct mouse_t {
    float x;     /*!< X position */
    float y;     /*!< Y position */
    bool left;   /*!< Left button */
    bool right;  /*!< Right button */
    bool middle; /*!< Middle button */
    float wheel; /*!< Wheel */
};

/**
 * \class AEventEngine
 * \brief Abstract class for event engine.
 * Used to manage events
 */
class AEventEngine
{
  public:
    AEventEngine() = default;          /*!< Default constructor */
    virtual ~AEventEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual void update() = 0
     * \brief Update the event engine
     */
    virtual void update() = 0;

    /**
     * \fn std::vector<Key> &getKeysPressed()
     * \brief Get the keys pressed
     * \return The keys pressed
     */
    std::vector<Key>& getKeysPressed();

    /**
     * \fn std::vector<Key> &getKeysReleased()
     * \brief Get the keys released
     * \return The keys released
     */
    std::vector<Key>& getKeysReleased();

    /**
     * \fn std::vector<EventType> &getEvents()
     * \brief Get the events
     * \return The events
     */
    std::vector<EventType>& getEvents();

    /**
     * \fn mouse_t &getMouse()
     * \brief Get the mouse
     * \return The mouse
     */
    mouse_t& getMouse();

  protected:
    std::vector<Key> keysPressed;                   /*!< Keys pressed */
    std::vector<Key> keysReleased;                  /*!< Keys released */
    std::vector<EventType> events;                  /*!< Events */
    mouse_t mouse = {0, 0, false, false, false, 0}; /*!< Mouse */
};