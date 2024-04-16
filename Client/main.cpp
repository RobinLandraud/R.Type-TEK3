/*
** EPITECH PROJECT, 2022
** R_type
** File description:
** a good game
*/

#include "Core.hpp"

/**
 * \fn int main()
 * \brief The main function
 * \return The exit code
 */
int main()
{
    Core core;
    core.initStart();
    return core.loop();
}