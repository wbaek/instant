#ifndef __UTILS_STRING_HPP__
#define __UTILS_STRING_HPP__

#include <string>
#include <vector>
#include <list>
#include <locale>
#include <map>
#include <sstream>

namespace instant {
    namespace Utils {
        class String {
          public:
            template < typename T >
            static std::string ToString(const T & value) {
                std::stringstream iostring;
                iostring << value;
                return iostring.str();
            }
            
            template < typename T >
            static bool ToPrimitive(const std::string & valueString,
                                        T & value) {
                std::stringstream iostring;
                iostring << valueString;
                if (iostring >> value)
                    return true;
                else
                    return false;
            }

            /// \brief 주어진 스트링에서 앞뒤에 있는 문자 집합을 제거하는 함수
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] char_set 제거할 문자들의 집합
            /// \return 문자 집합이 제거된 스트링
            static std::string Trim(const std::string & base,
                                        const std::string & char_set =
                                        " \t\v\f\r\n");

            /// \brief 주어진 스트링에서 앞에 있는 문자 집합을 제거하는 함수
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] char_set 제거할 문자들의 집합
            /// \return 문자 집합이 제거된 스트링
            static std::string FTrim(const std::string & base,
                                     const std::string & char_set =
                                     " \t\v\f\r\n");

            /// \brief 주어진 스트링에서 뒤에 있는 문자 집합을 제거하는 함수
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] char_set 제거할 문자들의 집합
            /// \return 문자 집합이 제거된 스트링
            static std::string RTrim(const std::string & base,
                                     const std::string & char_set =
                                     " \t\v\f\r\n");

            /// \brief 주어진 스트링 내에 있는 모든 whitespace를 제거한다.
            /// \param[in] base     함수를 수행할 스트링
            /// \return whitespace가 제거된 스트링
            static std::string TrimWhitespace(const std::string & base);

            /// \brief 주어진 스트링에서 문자열을 기준으로 분리하는 함수. token이 전부들어와야 단절자로 인식한다.
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] token    분리 기준이 되는 문자열
            /// \return 분리된 스트링들
            static std::vector < std::string >
                Split(const std::string & base, const std::string & token =
                      " ");

            /// \brief 주어진 스트링에서 문자들을 기준으로 분리하는 함수 split와 다른점은 각각의 char에 대해서 split가 행해진다.
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] token    분리 기준이 되는 문자들
            /// \return 분리된 스트링들
            static std::vector < std::string >
                Splits(const std::string & base,
                       const std::string & char_set = " \t\v\f\r\n");

            /// \brief 주어진 스트링에서 문자열을 기준으로 정수를 얻는 함수
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] token    분리 기준이 되는 문자열
            /// \return 분리된 정수들
            static std::vector < int >ISplit(const std::string & base,
                                             const std::string & token =
                                             " ");

            /// \brief 주어진 스트링에서 문자열을 기준으로 float 형식 수를 얻는 함수
            /// \param[in] base     함수를 수행할 스트링
            /// \param[in] token    분리 기준이 되는 문자열
            /// \return 분리된 실수들
            static std::vector < float >FSplit(const std::string & base,
                                               const std::string & token =
                                               " ");

            /// \brief format과 그에 대한 인자로 부터 스트링을 생성하는 함수
            /// \param[in] fmt 스트링 생성에 필요한 format
            /// \return format을 통해서 만들어진 스트링
            static std::string Format(const char *fmt, ...);

            /// \brief 주어진 string 의 vector 를 token을 가운데 넣고 합쳐서 하나의 string을 만들어주는 함수
            /// \param[in] base join이 될 vector
            /// \param[in] token join시에 string 사이에 입력될 문자열
            /// \return join이 된 스트링
            static std::string Join(const std::vector < std::string >
                                    &base, const std::string & token =
                                    " ");

            /// \brief 주어진 string 의 list 를 token을 가운데 넣고 합쳐서 하나의 string을 만들어주는 함수
            /// \param[in] base join이 될 list
            /// \param[in] token join시에 string 사이에 입력될 문자열
            /// \return join이 된 스트링
            static std::string Join(std::list < std::string > &base,
                                    const std::string & token = " ");

            /// \brief 주어진 string의 소문자를 대문자로 변환
            /// \param[in] base 변환할 문자열
            /// \return 변환이 완료된 스트링
            static std::string UpperString(const std::string & base);

            /// \brief 주어진 string의 대문자를 소문자로 변환
            /// \param[in] base 변환할 문자열
            /// \return 변환이 완료된 스트링
            static std::string LowerString(const std::string & base);

            /// \brief 문자열이 전부 숫자인지 체크
            /// \param[in] base 
            static bool IsDigit(const std::string & base,
                                std::locale const &loc =
                                std::locale("ko_KR.UTF-8"));

            /// \brief 문자열 True나 False 등을 boolean 값으로 바꿔줌 
            /// \param[in] base 변환할 문자열
            /// \details 
            ///   - 변환에 실패하면 false를 리턴함
            ///   - 대소문자를 구별하지 않음 ( TRUE, true, tRue 등은 모두 true )
            static bool ToBool(const std::string & base);

            /// \brief 문자열을 숫자로 변환 
            /// \param[in] base 변환할 문자열
            /// \param[out] number 변환된 숫자
            /// \details 
            ///   - 변환에 실패하면 false를 리턴함
            static bool ToInt(const std::string & base, int &number);

            /// \brief 문자열의 인코딩을 변환
            /// \param[in] base 변환할 문자열
            /// \param[in] from 디코딩 코덱
            /// \param[in] to 인코딩 코덱
            /// \details 
            ///  - 변환에 실패하면 빈 문자열이 나감 
            static std::string Encode(const std::string & base,
                                      const char *from =
                                      "EUC-KR", const char *to = "UTF-8");

            /// \brief string -> string change
            /// \param[in] base 변환할 문자열을 포함하는 원본 문자열
            /// \param[in] orig 변환할 문자열 
            /// \param[out] change  변환될 문자열 
            static std::string Replace(const std::string & base,
                                       const std::string & orig,
                                       const std::string & change);

            /// \brief python Template substitute와 같은 역할
            /// \param[in] templateString template의 ${KEY}가 대치대는 위치
            /// \param[in] KEY-VALUE의 셋으로 KEY값을 VALUE값으로 대치
            static std::string Substitute(const std::
                                          string & templateString,
                                          const std::map < std::string, std::string > &params);

            /// \brief query_string -> key-value map
            /// \param[in] query_string url query_string
            /// \param[out] key-value map
            /// \return number of keys
            static std::map < std::string, std::string >
                ParseOptions(const std::string & query_string);

            static std::string DecodeURL(const std::string & url);
            static std::string EncodeURL(const std::string & url);
          private:
            static std::string char2hex(char dec);
        };

    };
};

#endif // __UTILS_STRING_HPP__
