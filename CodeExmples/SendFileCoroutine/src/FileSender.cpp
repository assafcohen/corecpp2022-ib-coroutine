#include <fmt/core.h>

#include "FileSender.hpp"

namespace corecpp2022
{
using boost::system::error_code;
namespace fs = std::filesystem;
namespace asio = boost::asio;
using fs::path;
using std::size_t;

static constexpr size_t buffSize = 1024 * 64;

asio::awaitable<error_code> FileSender::sendFileSize(const path& filePath)
{  
  const auto fileSize = static_cast<size_t>(fs::file_size(filePath));
  co_await asio::async_write(mStream,asio::buffer(&fileSize, sizeof(fileSize)),asio::use_awaitable);
  co_return co_await sendFile(filePath);
}

asio::awaitable<error_code> FileSender::sendFile(const path& filePath)
{
  const auto fileSize = static_cast<size_t>(fs::file_size(filePath));
  auto buff = std::make_unique<std::byte[]>(buffSize);
  asio::stream_file f(mStream.get_executor(),
                      filePath.string(),
                      asio::file_base::read_only);
  size_t totalreadBytes = 0, totalsentBytes = 0, readBytes = 0, sentBytes = 0;
  while (totalreadBytes < fileSize)
  {
    totalreadBytes += readBytes =
        co_await f.async_read_some(asio::buffer(buff.get(), buffSize),
                                   asio::use_awaitable);
    totalsentBytes += sentBytes =
        co_await asio::async_write(mStream,
                                   asio::buffer(buff.get(), readBytes),
                                   asio::use_awaitable);
  }
  co_return error_code();
}
} // namespace corecpp2022