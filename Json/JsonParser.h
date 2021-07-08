#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "JsonToken.h"
#include "JsonNode.h"

namespace Amendieres
{       
    class JsonParser
    {
    public:

        std::unique_ptr<JsonNode> ParseFile(const std::string& filename);
        std::unique_ptr<JsonNode> ParseStream(std::istream& istream);
    private:
        char currentChar;
        std::istream* input;
        std::vector<JsonToken> tokens;
        std::vector<char> numberBuff;

        bool outputValid;
        int currentToken;

        void Init();
        std::unique_ptr<JsonNode> Fin();

        JsonObject* ParseObject();
        JsonObjectMember* ParseObjectMember();
        JsonArray* ParseArray();
        JsonNode* ParseValue();

        JsonToken MatchToken(const JsonTokenType expected);
        JsonToken NextToken();
        JsonToken PeekToken();

        void LexTokens();
        void LexComplexToken();
        void LexStringToken();
        void LexNumberToken();
    };
}