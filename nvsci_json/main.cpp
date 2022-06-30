#include <iostream>
#include "mta_config_json_file_provider.hpp"

using namespace std;
using namespace test_interfaces;
int main(int argc, char* argv[])
{
    cout << "start with argv[1] " << argv[1] << std::endl;
	JsonMtaConfigFileProvider jsonConfig(argv[1]);
    jsonConfig.parse();
}
