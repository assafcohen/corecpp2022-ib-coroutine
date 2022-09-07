#pragma once

#include <filesystem>
#include <asio.hpp>

namespace corecpp2022
{
class FileSender
{
public:
  explicit FileSender(asio::ip::tcp::socket&& socket) :
      mStream(std::move(socket))
  {
  }

  asio::awaitable<std::error_code> sendFileSize(
      const std::filesystem::path& filePath);
  asio::awaitable<std::error_code> sendFile(
      const std::filesystem::path& filePath);

private:
  asio::ip::tcp::socket mStream;
};
} // namespace corecpp2022