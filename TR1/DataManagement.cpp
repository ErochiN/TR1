#include "DataManagement.h"

DataManagement::DataManagement()
{
	GetJSON();
}

size_t DataManagement::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
	size_t total_size = size * nmemb;
	output->append((char*)contents, total_size);
	return total_size;
}

void DataManagement::GetJSON()
{
	CURL* curl;
	CURLcode res;
	std::string response;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.travelpayouts.com/data/ru/cities.json");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			nlohmann::json data = nlohmann::json::parse(response);

			for (const auto& item : data)
			{
				DataCity city;

				if (item.contains("code")) city.code = item["code"].get<std::string>();
				if (item.contains("name")) city.nameRu = item["name"].get<std::string>();
				if (item.contains("country_code")) city.countryCode = item["country_code"].get<std::string>();

				if (item.contains("name_translations") &&
					item["name_translations"].contains("en")) {
					city.nameEn = item["name_translations"]["en"].get<std::string>();
				}

				lstCityData.push_back(city);
			}

		}

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

std::string DataManagement::toLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return str;
}

int DataManagement::CitySearch(std::string nameCity)
{
	int returnIndex = 0;
	std::string lowerInput = toLower(nameCity);
	bool found = false;

	for (int i = 0; i < lstCityData.GetSize(); ++i)
	{
		const DataCity& city = lstCityData[i];

		std::string lowerRu = toLower(city.nameRu);
		std::string lowerEn = toLower(city.nameEn);

		if (lowerRu.find(lowerInput) != std::string::npos || lowerEn.find(lowerInput) != std::string::npos)
		{
			found = true;
			returnIndex = i;

			break;
		}
	}

	if (!found)
	{
		std::cout << "Город не найден в списке." << std::endl;
	}

	return returnIndex;
}

void DataManagement::GetDataJson(DataCity cityOne, DataCity cityTwo, std::string dataTime)
{
	CURL* curl;
	CURLcode res;
	std::string response;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {

		std::string encodedOrigin = curl_easy_escape(curl, cityOne.code.c_str(), 0);
		std::string encodedDest = curl_easy_escape(curl, cityTwo.code.c_str(), 0);

		std::string url = "https://api.travelpayouts.com/aviasales/v3/prices_for_dates?origin=" + encodedOrigin +
			"&destination=" + encodedDest +
			"&departure_at=" + dataTime +
			"&currency=rub&token=ca2c5aa34f73e98096a012d6a0a8e68f";

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}
		else
		{
			nlohmann::json data = nlohmann::json::parse(response);

			for (const auto& item : data["data"])
			{
				GettingDataCity city;

				if (item.contains("flight_number")) city.flight_number = item["flight_number"].get<std::string>();
				if (item.contains("departure_at")) city.departure_at = item["departure_at"].get<std::string>();
				if (item.contains("price")) city.price = item["price"].get<int>();

				getterData.push_back(city);
			}
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
}

void DataManagement::ShowData(const int index)
{
	std::cout << "flight_number: " << getterData[index].flight_number << std::endl;
	std::cout << "departure_at: " << getterData[index].departure_at << std::endl;
	std::cout << "price: " << getterData[index].price << std::endl;
}
