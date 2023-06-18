#include "string.h"
#include "generic-field.h"
#define RANGE 2

class Ip : public GenericField {
	unsigned int range[RANGE];
	int kind;
public:
    Ip(String pattern);
    bool set_value(String value);
    bool match(String packet);
};

