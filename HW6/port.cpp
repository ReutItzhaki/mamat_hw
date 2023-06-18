#include "port.h"

enum Bounds { LOWER_BOUND = 0, UPPER_BOUND = 65535 };
enum Num { FIELDS = 4};
#define SRC_PORT "src-port"
#define DST_PORT "dst-port"
enum Kind { SOURCE = 0, DEST = 1 };

//constructor of port that set the kind based on the type string given
Port::Port(String type) : GenericField()
{
	range[0]=0;
	range[1]=1;
	if(type.equals(SRC_PORT))
	{
		kind=SOURCE;
	}
	if(type.equals(DST_PORT))
	{
		kind=DEST;
	}
}

/*
 * the function gets string the represents a range of ports.
 * the function sets this range in the range array of the port element 
 */
bool Port::set_value(String val) 
{
	//if the string is empty- there is no range to set
    if (val.equals("\0"))
    {
        return false; 
    }
	String* output;
	size_t size = 0;
	//spliting to the port range
	val.split("-", &output, &size);

	if ((int)size != RANGE) 
	{
		delete[] output;
		return false;
	}
	//defining the range and checking if valid
	for(int i=0;i<RANGE;i++)
	{
		range[i]=output[i].trim().to_integer();
		if (range[i] < LOWER_BOUND || range[i] > UPPER_BOUND)
		{
			delete[] output;
			return false;
		}
	}
	//chacking if range is valid from small to big
	if (range[0] > range[1]) 
	{
		delete[] output;
		return false;
	}
		delete[] output;
		return true;
}
/*
 * the function gets a packet and checks if the field from the type 
 * of this Port element matches the current port rule
 */
bool Port::match(String packet) 
{
	String* fields;
	size_t sizeFields = 0;
	//spliting to fields
	packet.split(",", &fields, &sizeFields);
	if ((int)sizeFields != FIELDS)
	{
		delete[] fields;
		return false;
	}
	//finding the field from this port type
	for (int i = 0; i < FIELDS; i++)
	{
		String* curField;
		size_t sizeCurField = 0;
		fields[i].trim();
		fields[i].split("=", &curField, &sizeCurField);
		if ((int)sizeCurField != RANGE) 
		{
			delete[] fields;
			delete[] curField;
			return false;
		}

		String type = curField[0].trim();
		int val = curField[1].trim().to_integer();
		if ((type.equals(SRC_PORT) && kind == SOURCE) || (type.equals(DST_PORT) && kind == DEST))
		{
			//checking if it matches to the rule
			if(val < range[0] || val > range[1])
			{
				delete[] fields;
				delete[] curField;
				return false;
			}	
		}
		delete[] curField;
	}
	delete[] fields;	
 return true;
}
