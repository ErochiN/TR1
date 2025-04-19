#include <iostream>
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
#include "MyList.h"
#include "DataManagement.h"

int main()
{
	DataManagement data;

	std::string strCityOne;
	std::string strCityTwo;

	std::cout << "enter one city: " << strCityOne;
	std::cin >> strCityOne;

	std::cout << "enter two city: " << strCityTwo;
	std::cin >> strCityTwo;

	int indexOne = data.CitySearch(strCityOne);
	int indexTwo = data.CitySearch(strCityTwo);

	data.GetDataJson(data.lstCityData[indexOne], data.lstCityData[indexTwo], "2025-04");
	data.ShowData(0);

	return 0;
}
