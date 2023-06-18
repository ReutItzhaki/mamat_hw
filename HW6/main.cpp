
#include "port.h"
#include "ip.h"
#include "input.h"

enum Result { SUCCESS = 0,FAIL = 1 };
enum SPLITS {TWO = 2};
#define SRC_IP "src-ip"
#define DST_IP "dst-ip"
#define SRC_PORT "src-port"
#define DST_PORT "dst-port"

int main(int argc, char** argv)
{
	if (check_args(argc, argv))
	{
		return FAIL;
	}
	String field(argv[1]);
	String* output;
	size_t size = 0;
	String str;
	//spliting the rule to type and value
	field.split("=", &output, &size);

	if (size != TWO)
	{
		delete[] output;
		return FAIL;
	}

	String fieldType(output[0].trim());
	if (fieldType.equals(SRC_IP) || fieldType.equals(DST_IP))
	{
		//defining the ip rule
		Ip myIp(output[0].trim());
		if (!myIp.set_value(output[1].trim()))
		{
			delete[] output;
			return FAIL;
		}
		//printing all the packets that matches the rule
		parse_input(myIp);
	}
	else if (fieldType.equals(SRC_PORT) || fieldType.equals(DST_PORT))
	{
		//defining the port rule
		Port myPort(output[0].trim());
		if (!myPort.set_value(output[1].trim()))
		{
			delete[] output;
			return FAIL;
		}
		//printing all the packets that matches the rule
		parse_input(myPort);
	}
	else
	{
		delete[] output;
		return FAIL;
	}

	delete[] output;
	return SUCCESS;
}
