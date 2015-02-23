#include "helpers/fs.h"
#include <boost/algorithm/string.hpp>

bool lt::filesystem::isFile(const std::string &path)
{
    if (boost::filesystem::exists(path) && boost::filesystem::is_regular_file(path)) {
        return true;
    }

    return false;
}

std::string lt::filesystem::getBinaryFromEnv(const std::string &binaryName)
{
    char* envPath = getenv(binaryName.c_str());

    std::vector<std::string> splittedPaths;
    boost::split(splittedPaths, envPath, boost::is_any_of(":"));

    for (const std::string &path : splittedPaths) {
        if (isFile(path + "/" + binaryName)) {
            return path + "/" + binaryName;
        }
    }

    return std::string("");
}

std::string lt::filesystem::getEnvVar(const std::string &envVar)
{
    char* envPath = getenv(envVar.c_str());

    return std::string(envPath);
}
