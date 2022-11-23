#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <sstream>
#include <atomic>
#include <functional>

#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/process/async.hpp>

namespace ba = boost::asio;
namespace bp = boost::process;

#include "app.hpp"
#include "Fl_Flow.hpp"

class Clangd_Server
{
  public:
    bp::ipstream out;
    bp::opstream in;
    std::string line_out;

    std::atomic_bool running = true;

    void launch()
    {
        bp::child c("clangd", bp::std_err > out, bp::std_in < in);
        while (c.running())
        {
            std::getline(out, line_out);
            std::cout << line_out << std::endl;
        }
        running = false;
    };

    template <typename T>
    bp::opstream& operator<<(T msg)
    {
        in << msg << std::endl;
        return in;
    }

    bool run() { return running; }
};

int main(int argc, char** argv)
{
    // fc::App app(800, 600);

    Clangd_Server server;

    std::thread cth(&Clangd_Server::launch, &server);
    std::string line;

    while (server.run())
    {
        std::getline(std::cin, line);
        server << line;
    }

    cth.join();

    return 0;
}