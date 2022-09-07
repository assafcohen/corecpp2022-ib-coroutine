
#include <fmt/core.h>
#include <boost/asio.hpp>
#include <memory>
#include <utility>
#include "FileSender.hpp"

using namespace corecpp2022;
using boost::asio::ip::tcp;

class Server
{
public:
  Server(boost::asio::io_context& ioContext, std::uint16_t port) :
      mAcceptor(ioContext, tcp::endpoint(tcp::v4(), port))
  {
    doAccept();
  }

private:
  void doAccept()
  {
    mAcceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<FileSender>(std::move(socket))->start();
          }
          doAccept();
        });
  }
  tcp::acceptor mAcceptor;
};

std::int32_t main() noexcept
{
  try
  {
    boost::asio::io_context ioContext;

    Server s(ioContext, 2022);

    ioContext.run();
  }
  catch (std::exception& e)
  {
    fmt::print("Exception: {}\n", e.what());
  }
  return 0;
}