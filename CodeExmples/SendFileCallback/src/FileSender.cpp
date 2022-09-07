
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

void FileSender::start()
{
  receiveFilePath();
}
void FileSender::receiveFilePath()
{
  mBuffer = std::make_unique<std::byte[]>(buffSize);

  auto self(shared_from_this());
  mStream.async_read_some(
      asio::buffer(reinterpret_cast<char*>(mBuffer.get()), buffSize),

      [&, this, self](const error_code& ec, size_t opReadBytes)
      {
        if (ec)
        {
          throw std::exception(ec.what().c_str(), ec.value());
        }
        mFilePath.assign(
            std::string_view(reinterpret_cast<char*>(mBuffer.get()),
                             opReadBytes));
        sendFileSize();
      });
}

void FileSender::sendFileSize()
{
  mFileSize = static_cast<std::size_t>(fs::file_size(mFilePath));
  auto self(shared_from_this());
  asio::async_write(mStream,
                    asio::buffer(&mFileSize, sizeof(mFileSize)),
                    [this, self](error_code ec, size_t)
                    {
                      if (ec)
                      {
                        throw std::exception(ec.what().c_str(), ec.value());                       
                      }
                      else
                      {
                        return sendFile();
                      }
                    });
}

void FileSender::sendFile()
{
  mStreamFile.open(mFilePath.string(), asio::file_base::read_only);
  readFromFile();
}

void FileSender::readFromFile()
{
  auto self(shared_from_this());
  mStreamFile.async_read_some(
      asio::buffer(mBuffer.get(), buffSize),
      [&, this, self](const boost::system::error_code& ec, size_t opReadBytes)
      {
        if (ec)
        {
          throw std::exception(ec.what().c_str(), ec.value());
        }
        mReadBytes += opReadBytes;
        sendReadData(opReadBytes);
      });
}

void FileSender::sendReadData(size_t dataSize)
{
  auto self(shared_from_this());
  asio::async_write(
      mStream,
      asio::buffer(mBuffer.get(), dataSize),
      [this, self](const boost::system::error_code& ec, size_t opSentBytes)
      {
        if (ec)
        {
          throw std::exception(ec.what().c_str(), ec.value());
        }
        mSentBytes += opSentBytes;        
        if (mReadBytes < mFileSize)
        {
          readFromFile();
        }
      });
}
} // namespace corecpp2022