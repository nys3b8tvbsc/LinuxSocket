#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/time.h>

std::string getCurrentDayTime()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    std::time_t t = tv.tv_sec;

    std::stringstream ss;
    ss << "[" << std::put_time(std::localtime(&t), "%Y-%m-%d %T.") << std::setfill('0') << std::setw(3) << tv.tv_usec / 1000 << "]";
    return ss.str();
}

std::string createMessage(const std::string& client_name)
{
    std::stringstream ss;
    ss << getCurrentDayTime() << " " << client_name;
    return ss.str();
}
