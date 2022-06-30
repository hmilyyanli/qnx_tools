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
#ifndef TEST_INTERFACES__MTA_CONFIG_JSON_FILE_PROVIDER_HPP
#define TEST_INTERFACES__MTA_CONFIG_JSON_FILE_PROVIDER_HPP


#include "mta_config_file_provider.hpp"

extern "C" {
#include "tiny-json.h"
}

namespace test_interfaces
{

static constexpr char defaultConfigJsonPath[] = "/etc/nvsci_mta_config.json";

/// @brief Reader for Roudi Configuration using json config file
class JsonMtaConfigFileProvider : public test_interfaces::MtaConfigFileProvider
{
  private:
    /// @brief reads a mempool configuration from a segment
    /// @return the Mempool configuration or a helpful error when it is misconfigured
    // iox::cxx::expected<iox::mepoo::MePooConfig, iox::roudi::RouDiConfigFileParseError>
    // getMempool(json_t const* segment);
    void getElepool(json_t const* element);
  public:
    /// @brief constructor taking the comand-line options
    /// @param[in] cmdLineArgs parsed command line arguments
    JsonMtaConfigFileProvider(char const* path = nullptr);
    /// @brief default deconstructor
    virtual ~JsonMtaConfigFileProvider() = default;

    /// @brief Reads the manifest from a json file
    /// @code
    //   "general":{
    //      "version" : 1
    // },
    // "ipc":{
    //      "local"  : "nvscisync_b_1",
    //      "remote" : "nvscisync_b_0" 
    // },
    // "packet":{
    //       "count" : 6,
    //       "element" : 2
    // },
    // "elements":[
    //      {
    //         "RawCPU" : {
    //              "userdata" : 1,
    //              "size" : 123,
    //              "aligment" : 4,
    //              "BufAttr" : "NvSciBufAccessPerm_Readonly",
    //              "syncMode" : "NvSciStreamElementMode_Asynchronous",
    //              "Piggyback" : "false"
    //          },
    //          "RawCuda" : {
    //              "userdata" : 2,
    //              "size" : 123,
    //              "aligment" : 4,
    //              "BufAttr" : "NvSciBufAccessPerm_Readonly",
    //              "syncMode" : "NvSciStreamElementMode_Asynchronous",
    //              "Piggyback" : "false"
    //          }
    //      }
    // ] 
    /// @endcode
    /// @return[in] the roudi config or a helpful error
    MtaJsonConfig_t parse() noexcept override;
};

} // namespace test_interfaces

#endif /* TEST_INTERFACES__MTA_CONFIG_JSON_FILE_PROVIDER_HPP */
