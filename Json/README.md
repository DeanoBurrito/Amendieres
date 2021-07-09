# JSON Parser
This folder contains a super simple json parser I wrote, that eventually morphed into the rest of this project.
All the files you need are:
JsonNode(.h|.cpp), JsonParser(.h|.cpp) and JsonToken.h
There is reference to a Debug.h, which contains some macros I use for debugging. If you *just want the damn json parser and thats it*,
I totally understand and you can `#define AMENDIERES_JSON_STANDALONE` at the top of the file or `-DAMENDIERES_JSON_STANDALONE` when you compile JsonParser.cpp.

There's other stuff in here thats been added to this project, but its not necessary for the parsing.
It's under the same license as the rest of the code here. Please feel free to use it! 
:)