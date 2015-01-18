#include "utils/filesystem.hpp"

#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <list>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <stdlib.h>

namespace instant {
    namespace Utils {

        std::string Filesystem::GetFileValue(const std::string & file_path) {
            std::ifstream file;
            file.open(file_path.c_str());

            file.seekg(0, file.end);
            int length = file.tellg();
            file.seekg(0, file.beg);

            char* buffer = new char[length];
            file.read(buffer, length);

            file.close();
            std::string file_value(buffer, buffer+length);

            if( buffer )
                delete[] buffer;
            buffer = NULL;
            return file_value;
        }

        void Filesystem::SetFileValue(const std::string & file_path,
                                      const std::string & file_value) {
            std::ofstream file;
            file.exceptions(std::ofstream::failbit);
            file.open(file_path.c_str());
            file << file_value;
            file.close();
        }

        std::string Filesystem::JoinPath(const std::string & parent,
                                         const std::string & child) {
            char last = (parent.size() > 0) ? *parent.rbegin() : 0;
            char first = (child.size() > 0) ? *child.begin() : 0;

            if (last != 0) {
                if (last == '/' && first == '/')
                    return parent + child.substr(1);
                else if (last != '/' && first != '/')
                    return parent + '/' + child;
                else
                    return parent + child;
            }
            return child;
        }

        bool Filesystem::IsDirectory(const std::string & path) {
            struct stat s;
            if (stat(path.c_str(), &s) == -1 && errno == ENOENT) {
                return false;
            } else {
                return S_ISDIR(s.st_mode);
            }
        }

        bool Filesystem::IsFile(const std::string & path) {
            struct stat s;
            if (stat(path.c_str(), &s) == -1 && errno == ENOENT) {
                return false;
            } else {
                return S_ISREG(s.st_mode);
            }
        }

        int Filesystem::MakeDirectory(const std::string & spath) {
            const char *path = spath.c_str();
            const char *p = strchr(path, '/');
            while (p) {
                int len = p - path;
                if (len > 0) {
                    std::string directory(path, len);
                    mkdir(directory.c_str(), 0755);
                }
                p = strchr(p + 1, '/');
            }
            return mkdir(path, 0755);
        }

        bool Filesystem::EnsureDirectory(const std::string & path) {
            struct stat s;
            return (stat(path.c_str(), &s) == -1
                    && errno == ENOENT) ? (MakeDirectory(path) !=
                                           -1) : S_ISDIR(s.st_mode);
        }

        bool Filesystem::GetFileNames(const std::string & directory,
                                      std::vector < std::string >
                                      &file_list, bool full_path) {
            std::string str_path(directory);
            if (str_path.size() == 0)
                return false;

            if (str_path[str_path.length() - 1] != '/')
                str_path += "/";
            DIR *pdir = NULL;
            pdir = opendir(str_path.c_str());
            if (pdir == NULL) {
                return false;
            }

            struct dirent *pent = NULL;
            std::string file;
            pent = readdir(pdir);
            while (pent) {
                if (strcmp(pent->d_name, ".") !=
                    0 and strcmp(pent->d_name, "..") != 0) {
                    if (full_path)
                        file = str_path + pent->d_name;
                    else
                        file = pent->d_name;
                    file_list.push_back(file);
                }
                pent = readdir(pdir);
            }
            closedir(pdir);
            return true;
        }

        bool Filesystem::RemoveDirectory(const std::string & path) {
            std::string str_path(path);

            if (str_path[str_path.length() - 1] != '/')
                str_path += "/";
            DIR *pdir = NULL;
            pdir = opendir(str_path.c_str());

            if (pdir == NULL) {
                return false;
            }
            struct dirent *pent = NULL;
            std::string file;
            pent = readdir(pdir);
            while (pent) {
                if (strcmp(pent->d_name, ".") !=
                    0 and strcmp(pent->d_name, "..") != 0) {
                    file = str_path + pent->d_name;
                    if (IsDirectory(file) == true) {
                        RemoveDirectory(file);
                    } else {
                        remove(file.c_str());
                    }
                }
                pent = readdir(pdir);
            }

            closedir(pdir);
            if (!rmdir(str_path.c_str()))
                return false;
            return true;
        }

        std::string Filesystem::DirName(const std::string & path) {
            std::string dirname = "";
            std::string::size_type idx = path.rfind("/");
            if (idx != std::string::npos) {
                dirname = path.substr(0, idx);
            }

            return dirname;
        }

        std::string Filesystem::BaseName(const std::string & path) {
            std::string basename = path;
            std::string::size_type end =
                (path[path.size() - 1] ==
                 '/' ? path.size() - 2 : path.size() - 1);
            std::string::size_type idx = path.rfind("/", end);

            if (idx != std::string::npos) {
                basename = path.substr(idx + 1, end - idx);
            }

            return basename;
        }

        std::string Filesystem::AbsPath(const std::string & path) {
            char *abspath = realpath(path.c_str(), NULL);
            std::string path_ = abspath;
            free(abspath);
            return path_;
        }

        bool Filesystem::GetFileLastModifiedTime(const std::string & path,
                                                 double
                                                 &last_modified_time) {
            struct stat s;
            if (stat(path.c_str(), &s) == 0) {
                last_modified_time = s.st_mtime;

                return true;
            }

            return false;
        }

        bool Filesystem::RenamePath(const std::string & old_path,
                                    const std::string & new_path) {
            if (rename(old_path.c_str(), new_path.c_str()) == -1)
                return false;
            return true;
        }

        bool Filesystem::CanAccess(const std::string & path, int mode) {
            int ret;

            ret = access(path.c_str(), mode);
            if (ret == 0)
                return true;

            return false;
        }

        std::string Filesystem::GetCurrentPath() {
            char path[1024];
            getcwd(path, sizeof(path));
            return std::string(path) + "/";
        }
    };
};
