#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "AEventEngine.hpp"
#include "CollideComponent.hpp"
#include "Registry.hpp"
#include "TransformComponent.hpp"

/**
 * \class InputComponent
 * \brief A component that handle a button.
 * Used to create a button
 */
class InputComponent
{
  public:
    /**
     * \fn InputComponent(std::string textName, size_t maxSize)
     * \brief Constructor
     * \param textName the name of the text
     * \param maxSize the max size of the text
     */
    InputComponent(std::string textName, size_t maxSize)
        : textName(textName)
        , maxSize(maxSize)
    {
    }
    ~InputComponent() = default; /*!< Default destructor */

    InputComponent(
        InputComponent const&) = default; /*!< Default copy constructor */
    InputComponent(
        InputComponent&&) noexcept = default; /*!< Default move constructor */
    InputComponent& operator=(
        InputComponent const&) = default; /*!< Default copy assignment operator */
    InputComponent& operator=(
        InputComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void updateOn(AEngine& engine, TransformComponent& transform, CollideComponent& collide)
     * \brief set engine to update on
     * \param engine the engine
     * \param transform the transform component
     * \param collide the collide component
     */
    void updateOn(AEngine& engine,
        TransformComponent& transform,
        CollideComponent& collide)
    {
        mouse_t mouse = engine.getEvent().getMouse();
        if (mouse.left == true || mouse.right == true) {
            isOn = collide.isCollide(transform, mouse.x, mouse.y);
        }
    }

    /**
     * \fn void update(AEngine& engine, TransformComponent& transform, CollideComponent& collide)
     * \brief update the input
     * \param engine the engine
     * \param transform the transform component
     * \param collide the collide component
     */
    void update(AEngine& engine,
        TransformComponent& transform,
        CollideComponent& collide)
    {
        updateOn(engine, transform, collide);
        if (!isOn)
            return;
        auto& keysReleased = engine.getEvent().getKeysReleased();
        std::string text = engine.getGraphics().getText(textName);
        for (auto& key : keysReleased) {
            if (key == Key::Backspace) {
                if (!text.empty())
                    text = "";
            } else if (key == Key::Enter) {
                isOn = false;
            } else if (text.size() < maxSize || maxSize <= 0) {
                if (charByKey.find(key) != charByKey.end()) {
                    text += charByKey[key];
                }
            }
        }
        engine.getGraphics().changeText(textName, text);
    }

  private:
    bool isOn = false;      /*!< If the input is on */
    std::string textName;   /*!< The name of the text */
    size_t maxSize;
    std::unordered_map<Key, std::string> charByKey = {
        {Key::A, "a"},
        {Key::B, "b"},
        {Key::C, "c"},
        {Key::D, "d"},
        {Key::E, "e"},
        {Key::F, "f"},
        {Key::G, "g"},
        {Key::H, "h"},
        {Key::I, "i"},
        {Key::J, "j"},
        {Key::K, "k"},
        {Key::L, "l"},
        {Key::M, "m"},
        {Key::N, "n"},
        {Key::O, "o"},
        {Key::P, "p"},
        {Key::Q, "q"},
        {Key::R, "r"},
        {Key::S, "s"},
        {Key::T, "t"},
        {Key::U, "u"},
        {Key::V, "v"},
        {Key::W, "w"},
        {Key::X, "x"},
        {Key::Y, "y"},
        {Key::Z, "z"},
        {Key::Num0, "0"},
        {Key::Num1, "1"},
        {Key::Num2, "2"},
        {Key::Num3, "3"},
        {Key::Num4, "4"},
        {Key::Num5, "5"},
        {Key::Num6, "6"},
        {Key::Num7, "7"},
        {Key::Num8, "8"},
        {Key::Num9, "9"},
        {Key::Numpad0, "0"},
        {Key::Numpad1, "1"},
        {Key::Numpad2, "2"},
        {Key::Numpad3, "3"},
        {Key::Numpad4, "4"},
        {Key::Numpad5, "5"},
        {Key::Numpad6, "6"},
        {Key::Numpad7, "7"},
        {Key::Numpad8, "8"},
        {Key::Numpad9, "9"},
        {Key::Quote, "4"},
        {Key::Hyphen, "6"},
        {Key::Space, " "},
        {Key::Period, "."},
        {Key::Comma, ","},
    };  /*!< The char by key */
};