#include "/headers/CompositeCom.h"

class CompositeCom : public Commands {
    protected:
        //Commands* left;
        //Commands* right;

    public:
        CompositeCom() {}
        CompositeCom(std::string command_in) : Commands(command_in) {}
        //CompositeCom(std::string command_in, Commands* l, Commands* r) : Commands(command_in), left(l), right(r) {}
        
        bool parse();
        bool execute();
};

#endif // COMPOSITECOM_H