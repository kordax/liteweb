#ifndef FS_H
#define FS_H

#include <boost/filesystem/operations.hpp>

namespace lt
{
  namespace filesystem
  {
    std::string getBinaryFromEnv(const std::string &binary);
    std::string getEnvVar(const std::string &envVar);
    bool isFile(const std::string &path);
    bool isDir(const std::string &path);
  }
}

#endif // FS_H

