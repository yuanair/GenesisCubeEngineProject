//
// Created by admin on 2023/12/21.
//

#include <iostream>
#include <GenesisCubeBase/Json/Json.h>

using namespace std;
using namespace GenesisCube;
using namespace JSON;

int main()
{
	
	Json json;
	
	json[TEXT("key")] = TEXT("fuck\n\n\r");
	
	json[TEXT("key2")] = nullptr;
	
	wcout << json.ToString() << endl;
	
	return 0;
}
