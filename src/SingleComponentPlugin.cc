#include "SingleComponentPlugin.hh"

using namespace g4;
using namespace std;

const vector<string> SingleComponentPlugin::GetAvailableComponents() const
{
    return vector<string> { "default" };
}

Component *SingleComponentPlugin::GetComponent(const string&name)
{
    if (name == "default")
    {
        return this;
    }
    else
    {
        return nullptr;
    }
}
