/*
 * Property.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "m3u8/Name.h"

class Property
{
	NameBase *name;
	NameBase *value;
public:
	Property(NameBase *input): name(input)
	{
		value = NULL;
	};
	Property(NameBase *input1, NameBase *input2): name(input1),value(input2)
	{
	};
	~Property()
	{
		delete name;
		delete value;
	};
	NameBase* get_name()
	{
		return name;
	}
	NameBase* get_value()
	{
		return value;
	}
	void set_value(NameBase *newval)
	{
		delete value;
		value = newval;
	}
};


#endif /* PROPERTY_H_ */
