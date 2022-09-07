
#pragma once

#include <filesystem>
#include <asio.hpp>

namespace corecpp2022
{
class FileSender
{
public:
  explicit FileSender(asio::ip::tcp::socket& socket) : mStream(socket) { }

  void sendFileSize(const std::filesystem::path& filePath);

  void sendFile(const std::filesystem::path& filePath);

private:
  asio::ip::tcp::socket& mStream;
};
} // namespace corecpp2022