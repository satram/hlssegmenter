/*
 * Section.h
 *
 *  Created on: Jul 31, 2014
 *      Author: satram
 */

#ifndef SECTION_H_
#define SECTION_H_

#include "m3u8/Tag.h"

class Section {
	std::list<Tag> tags;

	std::string path;
	std::string locator;
	std::string id;

public:
	Section(std::string name):id(name){};
	virtual ~Section(){};

//	//copy assignemnt
//	Section & operator=(const Section &other) = default;
//
//	//copy constructors
//	//Section(const Section &s):tags(s.tags), path(s.path), locator(s.locator),id(s.id){};
//	Section(const Section &s) = default;

	//move constructors


	std::string get_name()
	{
		return id;
	};

	std::string marshall()
	{
		std::ostringstream oss;
		oss.str("");
		for(auto it = tags.begin(), ite = tags.end(); it != ite; it++)
			oss << it->marshall() << "\n";
		if(!path.empty())
			oss << path;
		if(!path.empty() && path.find_last_of("/") != (path.size()-1))
			oss << "/";
		if(!locator.empty())
			oss << locator << "\n";
		oss << "\n";
		return oss.str();
	};
	void set_path(const char *p)
	{
		path = std::string(p);
	};
	void set_path(std::string &p)
	{
		path = p;
	};
	void set_locator(const char *l)
	{
		locator = std::string(l);
	};
	void set_locator(std::string l)
	{
		locator = l;
	};
	void add_tag(Tag &t){
		tags.push_back(t);
	};

	template<typename T>
	void add_tag(T str)
	{
		Tag t(str);
		tags.push_back(t);
	};

	template<typename T1, typename T2>
	void add_tag(T1 str, T2 name)
	{
		Tag t(str);
		t.add_property(name);
		tags.push_back(t);
	};
	template<typename T1, typename T2, typename T3>
	void add_tag(T1 str, T2 name, T3 val)
	{
		Tag t(str);
		t.add_property(name, val);
		tags.push_back(t);
	};


	template<typename T1, typename T2>
	void modify_tag(T1 str, T2 name)
	{
		Tag t(str);
		t.add_property(name);
		for(auto it = tags.begin(), ite = tags.end(); it != ite; it++)
		{
			if(it->get_name() == t.get_name())
			{
				it = tags.erase(it);
				tags.insert(it, t);
				break;
			}
		}
	};

	template<typename T1, typename T2, typename T3>
	void modify_tag(T1 str, T2 name, T3 val)
	{
		Tag t(str);
		t.add_property(name, val);
		for(auto it = tags.begin(), ite = tags.end(); it != ite; it++)
			if(it->get_name() == t.get_name())
			{
				it = tags.erase(it);
				tags.insert(it, t);
				break;
			}

	};

};

#endif /* SECTION_H_ */
