#include "Ltrees.h"
#include "gtx/normal.hpp"


Ltrees::Ltrees() :
	pos({ 0, 0 ,0 }),
	theta(20),
	index(0),
	count(0),
	LOOP(5)
{
	rotate = glm::mat4(1.0f);
	//maps.insert({ 'F',"FF+[+F-F-F]-[-F+F+F]" });
	//axiom = "A"
	//	productions = { 'A': '[&FLA]/////[&FLA]///////`[&FLA]',
	//						'F' : 'S ///// F',
	//						'S' : 'F',
	//						'L' : '[Q^^Q][Q\\\\Q]' }
	//maps.insert({ 'F',"FF" });
	//maps.insert({ 'X',"F+[[X]-X]-F[-FX]+X" });
	//	maps.insert({ 'F',"FF+[+F-F-F]-[-F+F+F]" });
	me = Loader::loadObject("res/leaf2", "res/grass.png");
	maps.insert({ 'A', "[&FLA]/////[&FLA]///////[&FLA]" });
	maps.insert({ 'F', "S/////F" });
	maps.insert({ 'S', "F" });
	maps.insert({ 'L', "[Q^^Q][Q\\\\Q]" });

	/* Palm
	*
	*  axiom "a'12b"
  rules
  [ "a=a&~xf"
	"b=15\[16&cA]"
	"c=c2&"
	"A=F[12+B]8&[A][12-B]"
	"B=F8&B"

	*/
	//maps.insert({'a', "avf"});
	//maps.insert({ 'b', "\\\\\\\\\\\\\\\[&&&&&&&&&&&&&&&&cA]" });
	//maps.insert({ 'c', "c&&" });
	//maps.insert({ 'A', "F[++++++++++++B]8&[A][------------B]" });
	//maps.insert({ 'B', "F8&B" });
	//maps.insert({ 'A', "B-F+CFC+F-D&F^D-F+&&CFC+F+B//" });
	//		maps.insert({ 'B', "A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//" });
	//		maps.insert({'C', "|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//" });
	//		maps.insert({'D', "|CFB-F+B|FA&F^A&&FB-F+B|FC//" });

	create();
	
	glm::vec3* normals = new glm::vec3[vertices.size()];
	memset(normals, 0, sizeof(glm::vec3) * vertices.size());
	for (int i=0; i < indeces.size(); i=i+3)
	{
		 unsigned int ia = indeces[i];
		 unsigned int ib = indeces[i + 1];
		 unsigned int ic = indeces[i + 2];
						
		 glm::vec3 no = glm::triangleNormal(vertices[ia], vertices[ib], vertices[ic]);

		normals[ia] += no;
		normals[ib] += no;
		normals[ic] += no;
	}
	m = new Mesh(&vertices[0][0], &indeces[0], &tex[0][0], &normals[0][0], (unsigned int)vertices.size(), (unsigned int)indeces.size(),
		(unsigned int)vertices.size(), (unsigned int)vertices.size(), new Texture("res/ground.png"));
	entities.push_back(new Entity(m, glm::vec3(55.9028,  -3.03539 , 50), glm::vec3(0, 0, 0), 1.0f));
}
void Ltrees::create()
{
	//std::string a = "abbbbbbbbbbbb";
	std::string a = "A";

	for (size_t i = 0; i < 8; i++)
	{
		applyRules(a);
	}

	std::cout << "a" << a << std::endl;
	for (auto& var : a)
	{
		generate(var);
	}

}

Mesh* Ltrees::returnMesh()
{
	return m;
}

std::vector<Entity*> Ltrees::returnEntity()
{
	return entities;
}

void Ltrees::applyRules(std::string& rules)
{
	std::string test = "";
	for (auto& i : rules)
	{
		if (maps.find(i) == maps.end())
		{
			test += i;
			continue;
		}
		else
		{
			test += maps[i];
		}
	}
	rules = test;
}

