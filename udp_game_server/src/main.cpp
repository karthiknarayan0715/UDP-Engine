#include <iostream>
#include "server/server.h"
#include "game/global_physics.h"
#include "physics/bullet/bullet_init.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace std;
int main() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/server.log", true);
    file_sink->set_level(spdlog::level::debug);
    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    auto combined_logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
    spdlog::set_default_logger(combined_logger);
    spdlog::set_level(spdlog::level::debug);
    
    LoadMaps();
    if (Server::getInstance().Start() != 1) {
        spdlog::error("Error: UDP Server not Started, Internal Error");
    };
    spdlog::error("Server's work is done!");
}