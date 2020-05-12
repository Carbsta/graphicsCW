#pragma once

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "../Shared/Shapes.h"
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Tree :
	public DisplayableObject
{
public:
	Tree();
	Tree(GLuint _leafid, GLuint _barkid);
	~Tree();
	void Display();
	void addReplaceString(char flag, string str);
	void setReplaceString(char flag, string str);
	void setNumIter(unsigned int num);
	void setInitString(string str);
private:
	string sequence = "ff-[-& f + ff + < + fl] + [+>f--f&-fl]"; // default tree
	float angle = 22.5f;
	void branch();                          // draw branch function
	void leaves();
	void getSequence();
	int iter = 2;
	string init = "f";
	vector<string> change;
	vector<char> flags;
	GLuint leaf = -1;
	GLuint bark = -1;
	bool toBark = false;
	bool toLeaf = false;
};

