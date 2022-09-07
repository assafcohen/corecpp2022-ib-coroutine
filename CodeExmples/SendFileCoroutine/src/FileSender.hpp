#pragma once

#include <filesystem>
#include <boost/asio.hpp>

namespace corecpp2022
{
class FileSender
{
public:
  explicit FileSender(boost::asio::ip::tcp::socket&& socket) :
      mStream(std::move(socket))
  {
  }

  boost::asio::awaitable<boost::system::error_code> sendFileSize(
      const std::filesystem::path& filePath);
  boost::asio::awaitable<boost::system::error_code> sendFile(
      const std::filesystem::path& filePath);

private:
  boost::asio::ip::tcp::socket mStream;
};
} // namespace corecpp2022