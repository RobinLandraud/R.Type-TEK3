#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "AEventEngine.hpp"

/**
 * \class SFMLEventEngine
 * \brief A class that handle the event.
 * Used to handle the event
 */
class SFMLEventEngine : public AEventEngine
{
  public:
    SFMLEventEngine(sf::RenderWindow& window);  /*!< Default constructor */

    /**
     * \fn virtual void update() override;
     * \brief Update the event
     */
    virtual void update() override;

    /**
     * \fn void updateKeys();
     * \brief Update the keys
     */
    void updateKeys();

  private:
    sf::RenderWindow& window; /*!< The window */
    std::map<sf::Keyboard::Key, Key> keys = {
        {sf::Keyboard::Up, Up},
        {sf::Keyboard::Down, Down},
        {sf::Keyboard::Left, Left},
        {sf::Keyboard::Right, Right},
        {sf::Keyboard::Enter, Enter},
        {sf::Keyboard::Escape, Escape},
        {sf::Keyboard::A, A},
        {sf::Keyboard::B, B},
        {sf::Keyboard::C, C},
        {sf::Keyboard::D, D},
        {sf::Keyboard::E, E},
        {sf::Keyboard::F, F},
        {sf::Keyboard::G, G},
        {sf::Keyboard::H, H},
        {sf::Keyboard::I, I},
        {sf::Keyboard::J, J},
        {sf::Keyboard::K, K},
        {sf::Keyboard::L, L},
        {sf::Keyboard::M, M},
        {sf::Keyboard::N, N},
        {sf::Keyboard::O, O},
        {sf::Keyboard::P, P},
        {sf::Keyboard::Q, Q},
        {sf::Keyboard::R, R},
        {sf::Keyboard::S, S},
        {sf::Keyboard::T, T},
        {sf::Keyboard::U, U},
        {sf::Keyboard::V, V},
        {sf::Keyboard::W, W},
        {sf::Keyboard::X, X},
        {sf::Keyboard::Y, Y},
        {sf::Keyboard::Z, Z},
        {sf::Keyboard::BackSpace, Backspace},
        {sf::Keyboard::Space, Space},
        {sf::Keyboard::Num0, Num0},
        {sf::Keyboard::Num1, Num1},
        {sf::Keyboard::Num2, Num2},
        {sf::Keyboard::Num3, Num3},
        {sf::Keyboard::Num4, Num4},
        {sf::Keyboard::Num5, Num5},
        {sf::Keyboard::Num6, Num6},
        {sf::Keyboard::Num7, Num7},
        {sf::Keyboard::Num8, Num8},
        {sf::Keyboard::Num9, Num9},
        {sf::Keyboard::Numpad0, Numpad0},
        {sf::Keyboard::Numpad1, Numpad1},
        {sf::Keyboard::Numpad2, Numpad2},
        {sf::Keyboard::Numpad3, Numpad3},
        {sf::Keyboard::Numpad4, Numpad4},
        {sf::Keyboard::Numpad5, Numpad5},
        {sf::Keyboard::Numpad6, Numpad6},
        {sf::Keyboard::Numpad7, Numpad7},
        {sf::Keyboard::Numpad8, Numpad8},
        {sf::Keyboard::Numpad9, Numpad9},
        {sf::Keyboard::Comma, Comma},
        {sf::Keyboard::Period, Period},
        {sf::Keyboard::Quote, Quote},
        {sf::Keyboard::Hyphen, Hyphen},
    };  /*!< The keys */
    std::map<sf::Event::EventType, EventType> eventTypes = {
        {sf::Event::Closed, Closed},
        {sf::Event::Resized, Resized},
        {sf::Event::LostFocus, LostFocus},
        {sf::Event::GainedFocus, GainedFocus},
        {sf::Event::TextEntered, TextEntered},
        {sf::Event::KeyPressed, KeyPressed},
        {sf::Event::KeyReleased, KeyReleased},
        {sf::Event::MouseWheelMoved, MouseWheelMoved},
        {sf::Event::MouseWheelScrolled, MouseWheelScrolled},
        {sf::Event::MouseButtonPressed, MouseButtonPressed},
        {sf::Event::MouseButtonReleased, MouseButtonReleased},
        {sf::Event::MouseMoved, MouseMoved},
        {sf::Event::MouseEntered, MouseEntered},
        {sf::Event::MouseLeft, MouseLeft},
        {sf::Event::JoystickButtonPressed, JoystickButtonPressed},
        {sf::Event::JoystickButtonReleased, JoystickButtonReleased},
        {sf::Event::JoystickMoved, JoystickMoved},
        {sf::Event::JoystickConnected, JoystickConnected},
        {sf::Event::JoystickDisconnected, JoystickDisconnected},
        {sf::Event::TouchBegan, TouchBegan},
        {sf::Event::TouchMoved, TouchMoved},
        {sf::Event::TouchEnded, TouchEnded},
        {sf::Event::SensorChanged, SensorChanged}};
};  /*!< The Event Types */