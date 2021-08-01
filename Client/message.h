#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

/*!
 * \brief Creates string with the current date and time.
 * \return std::string [yyyy-mm-dd hh:mm:ss.ms]
 */
std::string getCurrentDayTime();

/*!
 * \brief Creates message that the client sends.
 * \param client_name std::string Name of client
 * \return std::string "[yyyy-mm-dd hh:mm:ss.ms] client_name"
 */
std::string createMessage(const std::string& client_name);

#endif // MESSAGE_H
