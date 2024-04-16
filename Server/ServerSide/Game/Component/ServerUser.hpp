#include <utility>

#include "User.hpp"

/**
 * \class ServerUser
 * \brief Class representing a user on the server
 */
class ServerUser
{
  public:
    ServerUser() = default; /*!< Default constructor */
    /**
     * \fn explicit ServerUser(User insertUser)
     * \brief Constructor
     * \param insertUser User to insert
     */
    explicit ServerUser(User insertUser)
        : user(std::move(insertUser)){};
    ~ServerUser() = default; /*!< Default destructor */

    ServerUser(ServerUser const&) = default; /*!< Default copy constructor */
    ServerUser(ServerUser&&) noexcept = default; /*!< Default move constructor */
    ServerUser& operator=(
        ServerUser const&) = default; /*!< Default copy assignment operator */
    ServerUser& operator=(
        ServerUser&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn [[nodiscard]] User getUser() const
     * \brief Get the user
     * \return the user
     */
    [[nodiscard]] User getUser() const
    {
        return user;
    }

  private:
    User user; /*!< User */
    int score = 0; /*!< Score */
};