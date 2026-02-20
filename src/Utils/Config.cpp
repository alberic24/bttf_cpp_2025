#include "Utils/Config.hpp"
#include <iostream>

namespace Config {
    Settings settings;
    
    void Settings::save(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << "volume=" << volume << "\n";
            file << "fullscreen=" << (fullscreen ? "1" : "0") << "\n";
            file.close();
            std::cout << "Settings saved to " << filename << std::endl;
        }
    }
    
    void Settings::load(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string key, value;
                if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                    if (key == "volume") {
                        volume = std::stof(value);
                    } else if (key == "fullscreen") {
                        fullscreen = (value == "1");
                    }
                }
            }
            file.close();
            std::cout << "Settings loaded from " << filename << std::endl;
        }
    }
}