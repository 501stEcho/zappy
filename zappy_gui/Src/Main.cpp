/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** main
*/

#include "Interpreter/Handler.hpp"
#include <memory>
#define RLIGHTS_IMPLEMENTATION

#include "Core/Core3D.hpp"
#include "Core/CoreDebug.hpp"
#include "GameState/GameManager.hpp"
#include "GameState/GameState.hpp"
#include "Network/Client/Client.hpp"
#include "Parsing/Parser.hpp"

int main(int argc, char *const *argv)
{
    parsing::Parser parser(argc, argv);

    parser.addOption(parsing::Option("--debug"));
    parser.addOption(parsing::Option("--help"));
    parser.addOption(parsing::Option("-p", {"port"}, "is the port number", 1));
    parser.addOption(parsing::Option("-h", {"host"}, "is the name of the host; localhost by default", 1));

    try {
        parser.parse();
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        parser.displayUsage();
        return 84;
    }

    if (parser.optionIsSets("--help") || parser.getValues().size() ||
    !parser.optionIsSets("-p")) {
        parser.displayUsage();
        return 0;
    }

    auto &gameManager = Bean<gamestate::GameManager>::getInstance();
    auto &client = Bean<network::Client>::getInstance();
    std::unique_ptr<zappy::ICore> core;
    std::string serverName = parser.optionIsSets("-h") ? parser["-h"].front() : DEFAULT_SERVEUR_NAME;
    std::string port = parser["-p"].front();

    try {
        client.start(serverName, port);
        client.enqueueMessage("GRAPHIC");
        gameManager.start();
        if (parser.optionIsSets("--debug")) {
            core = std::make_unique<zappy::CoreDebug>();
        } else {
            core = std::make_unique<zappy::Core3D>();
        }
        while (core->start())
            ;

    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        parser.displayUsage();
    }
    try {
        client.stop();
    } catch (const std::exception &except) {
    }
    return 0;
}
