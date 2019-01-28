cmake_minimum_required(VERSION 3.12)
project(AgeofWar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")

add_executable(AgeofWar
        src/main.cpp

        src/Game.cpp
        src/Playground.cpp
        #src/Serializable.cpp

        src/Player.cpp
        src/AIPlayer.cpp

        src/Entity.cpp
        src/Base.cpp

        src/AreaOfEffect.cpp
        src/Range.cpp

        src/Unit.cpp
        src/RecruitableUnit.cpp

        src/Soldier.cpp
        src/Archer.cpp
        src/Catapult.cpp

        src/utils/bitstream.cpp src/SuperSoldier.cpp src/SuperSoldier.hpp src/utils/ANSIColors.hpp src/utils/ANSIColors.cpp)