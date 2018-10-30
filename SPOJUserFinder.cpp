#include <iostream>
#include <string>
#include <algorithm>
#include <curl/curl.h>

static size_t WriteCallback(void * contents, size_t size, size_t nmemb, void * userp) {
	((std::string *) userp)->append((char *) contents, size * nmemb);
	return size * nmemb;
}

int main (int argc, char * argv[]) {
	int page_counter = 0;
	bool found = false;
	std::string name_to_find = argv[1];

	while (!found) {
		CURL * curl;
		CURLcode res;
		std::string read_buffer;
		curl = curl_easy_init();

		if (curl) {
			std::string address = "https://pl.spoj.com/ranks2/?start=" + std::to_string(page_counter * 25);
		
			curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			size_t it_beg = read_buffer.find("<tbody>");
			size_t it_end = read_buffer.find("</tbody>");

			std::string table = read_buffer.substr(it_beg, it_end - it_beg);

			int record_counter = 0;

			it_beg = 0;
			while (1) {
				it_beg = table.find("<a href", it_beg + 1);
				it_end = table.find("</a>", it_beg + 1);

				std::string record = table.substr(it_beg, it_end - it_beg);

				size_t it_beg_name = record.find("blank\">");
				size_t it_end_name = record.find("\0");

				std::string name = record.substr(it_beg_name + 7, it_end_name + 7 - it_beg_name);
			
				++record_counter;

				if (name == name_to_find) {
					std::cout << "Found " << name << " on position " << record_counter + page_counter * 25 << std::endl;
					found = true;
				}

				if (record_counter % 25 == 0)
					break;
			}
			++page_counter;
		}
	}
	return 0;
} 