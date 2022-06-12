//
// Created by pawel on 09/06/2022.
//

#ifndef KONSERWATORIUM_SHARED_H
#define KONSERWATORIUM_SHARED_H


#include <stdexcept>

namespace shared {
    class NotImplementedError : public std::logic_error {
    public:
        NotImplementedError() : std::logic_error("Method not yet implemented!") {};
    };

    class Logger {
    private:
        Logger() = default;
    public:
        static void print_welcome();
        static void print_help();
    };
}

#endif //KONSERWATORIUM_SHARED_H
