
#include "FileSender.hpp"

namespace corecpp2022
{
using std::error_code;
namespace fs = std::filesystem;
using fs::path;
using std::size_t;

static constexpr size_t buffSize = 1024 * 64;

void FileSender::sendFileSize(const path& filePath)
{
  const auto fileSize = static_cast<size_t>(fs::file_size(filePath));
  asio::write(mStream, asio::buffer(&fileSize, sizeof(fileSize)));
  return sendFile(filePath);
}

void FileSender::sendFile(const path& filePath)
{
  const auto fileSize = static_cast<size_t>(fs::file_size(filePath));
  auto buff = std::make_unique<std::byte[]>(buffSize);
  asio::stream_file file(mStream.get_executor(),
                         filePath.string(),
                         asio::file_base::read_only);
  size_t totalreadBytes = 0, totalsentBytes = 0, readBytes = 0;
  while (totalreadBytes < fileSize)
  {
    totalreadBytes += readBytes =
        file.read_some(asio::buffer(buff.get(), buffSize));
    totalsentBytes += asio::write(mStream, asio::buffer(buff.get(), readBytes));
  }
}
} // namespace corecpp2022