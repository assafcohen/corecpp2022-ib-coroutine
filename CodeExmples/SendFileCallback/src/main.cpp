#include <iostream>
#include <memory>
#include <asio.hpp>
#include <utility>
#include "FileSender.hpp"

using namespace corecpp2022;
using asio::ip::tcp;

class Server
{
public:
  Server(asio::io_context& ioContext, std::uint16_t port) :
      mAcceptor(ioContext, tcp::endpoint(tcp::v4(), port))
  {
    doAccept();
  }

private:
  void doAccept()
  {
    mAcceptor.async_accept(
        [this](std::error_code ec, tcp::socket socket)
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
    asio::io_context ioContext;

    Server s(ioContext, 2022);

    ioContext.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}