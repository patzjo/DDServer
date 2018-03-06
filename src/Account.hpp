#pragma once
#include <string>

namespace DDServer
{
    class Account
    {
    public:
        std::string getUserName() const { return userName; };
        unsigned long long getAccountID() const { return accountID; };
        
    private:
        std::string userName;
        unsigned long long accountID;
    };


}