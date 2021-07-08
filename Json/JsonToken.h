#pragma once

#include <string>

namespace Amendieres
{
    enum class JsonTokenType
    {
        EndOfFile,
        Whitespace,
        Colon,
        Comma,

        OpenBrace,
        CloseBrace,
        OpenBracket,
        CloseBracket,

        String,
        NumberInt,
        NumberFloat,
        True,
        False,
        Null,
    };
    
    class JsonToken
    {
    public:
        JsonToken(JsonTokenType t, std::string txt) 
        {
            type = t;
            text = txt;
        }

        JsonTokenType type;
        std::string text;
    private:
    };
}