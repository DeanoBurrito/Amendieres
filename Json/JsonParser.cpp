#include <exception>
#include <locale>
#include <limits>
#include "JsonParser.h"

#ifndef AMENDIERES_JSON_STANDALONE
#include "../Debug.h"
#else
    #define LOG_ERROR(x)
    #define LOG(x)
    #define LOG_ERROR_IF(x)
#endif

#define NUMBER_BUFF_STARTING_SIZE 32

namespace Amendieres
{    
    std::unique_ptr<JsonNode> JsonParser::ParseFile(const std::string& filename)
    {
        Init();
        
        std::fstream inFile;
        inFile.open(filename, std::ios::in);
        
        if (!inFile.is_open())
        {
            LOG_ERROR("JSON parser was unable to open file: " << filename);
            return std::make_unique<JsonNode>(JsonNode());
        }

        input = &inFile;

        try
        {
            LexTokens();
        }
        catch (std::exception e)
        {
            LOG_ERROR("JSON parser triggered exception: " << e.what() << ". Location: " << input->tellg());
            inFile.close();
            return std::make_unique<JsonNode>(JsonNode());
        }
        inFile.close();

        return Fin();
    }

    std::unique_ptr<JsonNode> JsonParser::ParseStream(std::istream& istream)
    {
        Init();
        input = &istream;

        try
        {
            LexTokens();
        }
        catch (std::exception e)
        {
            LOG_ERROR("JSON parser triggered exception: " << e.what() << ". Location: " << input->tellg());
            return std::make_unique<JsonNode>(JsonNode());
        }

        return Fin();
    }

    void JsonParser::Init()
    {
        tokens.clear();
        outputValid = true;
        currentToken = 0;
        //numberBuff.reserve(NUMBER_BUFF_STARTING_SIZE);
    }

    std::unique_ptr<JsonNode> JsonParser::Fin()
    {
        if (tokens.back().type != JsonTokenType::EndOfFile)
        {
            LOG_ERROR("Json parser read incorrect data, no EOF has been stored.");
            return std::make_unique<JsonNode>(JsonNode());
        }
        
        JsonNode* output = ParseValue();
        MatchToken(JsonTokenType::EndOfFile); //last token should be EOF, otherwise there's data we havent processed yet.

        if (outputValid)
            return std::unique_ptr<JsonNode>(output);
        return std::make_unique<JsonNode>(JsonNode());
    }

    JsonObject* JsonParser::ParseObject()
    { 
        JsonToken openBrace = MatchToken(JsonTokenType::OpenBrace);
        std::vector<JsonObjectMember*> members;

        while (PeekToken().type != JsonTokenType::CloseBrace)
        {
            if (members.size() > 0)
                MatchToken(JsonTokenType::Comma);
            members.push_back(ParseObjectMember());
        }
        JsonToken closeBrace = MatchToken(JsonTokenType::CloseBrace);

        return new JsonObject(members);
    }

    JsonObjectMember* JsonParser::ParseObjectMember()
    {
        std::string name = MatchToken(JsonTokenType::String).text;
        JsonToken delim = MatchToken(JsonTokenType::Colon);
        JsonNode* value = ParseValue();

        return new JsonObjectMember(name, value);
    }

    JsonArray* JsonParser::ParseArray()
    { 
        JsonToken openBracket = MatchToken(JsonTokenType::OpenBracket);
        std::vector<JsonNode*> elements;

        while (PeekToken().type != JsonTokenType::CloseBracket)
        {
            if (elements.size() > 0)
                MatchToken(JsonTokenType::Comma);
            elements.push_back(ParseValue());
        }
        JsonToken closeBracket = MatchToken(JsonTokenType::CloseBracket);

        return new JsonArray(elements);
    }

    JsonNode* JsonParser::ParseValue()
    { 
        JsonToken next = PeekToken();
        switch (next.type) 
        {
        case JsonTokenType::OpenBrace:
            return ParseObject();
        case JsonTokenType::OpenBracket:
            return ParseArray();
        
        case JsonTokenType::String:
            MatchToken(JsonTokenType::String);
            return new JsonString(next.text);
        
        case JsonTokenType::NumberInt:
        {
            MatchToken(JsonTokenType::NumberInt);
            int64_t intVal = std::atoll(next.text.c_str());
            return new JsonNumberInt(intVal);
        }
        
        case JsonTokenType::NumberFloat:
        {
            MatchToken(JsonTokenType::NumberFloat);
            float floatVal = std::atof(next.text.c_str());
            return new JsonNumberFloat(floatVal);
        }

        case JsonTokenType::True:
            MatchToken(JsonTokenType::True);
            return new JsonBool(true);
        case JsonTokenType::False:
            MatchToken(JsonTokenType::False);
            return new JsonBool(false);
        
        case JsonTokenType::Null:
            MatchToken(JsonTokenType::Null);
            return new JsonNode();

        default:
            outputValid = false;
            LOG_ERROR("Unexpected token type as value: " << static_cast<int>(next.type));
            NextToken(); //consume unknown to avoid infinite loops in parsing.
            return new JsonNode();
        }
    }

