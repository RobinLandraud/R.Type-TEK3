#include "Server.hpp"

/**
 * \fn int main(int argc, char** argv)
 * \brief The main function
 * \param argc The number of arguments
 * \param argv The arguments
 * \return The exit code
 */
int main(int argc, char** argv)
{
    Server server;
    server.handleUser();
    return 0;
}
