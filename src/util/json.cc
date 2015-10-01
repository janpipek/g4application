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
                string message = string("JSON file does not exist: ") + path;
                G4Exception("parseJsonFile", "FileNotExisting", FatalException, message.c_str());
            }
            try
            {

                string content(
                    (std::istreambuf_iterator<char>(file) ),
                    (std::istreambuf_iterator<char>()    )
                );

                shared_ptr<Json::Value> root(new Json::Value);
                Json::Reader reader;

                reader.parse(content, *root);
                return root;
            }
            catch (std::runtime_error& err)
            {
                string message = string("Cannot parse JSON file: ") + path;
                G4Exception("parseJsonFile", "CannotParse", FatalException, message.c_str());
            }
        }
    }
}
