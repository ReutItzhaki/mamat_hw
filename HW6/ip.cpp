#include "ip.h"

enum IpCheck {LOWER=0, UPPER_IP=255, SLASH_NUM=2, UPPER_MASK=32, 
	NUM_BYTES=4, BITS_IN_BYTE=8, BIGGEST_BYTE=24};
enum Num {ALL_SECTIONS=2, FIELDS=4};
const unsigned int MAX_NUM = 0xFFFFFFFF;
#define SRC_IP "src-ip"
#define DST_IP "dst-ip"
enum Kind { SOURCE = 0, DEST = 1 };

//constructor of IP that set the kind based on the type string given
Ip::Ip(String type) : GenericField() 
{
	range[0]=0;
	range[1]=1;
	if (type.equals(SRC_IP))
	{
		kind = SOURCE;
	}
	if (type.equals(DST_IP))
	{
		kind = DEST;
	}
}

/*
 * the function gets string the represents a range of ip's.
 * the function sets this range in the range array of the Ip element 
 */
bool Ip::set_value(String val) 
{
	//if the string is empty- there is no range to set
    if (val.equals("\0"))
    {
        return false; 
    }
    int maskBits = 0;
    unsigned int ip=0;
    unsigned int value=0;
    String* maskSplit;
    String* ipSplit;
    size_t sizeMaskSplit;
    size_t sizeIp;

    //getting the num of bits of the mask
    val.split("/", &maskSplit, &sizeMaskSplit);
    if ((int)sizeMaskSplit != SLASH_NUM) {
        delete[] maskSplit;
        delete[] ipSplit;
        return false;  
    }
    maskBits = maskSplit[SLASH_NUM-1].trim().to_integer();
    //checking it the num of bits of the mask is not valid
    if (maskBits > UPPER_MASK) 
    {
        delete[] maskSplit;
        delete[] ipSplit;
        return false;  
    }

    //spliting the ip string to bytes
    maskSplit[0].split(".", &ipSplit, &sizeIp);
    if ((int)sizeIp != NUM_BYTES) 
    {
        delete[] maskSplit;
        delete[] ipSplit;
        return false;  
    }
    //converting the ip bytes into ip in hex
    unsigned int subnetMask = MAX_NUM << (UPPER_MASK - maskBits);
    for (size_t i = 0; i < NUM_BYTES; i++) {
        value = ipSplit[i].trim().to_integer();
        if (value < LOWER || value > UPPER_IP) 
        {
            delete[] maskSplit;
            delete[] ipSplit;
            return false; 
        }
        ip |= value << (BIGGEST_BYTE - (BITS_IN_BYTE * i));
    }
    ip &= subnetMask;
    unsigned int broadcastAddress  = ip | (~subnetMask);

    // setting the range
     range[0] = ip;
     range[1] = broadcastAddress;


    delete[] ipSplit;
    delete[] maskSplit;
    return true;
}
/*
 * the function gets a packet and checks if the field from the type 
 * of this Ip element matches the current ip rule
 */
bool Ip::match(String packet) 
{
	String* fields;
	size_t sizeFields = 0;
	unsigned int ip=0;
	unsigned int byte=0;
	//spliting to fields
	packet.split(",", &fields, &sizeFields);
	if ((int)sizeFields != FIELDS)
	{
		delete[] fields;
		return false;
	}	
	//finding the field from this ip type
	for (int i = 0; i < FIELDS; i++)
	{
		String* curField;
		size_t sizeCurField = 0;
		fields[i].trim().split("=", &curField, &sizeCurField);
		if ((int)sizeCurField != ALL_SECTIONS) 
		{
			delete[] fields;
			delete[] curField;
			return false;
		}

		String type = curField[0].trim();
		String value = curField[1].trim();
		
		if ((type.equals(SRC_IP) && kind==SOURCE )|| (type.equals(DST_IP) && kind == DEST))
		{		
    		String *ipSplit;
    		size_t sizeIp;
    		
    		
			value.split(".", &ipSplit, &sizeIp);
    		if ((int)sizeIp != NUM_BYTES) 
    		{
        		delete[] ipSplit;
        		delete[] fields;
        		delete[] curField;
        		return false;
        		}
    		
			for(int j=0; j<NUM_BYTES; j++)
			{
				byte =ipSplit[j].trim().to_integer();
				if (byte<LOWER || byte>UPPER_IP) 
				{
          			delete[] ipSplit;
          			delete[] fields;
          			delete[] curField;
        			return false;
            	}
				ip = (ip << BITS_IN_BYTE) | byte;
			}
			//checking if it matches to the rule
			if (ip<range[0] || ip>range[1])    		
			{
				delete[] ipSplit;
				delete[] fields;
				delete[] curField;
				return false;
  			}

    		delete[] ipSplit;
  		}
   		delete[] curField;
    }
    delete[] fields;
    return true;
   }
