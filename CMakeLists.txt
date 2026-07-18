cmake_minimum_required(VERSION 3.16)

project(RedisClone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(redis-clone
    src/main.cpp
    src/storage/DataStore.cpp
    src/commands/CommandParser.cpp
    src/commands/CommandExecutor.cpp
    src/server/Server.cpp
    src/logger/Logger.cpp
)