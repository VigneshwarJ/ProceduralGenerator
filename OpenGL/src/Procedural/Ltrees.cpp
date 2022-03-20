#include "Ltrees.h"
#include "gtx/normal.hpp"
#include "../Scenegraph/geometry/PolygonalGeometry.h"
#include "../Scenegraph/material/DiffuseMaterial.h"


Ltrees::Ltrees(int loop) :
	pos({ 0, 0 ,0 }),
	theta(20),
	index(0),
	LOOP(loop),
	count(0)
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


	//leaves = Loader::loadObject("res/leaf2", "res/grass.png");
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

	for (int i = 0; i < indeces.size(); i = i + 3)
	{
		unsigned int ia = indeces[i];
		unsigned int ib = indeces[i + 1];
		unsigned int ic = indeces[i + 2];

		glm::vec3 no = glm::triangleNormal(vertices[ia].mPosition, vertices[ib].mPosition, vertices[ic].mPosition);

		vertices[ia].mNormal += no;
		vertices[ia].mNormal += no;
		vertices[ia].mNormal += no;
	}


	//m = new Mesh(&vertices[0][0], &indeces[0], &tex[0][0], &normals[0][0], (unsigned int)vertices.size(), (unsigned int)indeces.size(),
	//	(unsigned int)vertices.size(), (unsigned int)vertices.size(), new Texture("res/ground.png"));
	//entities.push_back(new Entity(m, glm::vec3(55.9028,  -3.03539 , 50), glm::vec3(0, 0, 0), 1.0f));
}
SceneItemSharedPtr Ltrees::returnMesh()
{

	std::vector<glm::vec4>* color = new std::vector<glm::vec4>(vertices.size());
	std::fill(color->begin(), color->end(), glm::vec4(0, 1, 0, 1));
	PolygonalGeometrySharedPtr triangle = std::make_shared<PolygonalGeometry>();

	triangle->setPrimitiveType(PG_TRIANGLES);
	triangle->setVertices(vertices.data(),
		vertices.size());
	triangle->setIndices(indeces.data(),
		indeces.size());

	DiffuseMaterialSharedPtr diffuse_material
		= std::make_shared<DiffuseMaterial>();
	diffuse_material->setColorPerVertex(color->data(),
		color->size());
	triangle->setMaterial(diffuse_material);
	return triangle;
}
void Ltrees::create()
{
	//std::string a = "abbbbbbbbbbbb";
	std::string a = "A";

	for (size_t i = 0; i < 8; i++)
	{
		applyRules(a);
	}

	for (auto& var : a)
	{
		generate(var);
	}

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
		size = 0.6f;

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
		// leaves can be added
		thetacount = (float)rand() / (float)RAND_MAX * 3.14f;
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

		vertices.push_back({ { 1.000000, 1.000000, -1.000000 }, { 0.625,0.5 }, {0.0f,0.0f,0.0f} });

		vertices.push_back({ { 1.000000,-1.000000, -1.000000 }, { 0.375, 0.5 }, {0.0f,0.0f,0.0f} });

		vertices.push_back({ { 1.000000,1.000000, 1.000000}, {0.625, 0.75 }, {0.0f,0.0f,0.0f} });

		vertices.push_back({ { 1.000000,-1.000000, 1.000000 }, { 0.375, 0.5 }, {0.0f,0.0f,0.0f} });

		vertices.push_back({ { -1.000000,1.000000, -1.000000 }, { 0.625,0.25 }, {0.0f,0.0f,0.0f} });


		vertices.push_back({ { -1.000000,-1.000000, -1.000000 }, { 0.375, 0.25 }, {0.0f,0.0f,0.0f} });


		vertices.push_back({ { -1.000000,1.000000, 1.000000 }, { 0.625,0 }, {0.0f,0.0f,0.0f} });


		vertices.push_back({ { -1.000000,-1.000000, 1.000000 }, {0.125 ,0.75}, {0.0f,0.0f,0.0f} });


		vertices.push_back({ {  1.000000, 2, 1.000000 }, {0.625, 0.7 }, {0.0f,0.0f,0.0f} });
		;

		vertices.push_back({ { -1.000000, 2, 1.000000 }, { 0.625, 0 }, {0.0f,0.0f,0.0f} });


		vertices.push_back({ { 1.000000, 2, -1.000000 }, { 0.625, 0.5 }, {0.0f,0.0f,0.0f} });

		vertices.push_back({ { -1.000000, 2, -1.000000 }, { 0.625, 0.25  }, {0.0f,0.0f,0.0f} });


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

		n = static_cast<uint32_t>(vertices.size());
	}
	else
	{

		if (size < 0.05)
		{
			size = 0.05f;
		}

		vertices.push_back({ pos + glm::vec3(1.0 * size, 1.0 * size, 1.0 * size),
		{ 0.625, 0.75 }, {0.0f,0.0f,0.0f}
			});

		vertices.push_back({ pos + glm::vec3(-1.0 * size, 1.0 * size, 1.0 * size),
		{ 0.625, 1 }, {0.0f,0.0f,0.0f}
			});

		vertices.push_back({ pos + glm::vec3(1.0 * size, 1.0 * size, -1.0 * size),
		{ 0.625, 0.5 }, {0.0f,0.0f,0.0f}
			});

		vertices.push_back({ pos + glm::vec3(-1.0 * size, 1.0 * size, -1.0 * size),
		{ 0.625, 0.25 }, {0.0f,0.0f,0.0f}
			});


		uint32_t n2 = static_cast<uint32_t>(vertices.size());

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
