/*
 * Name.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef NAME_H_
#define NAME_H_

#include "m3u8/Common.h"

class NameBase
{
public:
	NameBase(){};
	virtual ~NameBase(){};
	virtual std::string get_content()
	{
		return 0;
	};
	virtual bool empty()
	{
		return true;
	}
};


template<class T>
class Name : public NameBase
{
	T id;
	std::ostringstream oss;

public:
	Name(T name): id(name){};
    ~Name() {};

	std::string get_content() {
		oss.str("");
		oss << id;
		return oss.str();
	}
	bool empty()
	{
		return false;
	}
};

#endif /* NAME_H_ */
