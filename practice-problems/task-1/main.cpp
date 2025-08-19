#include <iostream>
#include <string>

#include "Commands.cpp"

int main() {
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "cp") {
            std::cin.ignore();
            std::string name;
            std::getline(std::cin, name);
            cmd_cp(name);
        }
        else if (cmd == "cc") {
            std::string color, name;
            std::cin >> color;
            std::cin.ignore();
            std::getline(std::cin, name);
            cmd_cc(color, name);
        }
        else if (cmd == "cd") {
            std::string player;
            std::cin.ignore();
            std::getline(std::cin, player);
            std::vector<std::string> cards;
            for (int i = 0; i < 60; i++) {
                std::string cname;
                std::getline(std::cin, cname);
                cards.push_back(cname);
            }
            cmd_cd(player, cards);
        }
        else if (cmd == "report") {
            cmd_report();
        }
        else {
            break;
        }
    }
}