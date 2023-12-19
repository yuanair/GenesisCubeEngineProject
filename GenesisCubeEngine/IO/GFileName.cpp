#include "GFileName.h"
#include <string>
#include <utility>


namespace GenesisCubeEngine
{



	GFileName::GFileName(TString fileName)
		: fileName(std::move(fileName))
	{

	}

}
