#include "util/json.hh"

#include <fstream>
#include <stdexcept>

using namespace std;

namespace g4
{
    namespace util
    {
        shared_ptr<Json::Value> parseJsonFile(const std::string& path)
        {
            ifstream file(path);
            if (!file)
            {
                // TODO: G4Exception?
                throw runtime_error(string("File does not exist: ") + path);
            }
            string content(
                (std::istreambuf_iterator<char>(file) ),
                (std::istreambuf_iterator<char>()    )
            );

            shared_ptr<Json::Value> root(new Json::Value);
            Json::Reader reader;
            
            reader.parse(content, *root);
            return root;
        }
    }
}