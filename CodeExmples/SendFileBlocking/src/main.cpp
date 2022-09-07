#include <iostream>
#include <asio.hpp>
#include "FileSender.hpp"

using namespace corecpp2022;
using asio::ip::tcp;

void session(tcp::socket sock)
{
  try
  {
    char fileName[256];
    auto bytesRead = sock.read_some(asio::buffer(fileName, sizeof fileName));
    FileSender fileSender(sock);
    fileSender.sendFileSize(std::string_view(fileName, bytesRead));
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

[[noreturn]] void server(asio::io_context& io_context, unsigned short port)
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
    asio::io_context ioContext;
    server(ioContext, 2022);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception : " << e.what() << "\n";
  }
  return 0;
}