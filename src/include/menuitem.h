#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <vector>

using namespace std;

class cMenuItem
{
    public:
        cMenuItem();
        string name;
        int actionid;
        virtual ~cMenuItem();
        vector<cMenuItem> menuitems;
    protected:
    private:
};

#endif // MENUITEM_H
