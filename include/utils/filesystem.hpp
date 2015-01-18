#ifndef __UTILS_FILESYSTEM_HPP__
#define __UTILS_FILESYSTEM_HPP__

#include <string>
#include <vector>

namespace instant {
    namespace Utils {
        class Filesystem {
          public:

            /// \brief 주어진 path에 존재하는 file의 내용을 읽어들여서 반환한다.
            /// \param[in] file_path 내용을 읽어들일 file_path
            /// \return    읽어들인 파일의 내용
            static std::string GetFileValue(const std::string & file_path);

            /// \brief 주어진 string의 내용을 file_path에 있는 file에 담는다. 없으면 생성
            /// \param[in] file_path 내용을 쓸 혹은 만들 file의 위치
            /// \param[in] file_value file안에 담길 내용
            static void SetFileValue(const std::string & file_path,
                                     const std::string & file_value);

            /// \brief 주어진 parent directory오 child directory를 합쳐서 하나의 directory를 만들어준다.
            /// \param[in] parent parent directory
            /// \param[in] child chidl directory
            /// \return 하나로 합쳐진 directory ( ex parent/child )
            static std::string JoinPath(const std::string & parent,
                                        const std::string & child);

            /// \brief 주어진 directory내부에 존재하는 file들의 이름을 반환한다. ( directory, file 포함 ".", ".." 미포함 )
            /// \param[in] directory  file_list를 추출할 directory
            /// \param[out] file_list 찾아낸 directory내부에 있는 file의 list
            /// \param[in] file name의 full path여부
            /// \return traverse 가능 여부
            static bool GetFileNames(const std::string & directory,
                                     std::vector < std::string >
                                     &file_list, bool full_path = true);

            /// \brief 주어진 path가 directory인지 구분한다.
            /// \param[in] path directory여부를 확인하고 싶은 path
            /// \return 디렉토리여부
            static bool IsDirectory(const std::string & path);

            /// \brief 주어진 path가 제대로된 File 인지 구분한다.
            /// \param[in] path file_path
            /// \return 파일체크 여부. 
            static bool IsFile(const std::string & path);

            static int MakeDirectory(const std::string & path);

            /// \brief 주어진 path의 directory가 있는지확인하고 없으면 생성한다.
            /// \param[in] path directory 확인하고 싶은 path
            /// \return 디렉토리의 생성 여부
            static bool EnsureDirectory(const std::string & path);

            /// \brief 주어진 path의 디렉토리 혹은 파일을 삭제한다.
            /// \note 하위에 파일 혹은 디렉토리가 있으면 recurisive하게 삭제한다. ( rm -r )
            /// \param[in] path 삭제하고싶은 directory(file) path
            /// \return 삭제여부
            static bool RemoveDirectory(const std::string & path);

            /// \brief 주어진 path의 디렉토리 이름을 추출한다.
            /// \return dirname
            static std::string DirName(const std::string & path);

            /// \brief 주어진 path의 파일이름 추출한다.
            /// \return basename 
            static std::string BaseName(const std::string & path);

            /// \brief 주어진 path의 절대경로를 돌려준다.
            /// \return abspath
            static std::string AbsPath(const std::string & path);

            /// \brief 파일의 최근 수정시간을 반환한다.
            /// \param[in] path
            /// \param[out] last_modified_time
            /// \return 성공 여부
            static bool GetFileLastModifiedTime(const std::string & path,
                                                double
                                                &last_modified_time);

            /// \brief 디렉토리의 이름을 변경한다.
            /// \param[in] current_path
            /// \param[in] next_path
            /// return 이름변경 성공여부
            static bool RenamePath(const std::string & old_path,
                                   const std::string & new_path);

            /// \brief access 가능 여부 확인
            /// \param[in] path
            /// \param[in] mode
            /// \return access 가능 여부
            static bool CanAccess(const std::string & path, int modeo);

            /// \brief current path 현재 디렉토리 위치 출력
            /// \return current path
            static std::string GetCurrentPath();
        };

    };
};

#endif //__UTILS_FILESYSTEM_HPP__
