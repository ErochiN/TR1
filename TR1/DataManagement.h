#pragma once
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
#include "MyList.h"

class DataManagement
{
public:

	DataManagement();

private:
	static const std::string JsonCityCode;

	struct DataCity
	{
		std::string code;
		std::string nameEn;
		std::string nameRu;
		std::string countryCode;
	};

	struct GettingDataCity
	{
		std::string flight_number;
		std::string departure_at;
		int price;
	};


	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

	void GetJSON();

	std::string toLower(std::string str);

	
public:
	List<DataCity> lstCityData;
	List<GettingDataCity> getterData;

	int CitySearch(std::string nameCity);
	void GetDataJson(DataCity cityOne, DataCity cityTwo, std::string dataTime);

	void ShowData(const int index);

};

