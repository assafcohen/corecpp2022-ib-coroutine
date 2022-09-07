
#include <fmt/core.h>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include "FileSender.hpp"

using namespace corecpp2022;
using boost::asio::ip::tcp;

void session(tcp::socket sock)
{
  try
  {
    char fileName[256];
    auto bytesRead =
        sock.read_some(boost::asio::buffer(fileName, sizeof fileName));
    FileSender fileSender(sock);
    fileSender.sendFileSize(std::string_view(fileName, bytesRead));
  }
  catch (std::exception& e)
  {
    fmt::print("Exception in thread: {}\n", e.what());
  }
}

[[noreturn]] void server(boost::asio::io_context& io_context, unsigned short port)
{
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    std::thread(session, acceptor.accept()).detach();
  }
}

std::int32_t main() noexcept
{
  try
  {
    boost::asio::io_context ioContext;
    server(ioContext, 2022);
  }
  catch (std::exception& e)
  {
    fmt::print("Exception: {}\n", e.what());
  }
  return 0;
}