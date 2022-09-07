#include <fmt/core.h>
#include <boost/asio.hpp>
#include <boost/asio/experimental/as_tuple.hpp>
#include <memory>
#include <utility>
#include "FileSender.hpp"

using namespace corecpp2022;

using boost::asio::detached;
using boost::asio::awaitable;
using boost::asio::buffer;
using boost::asio::co_spawn;
using boost::asio::ip::tcp;
using boost::asio::steady_timer;
using boost::asio::use_awaitable;
using boost::asio::experimental::as_tuple;
namespace this_coro = boost::asio::this_coro;

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
                boost::asio::buffer(fileName, sizeof fileName),
                use_awaitable);
            FileSender fileSender(std::move(sock));
            co_await fileSender.sendFileSize(
                std::string_view(fileName, bytesRead));
          },
          detached);
    }
    else
    {
      fmt::print("Accept failed: {}\n", e.message());
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
    boost::asio::io_context ioContext;

    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 2022));
    co_spawn(ioContext, server(acceptor), detached);

    ioContext.run();
  }
  catch (std::exception& e)
  {
    fmt::print("Exception: {}\n", e.what());
  }

  return 0;
}