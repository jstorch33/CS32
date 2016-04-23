#include "provided.h"
#include "http.h"
#include <string>
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
    string text;
    if (!HTTP().get(url, text))
        return false;
    
    Steg::hide(text, msg, host);
    HTTP().set(url, host);
    return true;
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
    string text;
    if (!HTTP().get(url, text))
        return false;
    
    Steg::reveal(text, msg);
    return true;
}
