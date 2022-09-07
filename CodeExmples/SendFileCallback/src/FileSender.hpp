
#pragma once

#include <filesystem>
#include <asio.hpp>

namespace corecpp2022
{
class FileSender : public std::enable_shared_from_this<FileSender>
{
public:
  explicit FileSender(asio::ip::tcp::socket&& socket) :
      mStream(std::move(socket)),
      mStreamFile(socket.get_executor())
  {
  }

  void start();

private:
  void receiveFilePath();
  void sendFileSize();
  void sendFile();
  void readFromFile();
  void sendReadData(std::size_t dataSize);

  std::filesystem::path mFilePath;
  asio::ip::tcp::socket mStream;
  asio::stream_file mStreamFile;
  std::unique_ptr<std::byte[]> mBuffer;
  std::size_t mReadBytes = 0;
  std::size_t mSentBytes = 0;
  std::size_t mFileSize = 0;
};
} // namespace corecpp2022