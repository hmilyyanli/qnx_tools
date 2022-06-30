// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "mta_config_json_file_provider.hpp"

namespace test_interfaces
{
    using namespace std;
JsonMtaConfigFileProvider::JsonMtaConfigFileProvider(char const* path)
{  
    /// don't print additional output if not running

     //cout << "path is " << path << endl;
    if (nullptr == path)
    {
        // open default path
#if 0                
        if (cmdLineArgs.m_configFilePath.empty())
        {
            cxx::FileReader configFile(std::begin(defaultConfigJsonPath), "", cxx::FileReader::ErrorMode::Ignore);

            if (configFile.IsOpen())
            {
                LogInfo() << "No config file provided. Using '" << defaultConfigJsonPath << "'";
                m_customConfigFilePath = defaultConfigJsonPath;
            }
            else
            {
                LogInfo() << "No config file provided and also not found at '" << defaultConfigJsonPath
                          << "'. Falling back to built-in config.";
            }
        }
        else
        {
            m_customConfigFilePath = cmdLineArgs.m_configFilePath;
        }
#endif        
    }
    else
    {
        cout << "path is " << path << endl;
        m_customConfigFilePath = path;
    }
}
#if 1
void JsonMtaConfigFileProvider::getElepool(json_t const* element)
{
    //MtaElementConfig_t eleConfig;
    MtaElementConfig_t rawBuf;
    if( !std::strcmp(element->name,"RawBuf") )
    {
        json_t const* userdata = json_getProperty(element, "userdata");
        if (nullptr == userdata || JSON_INTEGER != json_getType(userdata))
        {
            
        }
        else
        {
            cout << json_getValue(userdata) << endl;
        }
    }else if(! std::strcmp(element->name,"ImageBuf"))
    {
        json_t const* userdata = json_getProperty(element, "userdata");
        if (nullptr == userdata || JSON_INTEGER != json_getType(userdata))
        {
        }else
        {
            cout << json_getValue(userdata) << endl;
        }
    }
    
}
#endif

#if 0
iox::cxx::expected<iox::mepoo::MePooConfig, iox::roudi::RouDiConfigFileParseError>
JsonRouDiConfigFileProvider::getMempool(json_t const* segment)
{
    iox::mepoo::MePooConfig mempoolConfig;
    json_t const* mempools = json_getProperty(segment, "mempool");
    if (nullptr == mempools || JSON_ARRAY != json_getType(mempools)) 
    {
        return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
            iox::roudi::RouDiConfigFileParseError::SEGMENT_WITHOUT_MEMPOOL);
    }
    json_t const* mempool;
    uint32_t poolCount = 0;
    for (mempool = json_getChild(mempools); mempool != nullptr; mempool = json_getSibling(mempool))
    {
        if (JSON_OBJ == json_getType(mempool) && poolCount < iox::MAX_NUMBER_OF_MEMPOOLS)
        {
            json_t const* chunkSize = json_getProperty(mempool, "size");
            if (nullptr == chunkSize || JSON_INTEGER != json_getType(chunkSize))
            {
                return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
                    iox::roudi::RouDiConfigFileParseError::MEMPOOL_WITHOUT_CHUNK_SIZE);
            }
            json_t const* chunkCount = json_getProperty(mempool, "count");
            if (nullptr == chunkCount || JSON_INTEGER != json_getType(chunkCount))
            {
                return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
                    iox::roudi::RouDiConfigFileParseError::MEMPOOL_WITHOUT_CHUNK_COUNT);
            }
            uint32_t size = static_cast<uint32_t>(json_getInteger(chunkSize));
            uint32_t count = static_cast<uint32_t>(json_getInteger(chunkCount));
            mempoolConfig.addMemPool({size, count});
        }
        poolCount++;
    }
    if (poolCount > iox::MAX_NUMBER_OF_MEMPOOLS)
    {
        return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
            iox::roudi::RouDiConfigFileParseError::MAX_NUMBER_OF_MEMPOOLS_PER_SEGMENT_EXCEEDED);
    }
    return iox::cxx::success<iox::mepoo::MePooConfig>(mempoolConfig);
}
#endif

