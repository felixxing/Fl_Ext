#include <iostream>

#include "app.hpp"

int main(int argc, char** argv)
{
    fc::App app(800, 600);

    return app.run(argc, argv);
}