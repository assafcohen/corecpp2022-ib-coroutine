#include <iostream>
#include <memory>
#include <utility>
#include <asio.hpp>
#include <asio/experimental/as_tuple.hpp>
#include "FileSender.hpp"

using namespace corecpp2022;

using asio::detached;
using asio::awaitable;
using asio::buffer;
using asio::co_spawn;
using asio::ip::tcp;
using asio::steady_timer;
using asio::use_awaitable;
using asio::experimental::as_tuple;
namespace this_coro = asio::this_coro;

using namespace std::literals::chrono_literals;

awaitable<void> server(tcp::acceptor& acceptor)
{
  for (;;)
  {
    auto [e, sock] = co_await acceptor.async_accept(as_tuple(use_awaitable));
    if (!e)
    {
      auto ex = sock.get_executor();
      co_spawn(
          ex,
          [sock = std::move(sock)]() mutable -> awaitable<void>
          {
            char fileName[256];
            auto bytesRead = co_await sock.async_read_some(
                asio::buffer(fileName, sizeof fileName),
                use_awaitable);
            FileSender fileSender(std::move(sock));
            co_await fileSender.sendFileSize(
                std::string_view(fileName, bytesRead));
          },
          detached);
    }
    else
    {
      std::cerr << "Exception in thread: " << e.message() << "\n";
      steady_timer timer(co_await this_coro::executor);
      timer.expires_after(100ms);
      co_await timer.async_wait(use_awaitable);
    }
  }
}

std::int32_t main() noexcept
{
  try
  {
    asio::io_context ioContext;

    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 2022));
    co_spawn(ioContext, server(acceptor), detached);

    ioContext.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}