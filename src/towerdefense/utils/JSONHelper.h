#pragma once

#include <rapidjson/document.h>
#include <string>

namespace TowerDefense
{
	bool ParseFile(const std::string& fileName, rapidjson::Document& document);
}