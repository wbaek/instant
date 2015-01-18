#ifndef __WBAEK_NETWORK_H__
#define __WBAEK_NETWORK_H__

#include <sstream>
#include <string>
#include <map>

#include <curl/curl.h>
#include <utils/string.hpp>

namespace instant {
    namespace Utils {
	class CURLexception {
		private:
			static std::map<int, std::string> createStatusString();
			static std::map<int, std::string> HTTP_STATUS_STRING;

		protected:
			int code;
			std::string description;

		public:
			CURLexception(const int code, const std::string& description="") {
				this->code = code;
				this->description = description;
			}

			const int GetCode() const {
				return this->code;
			}
			const std::string& what() const {
				if(description.size() == 0) {
					return this->HTTP_STATUS_STRING[this->code];
				}
				return this->description;
			}
	};

	size_t dw_callback(void* buf, size_t size, size_t nmemb, void* userp);
	class Network {
		public:
			/// \brief HTTP request를 요청하는 함수
			/// \param[in] url HTTP reuqest를 요청하는 url
            /// \param[in] headers HTTP custom header
			/// \param[in] timeout timeout을 지정 (초단위) 0을 넣으면 무한 대기
			/// \return http response body
			/// \exception CURLexception Socket/HTTP error가 발생하면 CURLexception에 code와 description을 담아 예외를 던진다. (try, catch로 잡아 주지 않으면 예외 발생시 core dump됨)
			static std::string HttpRequest(const std::string& url,
                                           const long timeout=10, /*seconds*/
                                           const bool useDefaultHeader=false,
                                           const std::map<std::string, std::string>& headers = GetDefaultMap()
                                           ) {
				std::ostringstream os;
				CURLcode code(CURLE_FAILED_INIT);
				CURL* curl = curl_easy_init();
				long http_code = 0;

				if(curl) {
                    std::vector<std::string> headerStrings = GetHeaderString(headers, url, true);
                    struct curl_slist *chunk = NULL;
                    for(unsigned int i=0; i<headerStrings.size(); i++) {
                        chunk = curl_slist_append(chunk, headerStrings[i].c_str());
                    }
                    

					if(CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *dw_callback))
					&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
					&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
					&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
					&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
					&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1))
                    && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk))
					&& CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, url.c_str()))
                    ) {
						code = curl_easy_perform(curl);
					}
					curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
					curl_easy_cleanup(curl);
                    curl_slist_free_all(chunk);

					if(code != CURLE_OK) { // check network error
						throw CURLexception( code, std::string(curl_easy_strerror(code)) );
					}
					if(http_code != 200) { // check HTTP code error
						throw CURLexception( (int)http_code );
					}

				}
				return os.str();
			}

            static std::map<std::string, std::string> GetDefaultMap() {
                std::map<std::string, std::string> m;
                return m;
            }
        private:
            static std::vector<std::string> GetHeaderString(const std::map<std::string, std::string>& headers,
                                                            const std::string& url="",
                                                            const bool useDefaultHeader=false,
                                                            const bool autoReferer=false) {
                std::vector<std::string> headerStrings; 
                typedef std::map<std::string, std::string>::const_iterator headerIterator;
                for(headerIterator iter = headers.begin(); iter != headers.end(); iter++) {
                    if( iter->first.size() == 0 || iter->second.size() == 0 )
                        continue;
                    std::string header = iter->first + ": " + iter->second;
                    headerStrings.push_back(header);
                }
                
                // set deafault header
                if(useDefaultHeader) {
                    headerStrings.push_back("User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_5) AppleWebKit/536.26.17 ( KHTML, like Gecko) Version/6.0.2 Safari/536.26.17");
                }

                // set auto referer
                if(autoReferer) {
                    std::vector<std::string> urlList = instant::Utils::String::Split(url, "/");
                    urlList.resize(3);
                    std::string autoReferer = instant::Utils::String::Join(urlList, "/");
                    headerStrings.push_back(autoReferer);
                }

                return headerStrings;
            }
	};

}; };

#endif // __WBAEK_NETWORK_H__