MtaJsonConfig_t
JsonMtaConfigFileProvider::parse() noexcept
{
    // 11 Nodes are required for the one time nodes in configuration like parallelism etc.
    // 3 Nodes are required per Mempool (one for the mempool object, one for the number of elements and one for its
    // size).
    // 4 Nodes are required per Segment (one for the Segment object, one for writer and reader and one for the
    // mempool  array).
    constexpr static uint32_t NUMBER_OF_JSON_NODES = 256;//MAX_SHM_SEGMENTS * (4 + MAX_NUMBER_OF_MEMPOOLS * 3) + 11;
    std::cout << "start ..." << endl;
    //std::vector<json_t> mem(NUMBER_OF_JSON_NODES);
    json_t mem[NUMBER_OF_JSON_NODES];
    std::string content, line;
    MtaJsonConfig_t config;
    //memset(config, 0, sizeof(MtaJsonConfig_t));
    // Early exit in case no config file path was provided
  #if 0  
    if (m_customConfigFilePath.empty())
    {
        //iox::RouDiConfig_t defaultConfig;
        //defaultConfig.setDefaults();
        //return iox::cxx::success<iox::RouDiConfig_t>(defaultConfig);
        std::cout << "error: empty configure!" << std::endl;
        return config;
    }
#endif
    //std::ifstream reader(m_customConfigFilePath.c_str(), "", iox::cxx::FileReader::ErrorMode::Inform);
    std::ifstream reader("nvsci_mta_config.json", std::ifstream::in);

    //while (reader.ReadLine(line))
    while( std::getline(reader, line) )
    {
        content.append(line);
    }
    json_t const* json = json_create(&content[0], mem, NUMBER_OF_JSON_NODES);
    if (nullptr == json)
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::INVALID_STATE);
        cout << "error: create json file!" << endl;
        return config;
    }
    json_t const* general = json_getProperty(json, "general");
    if (nullptr == general || JSON_OBJ != json_getType(general))
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::NO_GENERAL_SECTION);
         cout << "error: get general!" << endl;
    }

    json_t const* version = json_getProperty(general, "version");
    if (nullptr == version || JSON_INTEGER != json_getType(version) || 1 != json_getInteger(version))
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::INVALID_CONFIG_FILE_VERSION);
    }
    else
    {
        cout << json_getValue(version) << endl;
    }

    json_t const* ipc = json_getProperty(json, "ipc");
    if (nullptr == ipc || JSON_OBJ != json_getType(ipc))
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::NO_SEGMENTS);
	 cout << "error ipc" << endl;
	 return config;
    }
    json_t const* local = json_getProperty(ipc, "local");
    if (nullptr == local || JSON_TEXT != json_getType(local) )
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::INVALID_CONFIG_FILE_VERSION);
        cout << "error" << endl;
    }
    else
    {
        cout << json_getValue(local) << endl;
    }

    json_t const* remote = json_getProperty(ipc, "remote");
    if (nullptr == remote || JSON_TEXT != json_getType(remote) )
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::INVALID_CONFIG_FILE_VERSION);
        cout << "error" << endl;
    }
    else
    {
        cout << json_getValue(remote) << endl;
    }

    json_t const* packet = json_getProperty(json, "packet");
    if (nullptr == packet || JSON_ARRAY != json_getType(packet))
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::NO_SEGMENTS);
    }
    json_t const* count = json_getProperty(packet, "size");
    if (nullptr == local || JSON_INTEGER != json_getType(count) )
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::INVALID_CONFIG_FILE_VERSION);
        cout << "error" << endl;
    }
    else
    {
        cout << json_getInteger(count) << endl;
    }

    json_t const* elements = json_getProperty(json, "elements");
    if (nullptr == elements || JSON_OBJ != json_getType(elements) )
    {
        // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
        //     iox::roudi::RouDiConfigFileParseError::INVALID_CONFIG_FILE_VERSION);
        cout << "error" << endl;
    }
    
    //iox::RouDiConfig_t parsedConfig;
    json_t const* element;
    uint32_t eleCount = 0;
    for (element = json_getChild(elements); element != nullptr; element = json_getSibling(element))
    {
        if (JSON_OBJ == json_getType(element) && eleCount < 5)
        {
            getElepool(element);
            // iox::cxx::expected<iox::mepoo::MePooConfig, iox::roudi::RouDiConfigFileParseError> meepooConfig =
            //      getMempool(segment);
            // if (meepooConfig.has_error())
            // {
            //     return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(meepooConfig.get_error());
            // }
            // parsedConfig.m_sharedMemorySegments.push_back({meepooConfig.get_value()});
        }
        eleCount++;
    }
    cout << "eleCount " << eleCount << endl;
    // if (segCount > 5)
    // {
    //     // return iox::cxx::error<iox::roudi::RouDiConfigFileParseError>(
    //     //     iox::roudi::RouDiConfigFileParseError::MAX_NUMBER_OF_SEGMENTS_EXCEEDED);
    // }
    //return iox::cxx::success<iox::RouDiConfig_t>(parsedConfig);
    return config;
}

} // namespace test_interfaces
