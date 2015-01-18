#include <iconv.h>
#include <cstdarg>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils/string.hpp"

namespace instant {
    namespace Utils {

        std::string String::Trim(const std::string & base,
                                 const std::string & char_set) {
            if (char_set.empty()) {
                return base;
            }

            std::string::size_type find_forward_pos =
                base.find_first_not_of(char_set);
             std::string::size_type find_reverse_pos =
                base.find_last_not_of(char_set);

            if (find_forward_pos == std::string::npos) {
                find_forward_pos = 0;
            }

            if (find_reverse_pos == std::string::npos) {
                find_forward_pos = base.size();
            }

            if (find_forward_pos == 0 && find_reverse_pos == base.size()) {
                return base;
            }

            return base.substr(find_forward_pos,
                               find_reverse_pos - find_forward_pos + 1);
        }

        std::string String::FTrim(const std::string & base,
                                  const std::string & char_set) {
            if (char_set.empty()) {
                return base;
            }

            std::string::size_type find_forward_pos =
                base.find_first_not_of(char_set);

            if (find_forward_pos == std::string::npos) {
                return base;
            }
            return base.substr(find_forward_pos);
        }

        std::string String::RTrim(const std::string & base,
                                  const std::string & char_set) {
            if (char_set.empty()) {
                return base;
            }

            std::string::size_type find_reverse_pos =
                base.find_last_not_of(char_set);
            if (find_reverse_pos == std::string::npos) {
                return base;
            }
            return base.substr(0, find_reverse_pos + 1);
        }


        std::string String::TrimWhitespace(const std::string & base) {
            std::vector < std::string > char_list = Splits(base);
            return Join(char_list, "");
        }

        std::vector < std::string > String::Split(const std::string & base,
                                                  const std::
                                                  string & token) {
            std::vector < std::string > split_list;

            if (token.empty()) {
                split_list.insert(split_list.end(), base);
                return split_list;
            }

            std::string::size_type split_pivot = 0;
            std::string::size_type split_pivot_size = token.length();
            std::string::size_type split_delim_pos =
                base.find(token, split_pivot);

            while (split_delim_pos != std::string::npos) {
                split_list.insert(split_list.end(),
                                  base.substr(split_pivot,
                                              split_delim_pos -
                                              split_pivot));
                split_pivot = split_delim_pos + split_pivot_size;
                split_delim_pos = base.find(token, split_pivot);
            }

            if (0 == split_pivot) {
                split_list.insert(split_list.end(), base);
            } else {
                split_list.insert(split_list.end(),
                                  base.substr(split_pivot));
            }

            return split_list;
        }

        std::vector < std::string >
            String::Splits(const std::string & base,
                           const std::string & char_set) {
            std::vector < std::string > split_list;

            if (char_set.empty()) {
                split_list.insert(split_list.end(), base);
                return split_list;
            }

            std::string::size_type lastPos =
                base.find_first_not_of(char_set, 0);
            std::string::size_type pos =
                base.find_first_of(char_set, lastPos);

            while (std::string::npos != pos
                   || std::string::npos != lastPos) {
                split_list.push_back(base.substr(lastPos, pos - lastPos));
                lastPos = base.find_first_not_of(char_set, pos);
                pos = base.find_first_of(char_set, lastPos);
            }

            return split_list;
        }

        std::vector < int >String::ISplit(const std::string & base,
                                          const std::string & token) {
            std::vector < std::string > values = Split(base, token);
            std::vector < int >result;

            std::vector < std::string >::iterator iter = values.begin();
            std::vector < int >results;
            for (; iter != values.end(); ++iter) {
                results.push_back(atoi((*iter).c_str()));
            }
            return results;
        }

        std::vector < float >String::FSplit(const std::string & base,
                                            const std::string & token) {
            std::vector < std::string > values = Split(base, token);
            std::vector < float >result;

            std::vector < std::string >::iterator iter = values.begin();

            std::vector < float >results;
            for (; iter != values.end(); ++iter) {
                results.push_back(atoi((*iter).c_str()));
            }
            return results;
        }

        std::string String::Format(const char *fmt,...) {
            std::string result;
            if (NULL == fmt) {
                return result;
            }

            va_list vl;

            va_start(vl, fmt);
            int need_size = vsnprintf(NULL, 0, fmt, vl);
            char *buffer = new char[need_size + 1];
            va_end(vl);

            va_start(vl, fmt);
            vsprintf(buffer, fmt, vl);
            va_end(vl);

            result = buffer;

            delete[]buffer;

            return result;
        }

        std::string String::Join(const std::vector < std::string > &base,
                                 const std::string & token) {
            std::stringstream ss;
            for (unsigned int index = 0; index < base.size(); ++index) {
                if (index != base.size() - 1)
                    ss << base[index] << token;
                else
                    ss << base[index];
            }
            return ss.str();
        }

        std::string String::Join(std::list < std::string > &base,
                                 const std::string & token) {
            std::stringstream ss;
            std::list < std::string >::iterator itr = base.begin();
            for (unsigned int index = 0; itr != base.end(); ++index, ++itr) {
                if (index != base.size() - 1)
                    ss << *itr << token;
                else
                    ss << *itr;
            }
            return ss.str();
        }

