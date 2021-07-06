#include "JsonNode.h"

namespace Amendieres
{
    int IndexFromPath(const std::string& path)
    {
        try
        {
            int index = std::atoi(path.c_str());
            return index;
        }
        catch ( ... )
        {
            return -1;
        }
        return -1;
    }
    
    bool JsonNode::Exists(const std::string& path) const
    {   
        return Find(path) != nullptr;
    }

    JsonNode* JsonNode::Find(const std::string& path) const
    {
        std::string remainder = "";
        std::string identifier = path;

        auto delimPos = path.find('/');
        if (delimPos != std::string::npos)
        {
            remainder = path.substr(delimPos + 1);
            identifier = path.substr(0, delimPos);
        }

        //if path started with '/', run recursively with remainder of path
        if (identifier.size() == 0)
            return Find(remainder);

        if (type == JsonNodeType::Object)
        {
            const JsonObject* thisObj = static_cast<const JsonObject*>(this);
            for (auto member : thisObj->members)
            {
                if (member->name.compare(identifier) == 0)
                {
                    //indentity matches
                    if (remainder.size() > 0)
                        return member->value->Find(remainder);
                    else
                        return member->value;
                }
            }
        }
        else if (type == JsonNodeType::Array)
        {
            const JsonArray* thisArray = static_cast<const JsonArray*>(this);
            int index = IndexFromPath(identifier);
            
            //path was either not a number, or is an invalid index, head home.
            if (index < 0 || index >= thisArray->elements.size())
                return nullptr;
            
            if (remainder.size() > 0)
                return thisArray->elements[index]->Find(remainder);
            else
                return thisArray->elements[index];
        }
        
        return nullptr; //path cannot be continued or does not exist
    }

    JsonObjectMember::JsonObjectMember(std::string nName, JsonNode* nValue)
    {
        type = JsonNodeType::ObjectMember;
        name = nName;
        value = nValue;
    }

    JsonObjectMember::~JsonObjectMember()
    {
        delete value;
    }

    JsonObject::JsonObject(std::vector<JsonObjectMember*> nMembers)
    {
        type = JsonNodeType::Object;
        members = nMembers;
    }

    JsonObject::~JsonObject()
    {
        for (auto member : members)
            delete member;
    }

    JsonArray::JsonArray(std::vector<JsonNode*> nElements)
    {
        type = JsonNodeType::Array;
        elements = nElements;
    }

    JsonArray::~JsonArray()
    {
        for (auto element : elements)
            delete element;
    }

    JsonString::JsonString(std::string nValue)
    {
        type = JsonNodeType::String;
        value = nValue;
    }

    JsonNumberFloat::JsonNumberFloat(float nValue)
    {
        type = JsonNodeType::NumberFloat;
        value = nValue;
    }

    JsonNumberInt::JsonNumberInt(int64_t nValue)
    {
        type = JsonNodeType::NumberInt;
        value = nValue;
    }

    JsonBool::JsonBool(bool nValue)
    {
        type = JsonNodeType::Bool;
        value = nValue;
    }
}