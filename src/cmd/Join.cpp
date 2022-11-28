#include "../../incl/cmd/Join.hpp"

ft::Join::Join(void)
{
    _name = "Join";
    _description = "Join a channel";
    _usage = "/join <channel> [key]";
}

void ft::Join::execute()
{
    std::cout << "Join executed" << std::endl;
}
