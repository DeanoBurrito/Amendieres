#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Amendieres
{
    enum class JsonNodeType
    {
        Object,
        ObjectMember,
        Array,
        String,
        NumberFloat,
        NumberInt,
        Bool,
        Null,
    };
    
    class JsonNode
    {
    public:
        JsonNodeType type = JsonNodeType::Null;

        virtual ~JsonNode() {}
        bool Exists(const std::string& path) const;
        JsonNode* Find(const std::string& path) const;
        
        template <class T> 
        T* Find(const std::string& path) const
        {
            static_assert(std::is_base_of<JsonNode, T>(), "JsonNode::Find can only return JsonNode types, derived is not of this type.");
        
            JsonNode* found = Find(path);
            if (found != nullptr)
                return static_cast<T*>(found);
            return nullptr;
        }
    };

    class JsonObjectMember : public JsonNode
    {
    public:
        std::string name;
        JsonNode* value;

        JsonObjectMember(std::string nName, JsonNode* nValue);
        ~JsonObjectMember();
    };

    class JsonObject : public JsonNode
    {
    public:
        std::vector<JsonObjectMember*> members;

        JsonObject(std::vector<JsonObjectMember*> nMembers);
        ~JsonObject();
    };

    class JsonArray : public JsonNode
    {
    public:
        std::vector<JsonNode*> elements;

        JsonArray(std::vector<JsonNode*> nElements);
        ~JsonArray();
    };

    class JsonString : public JsonNode
    {
    public:
        std::string value;

        JsonString(std::string nValue);
    };

    class JsonNumberFloat : public JsonNode
    {
    public:
        float value;

        JsonNumberFloat(float nValue);
    };

    class JsonNumberInt : public JsonNode
    {
    public:
        int64_t value;

        JsonNumberInt(int64_t nValue);
    };

    class JsonBool : public JsonNode
    {
    public:
        bool value;

        JsonBool(bool nValue);
    };
}