void Ltrees::generate(char r)
{
	if (r == '[')
	{

		locations.push_back(pos);
		thetas.push_back(n);
		location.push_back(rotate);
		sizes.push_back(size);
	}
	else if (r == ']')
	{
		pos = locations.back();
		locations.pop_back();
		rotate = location.back();
		location.pop_back();
		n = thetas.back();
		size = sizes.back();
		sizes.pop_back();
		thetas.pop_back();
		;
	}
	else if (r == '-')
	{
		rotate = glm::rotate(rotate, glm::radians(-theta), glm::vec3(0, 0, 1));
		//size -= .1510f;
	}
	else if (r == '+')
	{
		rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 0, 1));
		//size -= .1510f;
	}
	else if (r == '/')
	{
		rotate = glm::rotate(rotate, glm::radians(-theta), glm::vec3(0, 1, 0));
		//size -= .1510f;
	}
	else if (r == '\\')
	{
		rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 1, 0));
		//size -= .1510f;
	}
	else if (r == '^')
	{
		rotate = glm::rotate(rotate, glm::radians(-theta), glm::vec3(1, 0, 0));
		//size -= .1510f;
	}
	else if (r == '&')
	{
		rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(1, 0, 0));
		//size -= .1510f;
	}
	else if (r == 'F')
	{
		size *= .95910f;
		createmesh();
	}
	else if (r == 'v')
	{
		size = 0.6;
		
		createmesh();
	}
	else if (r == 'f')
	{
		//size *= .85910f;
		pos += glm::vec3(rotate * glm::vec4(0, 1, 0, 1));
		//createmesh();
	}
	else if (r == 'Q')
	{
		entities.push_back(new Entity(me, pos + glm::vec3{55.9028, -3.03539,51.0}, glm::vec3(0, 0, thetacount), 0.425f));
		thetacount = (float)rand() / (float)RAND_MAX * 3.14;
	}
	else
	{

	}

}

void Ltrees::drawtubes(glm::mat2x2 transform, glm::vec3 position)
{
}

void Ltrees::createmesh()
{
	pos += glm::vec3(rotate * glm::vec4(0, 1, 0, 1));

	if (vertices.empty())
	{

		vertices.push_back({ 1.000000, 1.000000, -1.000000 });
		tex.push_back({ 0.625,0.5 });

		vertices.push_back({ 1.000000,-1.000000, -1.000000 });
		tex.push_back({ 0.375, 0.5 });

		vertices.push_back({ 1.000000,1.000000, 1.000000 });
		tex.push_back({ 0.625, 0.75 });

		vertices.push_back({ 1.000000,-1.000000, 1.000000 });
		tex.push_back({ 0.375, 0.75 });

		vertices.push_back({ -1.000000,1.000000, -1.000000 });
		tex.push_back({ 0.625,0.25 });

		vertices.push_back({ -1.000000,-1.000000, -1.000000 });
		tex.push_back({ 0.375,0.25 });

		vertices.push_back({ -1.000000,1.000000, 1.000000 });
		tex.push_back({ 0.625,0 });


		vertices.push_back({ -1.000000,-1.000000, 1.000000 });
		tex.push_back({ 0.125 ,0.75 });

		vertices.push_back({ 1.000000, 2, 1.000000 });
		tex.push_back({ 0.625, 0.75 });

		vertices.push_back({ -1.000000, 2, 1.000000 });
		tex.push_back({ 0.625, 0 });

		vertices.push_back({ 1.000000, 2, -1.000000 });
		tex.push_back({ 0.625, 0.5 });

		vertices.push_back({ -1.000000, 2, -1.000000 });
		tex.push_back({ 0.625, 0.25 });

		indeces = { 2,6,7,
					6,4,5,
					1,3,7,
					0,2,3,
					4,0,1,
					2,7,3,
					6,5,7,
					1,7,5,
					0,3,1,
					4,1,5,
					6,11,4,
					0,8,2,
					4,10,0,
					2,9,6,
					6,9,11,
					0,10,8,
					4,11,10,
					2,8,9 };

		n = vertices.size();
	}
	else
	{

		if (size < 0.05)
		{
			size = 0.05;
		}

		vertices.push_back(pos + glm::vec3(1.0 * size, 1.0 * size, 1.0 * size));
		tex.push_back({ 0.625, 0.75 });

		vertices.push_back(pos + glm::vec3(-1.0 * size, 1.0 * size, 1.0 * size));
		tex.push_back({ 0.625, 1 });

		vertices.push_back(pos + glm::vec3(1.0 * size, 1.0 * size, -1.0 * size));
		tex.push_back({ 0.625, 0.5 });

		vertices.push_back(pos + glm::vec3(-1.0 * size, 1.0 * size, -1.0 * size));
		tex.push_back({ 0.625, 0.25 });

		unsigned int n2 = vertices.size();

		indeces.insert(indeces.end(), {
			n - 3, n2 - 3, n2 - 1,
			n - 4, n2 - 4, n2 - 3,
			n - 1, n2 - 1, n2 - 2,
			n - 2, n2 - 2, n2 - 4,
			n - 3, n2 - 1, n - 1,
			n - 1, n2 - 2, n - 2,
			n - 4, n2 - 3, n - 3,
			n - 2, n2 - 4, n - 4
			});
		n = n2;
	}

}
