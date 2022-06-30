// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
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
#ifndef TEST_INTERFACES__MTA_CONFIG_FILE_PROVIDER_HPP
#define TEST_INTERFACES__MTA_CONFIG_FILE_PROVIDER_HPP

// #include "iceoryx_utils/cxx/string.hpp"
#include <string>
#include <vector>
#include <cstring>
namespace test_interfaces
{
  using namespace std;
// using ConfigFilePathString_t = cxx::string<1024>;  
/// @brief This are the errors which can occur when a config file is parsed
/// NO_GENERAL_SECTION - the section for general config was not found
/// INVALID_CONFIG_FILE_VERSION - an invalid config file version was detected
/// NO_SEGMENTS - at least one segment needs to be defined
/// MAX_NUMBER_OF_SEGMENTS_EXCEEDED - max number of segments exceeded
/// SEGMENT_WITHOUT_MEMPOOL - a segment must have at least one mempool
/// MAX_NUMBER_OF_MEMPOOLS_PER_SEGMENT_EXCEEDED - the max number of mempools per segment is exceeded
/// MEMPOOL_WITHOUT_CHUNK_SIZE - chunk size not specified for the mempool
/// MEMPOOL_WITHOUT_CHUNK_COUNT - chunk count not specified for the mempool
enum class RouDiConfigFileParseError : uint8_t
{
    INVALID_STATE,
    NO_GENERAL_SECTION,
    INVALID_CONFIG_FILE_VERSION,
    NO_SEGMENTS,
    MAX_NUMBER_OF_SEGMENTS_EXCEEDED,
    SEGMENT_WITHOUT_MEMPOOL,
    MAX_NUMBER_OF_MEMPOOLS_PER_SEGMENT_EXCEEDED,
    MEMPOOL_WITHOUT_CHUNK_SIZE,
    MEMPOOL_WITHOUT_CHUNK_COUNT,
};

constexpr const char* ROUDI_CONFIG_FILE_PARSE_ERROR_STRINGS[] = {"INVALID_STATE",
                                                                 "NO_GENERAL_SECTION",
                                                                 "INVALID_CONFIG_FILE_VERSION",
                                                                 "NO_SEGMENTS",
                                                                 "MAX_NUMBER_OF_SEGMENTS_EXCEEDED",
                                                                 "SEGMENT_WITHOUT_MEMPOOL",
                                                                 "MAX_NUMBER_OF_MEMPOOLS_PER_SEGMENT_EXCEEDED",
                                                                 "MEMPOOL_WITHOUT_CHUNK_SIZE",
                                                                 "MEMPOOL_WITHOUT_CHUNK_COUNT"};

struct MtaRawBuf_t
{
    uint32_t userdata{0};
    uint32_t size{0};
    uint32_t alignment{0};
    string bufAttr;
    bool syncMode{false};
    bool piggyback{false};
    /// @brief Default constructor to set the configuration for rawbuf
    MtaRawBuf_t() = default;

};

struct MtaImageBuf_t
{
    uint32_t userdata{0};
    string surfaceFormat;
    bool syncMode{0};
    bool piggyback{0};
    /// @brief Default constructor to set the configuration for rawbuf
    MtaImageBuf_t() = default;
};

union MtaElementConfig_t
{
    MtaRawBuf_t rawBuf;
    MtaImageBuf_t imageBuf;
    MtaElementConfig_t() {memset(this, 0, sizeof(*this));};
    ~MtaElementConfig_t() {};
};

typedef struct _MtaJsonConfig_t
{
    string ipcLocal;
    string ipcRemote;
    uint32_t packetCount;
    uint32_t elementCount;
    //std::vector<MtaElementConfig_t> elements;
}MtaJsonConfig_t;

using namespace std;
/// @brief Base class for a config file provider.
class MtaConfigFileProvider
{
  public:
    /// @brief interface to parse a config file which needs to be implemented for a custom parser
    /// @param[in] configFilePath to the custom RouDi config file
    /// @return a cxx::expected with either the parsed RouDiConfig_t if the parsing was successful or a parsing error
    //virtual cxx::expected<RouDiConfig_t, RouDiConfigFileParseError> parse() = 0;
    virtual MtaJsonConfig_t parse() = 0;
  protected:
    //ConfigFilePathString_t m_customConfigFilePath;
    std::string m_customConfigFilePath;
};

} // namespace test_interfaces

#endif // TEST_INTERFACES__MTA_CONFIG_FILE_PROVIDER_HPP