    JsonToken JsonParser::MatchToken(const JsonTokenType expected)
    { 
        JsonToken next = NextToken();
        if (next.type == expected)
            return next;
        
        outputValid = false;
        LOG_ERROR("Expected json token: " << static_cast<int>(expected) << ", got instead " << static_cast<int>(next.type) << ". Text=" << next.text);
        return JsonToken(expected, "<SynthesizedToken>");
    }

    JsonToken JsonParser::NextToken()
    { 
        JsonToken next = tokens[currentToken];
        currentToken++;
        if (currentToken >= tokens.size())
            currentToken = tokens.size() - 1;
        return next;
    }

    JsonToken JsonParser::PeekToken()
    {
        return tokens[currentToken];
    }

    void JsonParser::LexTokens()
    {
        while (true)
        {
            currentChar = input->get();
            if (input->eof())
            {
                tokens.push_back({ JsonTokenType::EndOfFile, "" });
                break;
            }

            switch (currentChar)
            {
            case '/': //This is a comment :D
                input->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            case '{':
                tokens.push_back({ JsonTokenType::OpenBrace, "{" });
                continue;
            case '}':
                tokens.push_back({ JsonTokenType::CloseBrace, "}" });
                continue;
            case '[':
                tokens.push_back({ JsonTokenType::OpenBracket, "[" });
                continue;
            case ']':
                tokens.push_back({ JsonTokenType::CloseBracket, "]" });
                continue;
            case ':':
                tokens.push_back({ JsonTokenType::Colon, ":" });
                continue;
            case ',':
                tokens.push_back({ JsonTokenType::Comma, "," });
                continue;

                //See note about destructive whitespace consumption below
            case ' ':
            case '\n':
            case '\t':
                continue;
            
            default:
                LexComplexToken();
                continue;
            }
        }
    }

    void JsonParser::LexComplexToken()
    {
        if (currentChar == '\"')
        {
            LexStringToken();
            return;
        }

        if (std::isspace(currentChar))
        {
            while (std::isspace(input->peek()))
            {
                /*  NOTE:
                    Currently this is destructive, in that it consumes whitespace from the input without
                    actually storing in on the tree. This is fine for now, but will stop us recreating the input
                    later if we need to. Something to be aware of.
                */
                input->get();
            }
            return;
        }

        if (std::isdigit(currentChar) 
            || (currentChar == '-' && std::isdigit(input->peek())) 
            || (currentChar == '+') && std::isdigit(input->peek()))
        {
            LexNumberToken();
            return;
        }

        //only remaining tokens are literals, so put back that char we just looked at
        input->unget();

        //peek ahead until the next whitespace, all that cna be left is true/false/null literals
        std::string nextLiteral;
        std::getline(*input, nextLiteral, '\n');
        if (nextLiteral.compare("true") == 0)
        {
            tokens.push_back({ JsonTokenType::True, "true" });
            return;
        }
        else if (nextLiteral.compare("false") == 0)
        {
            tokens.push_back({ JsonTokenType::False, "false" });
            return;
        }
        else if (nextLiteral.compare("null") == 0)
        {
            tokens.push_back({ JsonTokenType::Null, "null" });
            return;
        }

        LOG_ERROR("Unknown literal token \"" << nextLiteral << "\" @ " << input->tellg());
    }

    void JsonParser::LexStringToken()
    {
        std::string data;
        std::getline(*input, data, '\"');
        //TODO: This currently ignores escaped quotes, we should check the previous character. If it's a backslash, then we keep consuming input until the next set of quotes.
        
        tokens.push_back({ JsonTokenType::String, data });
    }


    void JsonParser::LexNumberToken()
    {
        numberBuff.clear();
        numberBuff.push_back(currentChar);

        while (std::isdigit(input->peek()))
        {
            numberBuff.push_back(input->get());
        }

        bool isInteger = true;
        if (input->peek() == '.')
        {
            numberBuff.push_back(input->get());
            isInteger = false;

            //The JSON standard says there must be at least 1 digit following the point. 
            //I'm not enforcing that here as atof() (which we ultimately use), dosnt require it either.
            while (std::isdigit(input->peek()))
            {
                numberBuff.push_back(input->get());
            }
        }
        if (input->peek() == 'e' || input->peek() == 'E')
        {
            numberBuff.push_back(input->get());
            isInteger = false;

            if (input->peek() == '-' || input->peek() == '+')
                numberBuff.push_back(input->get());
            
            int readDigits = 0;
            while (std::isdigit(input->peek()))
            {
                numberBuff.push_back(input->get());
                readDigits++;
            }

            LOG_ERROR_IF(readDigits == 0, "JSON Parser read floating point value with exponent, but no digits following. This is not standards compliant. Parsed number so far: " << std::string(numberBuff.data(), numberBuff.size()));
        }

        std::string data(numberBuff.data(), numberBuff.size());
        if (isInteger)
            tokens.push_back({ JsonTokenType::NumberInt, data });
        else
            tokens.push_back({ JsonTokenType::NumberFloat, data });
    }
}