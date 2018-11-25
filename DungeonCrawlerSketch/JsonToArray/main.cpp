#include <iostream>
#include "json.hpp"

void addEnemies( std::string &, const int &, const int & );
void addPatrollers( std::string &, const int &, const int & );
void addWind( std::string &, const int &, const int & );
void addLava( std::string &, const int &, const int & );

using json = nlohmann::json;
json jobj = "{\"num\":3,\"levels\":[{\"ppos\":0,\"Enemies\":{\"num\":1,\"pos\":[250],\"delay\":[0]},\"Patrollers\":{\"num\":0},\"Lava\":{\"num\":0},\"Wind\":{\"num\":0}},{\"ppos\":20,\"Enemies\":{\"num\":1,\"pos\":[250],\"delay\":[0]},\"Patrollers\":{\"num\":1,\"pos\":[150],\"offset\":[0]},\"Lava\":{\"num\":3,\"pos\":[150,160,170],\"length\":[10,10,10]},\"Wind\":{\"num\":2,\"pos\":[30,40],\"mul\":[1,1]}},{\"ppos\":20,\"Enemies\":{\"num\":5,\"pos\":[100,105,110,115,120],\"delay\":[0,10,20,30,40]},\"Patrollers\":{\"num\":3,\"pos\":[150,155,160],\"offset\":[0,100,200]},\"Lava\":{\"num\":1,\"pos\":[290],\"length\":[30]},\"Wind\":{\"num\":4,\"pos\":[30,40,50,60],\"mul\":[1,1,-1,-1]}}]}"_json;

int main() {

    //std::string str = "{\"num\":2,\"levels\":[{\"ppos\":0,\"Enemies\":{\"num\":1,\"pos\":[250],\"delay\":[0]},\"Patrollers\":{\"num\":0},\"Lava\":{\"num\":0},\"Wind\":{\"num\":0}},{\"ppos\":20,\"Enemies\":{\"num\":1,\"pos\":[250],\"delay\":[0]},\"Patrollers\":{\"num\":1,\"pos\":[150]},\"Lava\":{\"num\":1,\"pos\":[150]},\"Wind\":{\"num\":2,\"pos\":[30,40],\"mul\":[1,1]}},{\"ppos\":20,\"Enemies\":{\"num\":5,\"pos\":[100,105,110,115,120],\"delay\":[0]},\"Patrollers\":{\"num\":3,\"pos\":[150,155,160]},\"Lava\":{\"num\":1,\"pos\":[290]},\"Wind\":{\"num\":4,\"pos\":[30,40,50,60],\"mul\":[1,1,-1,-1]}}]}";

    std::string array = "{\n";

    int total_levels = jobj["num"];
    //std::cout << jobj["levels"][0]["Enemies"]["num"];
    for ( int level_num = 0; level_num < total_levels; ++level_num ) {
        array += "\t{";

        // player positions
        int ppos = jobj["levels"][level_num]["ppos"];
        array += std::to_string(ppos) + ", ";

        // ENEMIES --------------------------------------------------------------------------------------
        int total_enemies = jobj["levels"][level_num]["Enemies"]["num"];
        array += std::to_string( total_enemies ) + ", ";

        array += "{";
        addEnemies( array, level_num, total_enemies );
        array += "}, ";

        // PATROLLERS -----------------------------------------------------------------------------------
        int total_patrollers = jobj["levels"][level_num]["Patrollers"]["num"];
        array += std::to_string( total_patrollers ) + ", ";

        array += "{";
        addPatrollers( array, level_num, total_patrollers );
        array += "}, ";

        // LAVAS ----------------------------------------------------------------------------------------
        int total_lavas = jobj["levels"][level_num]["Lava"]["num"];
        array += std::to_string( total_lavas ) + ", ";

        array += "{";
        addLava( array, level_num, total_lavas );
        array += "}, ";

        // add the number of winds
        int total_winds = jobj["levels"][level_num]["Wind"]["num"];
        array += std::to_string( total_winds ) + ", ";

        array += "{";
        addWind( array, level_num, total_winds );

        // add the last curly brace
        if ( level_num == total_levels - 1 ) {
            array += '}';
        }
        else {
            array += "},\n";
        }
    }

    array += "\n};";

    std::cout << array;

    return 0;
}

void addEnemies( std::string &array, const int &level_num, const int &total_enemies ) {
    if ( total_enemies == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_enemies; ++a ) {
        int enemy_a_pos = jobj["levels"][level_num]["Enemies"]["pos"][a];
        if ( a == total_enemies - 1 ) {
            array += std::to_string( enemy_a_pos );
        }
        else {
            array += std::to_string( enemy_a_pos ) + ", ";
        }
    }
    array += "}, ";

    array += "{";

    if ( total_enemies == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_enemies; ++a ) {
        int enemy_a_pos = jobj["levels"][level_num]["Enemies"]["delay"][a];
        if ( a == total_enemies - 1 ) {
            array += std::to_string( enemy_a_pos );
        }
        else {
            array += std::to_string( enemy_a_pos ) + ", ";
        }
    }
}

void addPatrollers( std::string &array, const int &level_num, const int &total_patrollers ) {
    if ( total_patrollers == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_patrollers; ++a ) {
        int patroller_a_pos = jobj["levels"][level_num]["Patrollers"]["pos"][a];
        if ( a == total_patrollers - 1 ) {
            array += std::to_string( patroller_a_pos );
        }
        else {
            array += std::to_string( patroller_a_pos ) + ", ";
        }
    }
    array += "}, ";

    array += "{";

    if ( total_patrollers == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_patrollers; ++a ) {
        int patroller_a_pos = jobj["levels"][level_num]["Patrollers"]["offset"][a];
        if ( a == total_patrollers - 1 ) {
            array += std::to_string( patroller_a_pos );
        }
        else {
            array += std::to_string( patroller_a_pos ) + ", ";
        }
    }
}

void addLava( std::string &array, const int &level_num, const int &total_lavas ) {
    if ( total_lavas == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_lavas; ++a ) {
        int lava_a_pos = jobj["levels"][level_num]["Lava"]["pos"][a];
        if ( a == total_lavas - 1 ) {
            array += std::to_string( lava_a_pos );
        }
        else {
            array += std::to_string( lava_a_pos ) + ", ";
        }
    }
    array += "}, ";

    array += "{";

    if ( total_lavas == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_lavas; ++a ) {
        int lava_a_pos = jobj["levels"][level_num]["Lava"]["length"][a];
        if ( a == total_lavas - 1 ) {
            array += std::to_string( lava_a_pos );
        }
        else {
            array += std::to_string( lava_a_pos ) + ", ";
        }
    }
}

void addWind( std::string &array, const int &level_num, const int &total_winds ) {
    if ( total_winds == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_winds; ++a ) {
        int wind_a_pos = jobj["levels"][level_num]["Wind"]["pos"][a];
        if ( a == total_winds - 1 ) {
            array += std::to_string( wind_a_pos );
        }
        else {
            array += std::to_string( wind_a_pos ) + ", ";
        }
    }
    array += "}, {";

    if ( total_winds == 0 ) {
        array += "0";
    }

    for ( int a = 0; a < total_winds; ++a ) {
        int lava_a_pos = jobj["levels"][level_num]["Wind"]["mul"][a];
        if ( a == total_winds - 1 ) {
            array += std::to_string( lava_a_pos );
        }
        else {
            array += std::to_string( lava_a_pos ) + ", ";
        }
    }
    array += "}";
}