        std::string String::UpperString(const std::string & base) {
            std::string trans_data = base;
            std::transform(trans_data.begin(), trans_data.end(),
                           trans_data.begin(),::toupper);
            return trans_data;
        }

        std::string String::LowerString(const std::string & base) {
            std::string trans_data = base;
            std::transform(trans_data.begin(), trans_data.end(),
                           trans_data.begin(),::tolower);
            return trans_data;
        }

        bool String::IsDigit(const std::string & base,
                             std::locale const &loc) {
            bool digit = true;
            for (unsigned i = 0; i < base.size(); ++i) {
                digit &= std::isdigit(base[i], loc);
            }
            return digit;
        }

        bool String::ToBool(const std::string & base) {
            std::string value = LowerString(base);
            if (std::string::npos == value.find_first_not_of("0123456789")) {
                if (value == "0" or value.empty())
                    return false;
                else
                    return true;
            } else {
                if (value == "true")
                    return true;
                else
                    return false;
            }
        }

        bool String::ToInt(const std::string & base, int &number) {
            std::istringstream str(base);
            if (str >> number)
                return true;
            else
                return false;
        }

        std::string String::Encode(const std::string & base,
                                   const char *from, const char *to) {
            char in_buf[base.size()];
            char out_buf[base.size() * 2];
            size_t in_size, out_size;

            sprintf(in_buf, "%s", base.c_str());
            memset(out_buf, '\0', base.size() * 2);

            char *input_buf_ptr = in_buf;
            char *output_buf_ptr = out_buf;

            in_size = base.size();
            out_size = sizeof(out_buf);

            iconv_t it = iconv_open(to, from);
            iconv(it, &input_buf_ptr, &in_size, &output_buf_ptr,
                  &out_size);
            iconv_close(it);

            return std::string(out_buf);
        }

        std::string String::Replace(const std::string & base,
                                    const std::string & orig,
                                    const std::string & change) {
            std::vector < std::string > str_list = Split(base, orig);
            return Join(str_list, change);
        }

        std::string String::Substitute(const std::string & templateString,
                                       const std::map < std::string, std::string > &params) {
            std::string result = templateString;

            std::map < std::string, std::string >::const_iterator iter;
            for (iter = params.begin(); iter != params.end(); iter++) {
                std::string key = "${" + iter->first + "}";
                std::string value = iter->second;
                result = Replace(result, key, value);
            }

            return result;
        }

        std::map < std::string, std::string > String::ParseOptions(const std::string & query_string) {
            std::map < std::string, std::string > options;

            std::vector < std::string > params = Split(query_string, "&");
            for (unsigned int i = 0; i < params.size(); i++) {
                std::vector < std::string > key_value =
                    Split(params[i], "=");
                if (key_value.size() == 2) {
                    options[key_value[0]] = key_value[1];
                }
            }

            return options;
        }

        std::string String::DecodeURL(const std::string & url) {
            std::string out;
            out.clear();
            out.reserve(url.size());
            for (std::size_t i = 0; i < url.size(); ++i) {
                if (url[i] == '%') {
                    if (i + 3 <= url.size()) {
                        int value = 0;
                        std::istringstream is(url.substr(i + 1, 2));
                        if (is >> std::hex >> value) {
                            out += static_cast < char >(value);
                            i += 2;
                        } else {
                            return std::string();
                        }
                    } else {
                        return std::string();
                    }
                } else if (url[i] == '+') {
                    out += ' ';
                } else {
                    out += url[i];
                }
            }
            return out;
        }

        std::string String::EncodeURL(const std::string & url) {
            std::string escaped = "";
            int max = url.length();
            for (int i = 0; i < max; i++) {
                if ((48 <= url[i] && url[i] <= 57) ||   //0-9
                    (65 <= url[i] && url[i] <= 90) ||   //abc...xyz
                    (97 <= url[i] && url[i] <= 122) ||  //ABC...XYZ
                    (url[i] == '~' || url[i] == '!' || url[i] == '*'
                     || url[i] == '(' || url[i] == ')' || url[i] == '\'')
                    ) {
                    escaped.append(&url[i], 1);
                } else {
                    escaped.append("%");
                    std::string temp = char2hex(url[i]);        //converts char 255 to string "ff"
                    std::transform(temp.begin(), temp.end(), temp.begin(),::toupper);   // to  upper case
                    escaped.append(temp);
                }
            }
            return escaped;
        }

        std::string String::char2hex(char dec) {
            char dig1 = (dec & 0xF0) >> 4;
            char dig2 = (dec & 0x0F);
            if (0 <= dig1 && dig1 <= 9)
                dig1 += 48;     //0,48inascii
            if (10 <= dig1 && dig1 <= 15)
                dig1 += 97 - 10;        //a,97inascii
            if (0 <= dig2 && dig2 <= 9)
                dig2 += 48;
            if (10 <= dig2 && dig2 <= 15)
                dig2 += 97 - 10;

            std::string r;
            r.append(&dig1, 1);
            r.append(&dig2, 1);
            return r;
        }

    };
};
