#ifndef operation_HEADER
#define operation_HEADER

#include <iostream>

class Operation {
    protected :
        std::string name;
    public :
        virtual bool execute () = 0;
        void s_name (std::string name);
        std::string g_name ();
};

#endif
