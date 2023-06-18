#include "string.h"
#include "generic-field.h"
#define RANGE 2
class Port : public GenericField{
	int range[RANGE];
	int kind;
public:
	Port(String type);
	bool set_value(String value);
	bool match(String packet) ;
};

