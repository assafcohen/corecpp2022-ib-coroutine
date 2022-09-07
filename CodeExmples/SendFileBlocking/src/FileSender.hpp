
#pragma once

#include <filesystem>
#include <boost/asio.hpp>

namespace corecpp2022
{
class FileSender
{
public:
  explicit FileSender(boost::asio::ip::tcp::socket& socket) :
      mStream(socket) { }

  void sendFileSize(const std::filesystem::path& filePath);

  void sendFile(const std::filesystem::path& filePath);

private:
  boost::asio::ip::tcp::socket& mStream;
};
} // namespace corecpp2022