#include "JSONHelper.h"
#include "GameParameters.h"

#include <fstream>
#include <sstream>
#include <SDL2/SDL_log.h>

namespace TowerDefense
{
	bool ParseFile(const std::string& fileName, rapidjson::Document& document)
	{
		std::ifstream stream(fileName);
		if (!stream.is_open() || stream.fail())
		{
			stream.close();

			if(DISPLAY_LOGS)
            {
                SDL_Log("Unable to read file: %s", fileName.c_str());
            }
			return false;
		}
		std::stringstream sStream;
		sStream << stream.rdbuf();
		document.Parse(sStream.str().c_str());
		stream.close();

		if (document.HasParseError())
		{
		    if(DISPLAY_LOGS)
            {
                SDL_Log("Unable to parse file. Error Code: %i", document.GetParseError());
            }
			return false;
		}
		return true;
	}
}