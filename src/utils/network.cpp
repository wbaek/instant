#include <utils/network.hpp>

namespace instant { namespace Utils {
	std::map<int, std::string> CURLexception::HTTP_STATUS_STRING(CURLexception::createStatusString());
	std::map<int, std::string> CURLexception::createStatusString()
	{
		std::map<int, std::string> HTTP_STATUS_STRING;
		HTTP_STATUS_STRING[100]="Continue";
		HTTP_STATUS_STRING[101]="Switching Protocols";
		HTTP_STATUS_STRING[200]="OK";
		HTTP_STATUS_STRING[201]="Created";
		HTTP_STATUS_STRING[202]="Accepted";
		HTTP_STATUS_STRING[203]="Non-Authoritative Information";
		HTTP_STATUS_STRING[204]="No Content";
		HTTP_STATUS_STRING[205]="Reset Content";
		HTTP_STATUS_STRING[206]="Partial Content";
		HTTP_STATUS_STRING[300]="Multiple Choices";
		HTTP_STATUS_STRING[301]="Moved Permanently";
		HTTP_STATUS_STRING[302]="Found";
		HTTP_STATUS_STRING[303]="See Other";
		HTTP_STATUS_STRING[304]="Not Modified";
		HTTP_STATUS_STRING[305]="Use Proxy";
		HTTP_STATUS_STRING[307]="Temporary Redirect";
		HTTP_STATUS_STRING[400]="Bad Request";
		HTTP_STATUS_STRING[401]="Unauthorized";
		HTTP_STATUS_STRING[402]="Payment Required";
		HTTP_STATUS_STRING[403]="Forbidden";
		HTTP_STATUS_STRING[404]="Not Found";
		HTTP_STATUS_STRING[405]="Method Not Allowed";
		HTTP_STATUS_STRING[406]="Not Acceptable";
		HTTP_STATUS_STRING[407]="Proxy Authentication Required";
		HTTP_STATUS_STRING[408]="Request Timeout";
		HTTP_STATUS_STRING[409]="Conflict";
		HTTP_STATUS_STRING[410]="Gone";
		HTTP_STATUS_STRING[411]="Length Required";
		HTTP_STATUS_STRING[412]="Precondition Failed";
		HTTP_STATUS_STRING[413]="Request Entity Too Large";
		HTTP_STATUS_STRING[414]="Request-URI Too Long";
		HTTP_STATUS_STRING[415]="Unsupported Media Type";
		HTTP_STATUS_STRING[416]="Requested Range Not Satisfiable";
		HTTP_STATUS_STRING[417]="Expectation Failed";
		HTTP_STATUS_STRING[500]="Internal Server Error";
		HTTP_STATUS_STRING[501]="Not Implemented";
		HTTP_STATUS_STRING[502]="Bad Gateway";
		HTTP_STATUS_STRING[503]="Service Unavailable";
		HTTP_STATUS_STRING[504]="Gateway Timeout";
		HTTP_STATUS_STRING[505]="HTTP Version Not Supported";

		return HTTP_STATUS_STRING;
	};

	size_t dw_callback(void* buf, size_t size, size_t nmemb, void* userp)
	{
		if(userp)
		{
			std::ostream& os = *static_cast<std::ostream*>(userp);
			std::streamsize len = size * nmemb;
			if(os.write(static_cast<char*>(buf), len))
				return len;
		}
		return 0;
	};
}; };

