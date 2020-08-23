#include "Ltrees.h"



Ltrees::Ltrees():
	pos({ 41.6022, -3.697132 ,+27.5689 }),
	theta(30),
	index(0),
	count(0),
	LOOP(5)
{
	rotate = glm::mat4(1.0f);
	maps.insert({ 'F',"FF+[+F-F-F]-[-F+F+F]" });
	create();
}
void Ltrees::create()
{
	std::string a = "F";
	for (size_t i = 0; i < 3; i++)
	{
		applyRules(a);
	}
	m = Loader::loadObject("res/cub", "res/ground.png");
	std::cout << "a" << a << std::endl;
	for (auto& var :a)
	{
		generate(var);
	}
	//m = new Mesh(&vertices[0][0], &indeces[0], &tex[0][0], &vertices[0][0],vertices.size(),indeces.size(),
		//vertices.size(), vertices.size(), new Texture("res/grass2.png"));
	
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
	//using old symbols
//F draw a line
//+ left - right
//[ push and ] pop
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
	if(r=='[')
	{
		locations.push_back(pos);
		thetas.push_back(thetacount);
	}
	else if(r==']')
	{ 
		pos = locations.back();
		locations.pop_back();
		thetacount = thetas.back();
		thetas.pop_back();
		/*rotate = glm::rotate(glm::mat4(1.0f), glm::radians(theta), glm::vec3(0, 1, 0));
		rotate = glm::rotate(rotate, glm::radians(thetacount), glm::vec3(0, 0, 1));*/
		rotate = glm::rotate(glm::mat4(1.0f), glm::radians(thetacount), glm::vec3(0, 0, 1));
		//rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 1, 0));
	}
	else if(r=='-')
	{ 
		//rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 1, 0));
		rotate = glm::rotate(rotate, glm::radians(-theta), glm::vec3(0, 0, 1));
		//rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 1, 0));
		thetacount -= theta;
	}
	else if(r=='+')
	{ 
		//rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 1, 0));
		rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 0, 1));
		//rotate = glm::rotate(rotate, glm::radians(theta), glm::vec3(0, 1, 0));
		thetacount += theta;
	}
	else if (r == 'F')
	{
		createmesh();
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
	//std::cout << thetacount<<" "<<pos.r<<" "<<pos.g<<" "<<pos.b<<std::endl;
	entities.push_back(new Entity(m, pos, glm::vec3(0, 0, glm::radians(thetacount)), 0.25f));
	//vertices.push_back(pos + glm::vec3(rotate * glm::vec4(0, 0, 0,1)));
	//vertices.push_back(pos + glm::vec3(rotate * glm::vec4(0, 1, 0,1)));
	//vertices.push_back(pos + glm::vec3(rotate * glm::vec4(1, 1, 0,1)));
	//vertices.push_back(pos + glm::vec3(rotate * glm::vec4(1, 0, 0,1)));
	pos += glm::vec3(rotate * glm::vec4(0, 1.0, 0,1));

	
	//std::cout << index << std::endl;
	//indeces.push_back(index++);//1
	//indeces.push_back(index++);//2
	//indeces.push_back(index);//2
	//indeces.push_back(index-2);//2
	//indeces.push_back(index);//1
	//indeces.push_back(++index);//3
	//index++;
	//tex.push_back(glm::vec2(-1, 1));
	//tex.push_back(glm::vec2(1, -1));
	//tex.push_back(glm::vec2(-1, -1));
	//tex.push_back(glm::vec2(1, -1));
}
