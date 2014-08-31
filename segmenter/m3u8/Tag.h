/*
 * Tag.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef TAG_H_
#define TAG_H_

#include "Common.h"

class Tag {
	std::string id;
	std::string output_format;
	std::list<Property *> properties;

public:
	//Tag(const Tag &t): id(t.id), output_format(t.output_format), properties(t.properties){};
	Tag(std::string name):id(name)
	{
		if(id == "M3U" || id == "INF")
			output_format = std::string("#EXT");
		else
			output_format = std::string("#EXT-X-");
	};

	std::string get_name()
	{
		return id;
	}

	std::string marshall()
	{
		std::ostringstream oss;
		oss.str("");
		oss << output_format << id;

		if(properties.size() > 0)
			oss << ":";

		for(auto it = properties.begin(), ite= properties.end(); it != ite ;)
		{
			if((*it)->get_name() != NULL)
				oss << (*it)->get_name()->get_content();
			if((*it)->get_value() != NULL)
			{
				oss << "=";
				oss << (*it)->get_value()->get_content();
			}
			it++;
			if(it != ite)
				oss << ",";
		}
		return oss.str();
	}

	template<typename T>
	void add_property(T str)
	{
		Name<T>* name = new Name<T>(str);
		properties.push_back(new Property(name));
	}
	template<typename T1, typename T2>
	void add_property(T1 str, T2 val)
	{
		Name<T1>* name = new Name<T1>(str);
		Name<T2>* value = new Name<T2>(val);
		properties.push_back(new Property(name, value));
	}

	template<typename T>
	void delete_property(T str)
	{
		Name<T>* name = new Name<T>(str);
		for(auto it = properties.begin(), ite= properties.end(); it != ite ;it++)
		{
			if((*it)->get_name()->get_content() == name->get_content()){
				properties.erase(it);
				break;
			}
		}
		delete name;
	}


	template<typename T1, typename T2>
	void mod_property(T1 str, T2 val)
	{
		Name<T1>* name = new Name<T1>(str);
		Name<T2>* value = new Name<T2>(val);
		for(auto it = properties.begin(), ite= properties.end(); it != ite ;it++)
		{
			if((*it)->get_name()->get_content() == name->get_content()){
				(*it)->set_value(value);
				break;
			}
		}
		delete name;
	}
};


#endif /* TAG_H_ */
