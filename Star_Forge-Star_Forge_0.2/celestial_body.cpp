#include "celestial_body.hpp"

//Vector section
Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(double a, double b)
{
	x = a;
	y = b;
}

void Vector::set()
{
	x = 0;
	y = 0;
}

void Vector::set(double a)
{
	x = a;
}

void Vector::set(double a, double b)
{
	x = a;
	y = b;
}

Vector Vector::operator +(Vector b)
{
	Vector c;
	c.x = x + b.x;
	c.y = y + b.y;
	return c;
}

Vector Vector::operator -(Vector b)
{
	Vector c;
	c.x = x - b.x;
	c.y = y - b.y;
	return c;
}

double Vector::abs(Vector a)
{
	return (a.x * a.x)+(a.y * a.y);
}
//Phase_vector section
Phase_vector::Phase_vector()
{
	x = 0;
	y = 0;
	v_x = 0;
	v_y = 0;
}
Phase_vector::Phase_vector(double a, double b, double c, double d)
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
}

Phase_vector::Phase_vector(double a, double b)
{
	x = a;
	y = b;
	v_x = 0;
	v_y = 0;
}
Phase_vector Phase_vector::operator *(double a)
{
	Phase_vector res = Phase_vector();
	res.x = x * a;
	res.y = y * a;
	res.v_x = v_x * a;
	res.v_y = v_y * a;
	return res;
}
Phase_vector Phase_vector::operator /(double a)
{
	Phase_vector res = Phase_vector();
	res.x = x / a;
	res.y = y / a;
	res.v_x = v_x / a;
	res.v_y = v_y / a;
	return res;
}
Phase_vector Phase_vector::operator +(Phase_vector a)
{
	Phase_vector res = Phase_vector();
	res.x = x + a.x;
	res.y = y + a.y;
	res.v_x = v_x + a.v_x;
	res.v_y = v_y + a.v_y;
	return res;
}
Phase_vector Phase_vector::operator -(Phase_vector a)
{
	Phase_vector res = Phase_vector();
	res.x = x - a.x;
	res.y = y - a.y;
	res.v_x = v_x - a.v_x;
	res.v_y = v_y - a.v_y;
	return res;
}
//Celestial_body section
Celestial_Body::Celestial_Body()
{
	x = 0;
	y = 0;
	v_x = 0;
	v_y = 0;
	w_x = 0;
	w_y = 0;
	Radius = 0;
	Mass = 0;
	texture_path = "";
}

Celestial_Body::Celestial_Body(const Celestial_Body& other)
{
	x = other.x;
	y = other.y;
	v_x = other.v_x;
	v_y = other.v_y;
	w_x = other.w_x;
	w_y = other.w_y;
	Radius = other.Radius;
	Mass = other.Mass;
}

Celestial_Body::Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k, std::string t, std::string name)//добавленный конструктор
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
	w_x = e;
	w_y = f;
	Radius = g;
	Mass = k;
	texture_path = t;
	body_name = name;
}

Celestial_Body::Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k)
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
	w_x = e;
	w_y = f;
	Radius = g;
	Mass = k;
	texture_path = "_";
}

Celestial_Body Celestial_Body::operator +(Phase_vector a)
{
	Celestial_Body res = Celestial_Body(x, y, v_x, v_y, w_x, w_y, Radius, Mass);
	res.x+=a.x;
	res.y+=a.y;
	res.v_x+=a.v_x;
	res.v_y+=a.v_y;
	return res;
}

Celestial_Body Celestial_Body::operator +=(Phase_vector a)
{
	x+=a.x;
	y+=a.y;
	v_x+=a.v_x;
	v_y+=a.v_y;
	return *this;
}

Celestial_Body Celestial_Body::operator -(Phase_vector a)
{
	Celestial_Body res = Celestial_Body(x, y, v_x, v_y, w_x, w_y, Radius, Mass);
	res.x-=a.x;
	res.y-=a.y;
	res.v_x-=a.v_x;
	res.v_y-=a.v_y;
	return res;
}

Celestial_Body Celestial_Body::operator =(Celestial_Body a)
{
	x = a.x;
	y = a.y;
	v_x = a.v_x;
	v_y = a.v_y;
	Radius = a.Radius;
	Mass = a.Mass;
	return *this;
}

Celestial_Body Celestial_Body::operator =(Celestial_Body *a) //added by Nestor
{
	x = a->x;
	y = a->y;
	v_x = a->v_x;
	v_y = a->v_y;
	Radius = a->Radius;
	Mass = a->Mass;  
	texture_path = a->texture_path;
	body_name = a->body_name;
	return *this;
}

/*int Celestial_Body::operator ==(Celestial_Body a)
{
	if ((x == a.x)&&(y == a.y)&&(v_x == a.v_x)&&(v_y == a.v_y)&&(w_y == a.w_y)&&(w_y == a.w_y)&&(Radius == a.Radius)&&(Mass == a.Mass))
	return true;
	else return false;
}
int Celestial_Body::operator !=(Celestial_Body a)
{
	if ((x != a.x)||(y != a.y)||(v_x != a.v_x)||(v_y != a.v_y)||(w_y != a.w_y)||(w_y != a.w_y)||(Radius != a.Radius)||(Mass != a.Mass))
	return true;
	else return false;
}*/

//Atlas section

double x(double x_m, double scale)
{
	double res = (x_m * (scale))/(6.084e11) + scale/2;
	return res;
}

double y(double y_m, double scale)
{
	double res = scale/2 - (y_m * scale)/(6.084e11);
	return res;
}

double x_satellite(double x, Celestial_Body* a)
{
	double res = x + a->x;
	return res;
}

double y_satellite(double y, Celestial_Body* a)
{
	double res = y + a->y;
	return res;
}

double v_x_satellite(double v_x, Celestial_Body* a)
{
	double res = v_x + a->v_x;
	return res;
}

double v_y_satellite(double v_y, Celestial_Body* a)
{
	double res = v_y + a->v_y;
	return res;
}

Atlas::Atlas()
{
	first = NULL;
	last = NULL;
	active = NULL;
	amount = 0;
}

Atlas::Atlas(Celestial_Body a)
{
	Atlas_node tmp = new Atlas_node_el;
	tmp->body = a;
	tmp->next = NULL;
	sf::CircleShape avat(a.Radius);
	tmp->avatar = avat;
	first = tmp;
	last = tmp;
	active = NULL;
	amount = 1;
}

void Atlas::add(Celestial_Body* a) //changed by Nestor
{
	if (active == NULL)
	{
		Atlas_node tmp = new Atlas_node_el;
		tmp->body = a;
		tmp->next = NULL;
		sf::CircleShape avat(a->Radius);
		avat.setOrigin(a->Radius,a->Radius);
		if(a->texture_path!="_")
		{
			tmp->body.t.loadFromFile(tmp->body.texture_path);
			avat.setTexture(&(tmp->body.t));
		}
		tmp->avatar = avat;
		if(last != NULL)
		{
			last->next = tmp;
			last = last -> next;
			std::cout<<first<<"\n";
		}
		else
		{
			last = tmp;
			first = tmp;
			std::cout<<first<<" null\n";
		}
		amount++;
		return;
	}else
	{
		Atlas_node tmp = new Atlas_node_el;
		tmp->body = Celestial_Body(x_satellite(a->x, &(active->body)), y_satellite(a->y, &(active->body)), v_x_satellite(a->v_x, &(active->body)), v_y_satellite(a->v_y, &(active->body)), 0, 0, a->Radius, a->Mass);
		tmp->next = NULL;
		sf::CircleShape avat(a->Radius);
		avat.setOrigin(a->Radius,a->Radius);
		if(a->texture_path!="_")
		{
			tmp->body.t.loadFromFile(tmp->body.texture_path);
			avat.setTexture(&(tmp->body.t));
		}
		tmp->avatar = avat;
		if(last != NULL)
		{
		last->next = tmp;
		last = last -> next;
		}
		else
		{
			last = tmp;
			first = tmp;
		}
		amount++;
		return;
	}
}

/*void Atlas::remove()
{
		Atlas_node tmp = first;
		if (tmp == NULL) return;
		while (tmp -> next != active) tmp = tmp -> next;
		tmp -> next = active -> next;
		delete active;
		active = NULL;
	void remove()
	{
		object* tmp;
		object* ntr;
		tmp = first;
		if (tmp->eq == active)
		{
			if(tmp->next)set(tmp->next);
			tmp = first->next;
			delete first;
			first = tmp;
			if(counter == 1) first = NULL;
			active = NULL;
			counter--;
			return;
		}
		while (tmp->next && tmp->next->eq!=active)
		{
			tmp = tmp -> next;
		}
		if(tmp->next==last) last = tmp;
		if(tmp->next)
		{
			set(tmp->next);
			ntr=tmp->next;
		}
		else ntr->next = NULL;
		if (ntr->next) tmp->next=tmp->next->next;
		else tmp->next = NULL;
		delete ntr;
		counter--;
		active = NULL;
		sign = 0;
	}
}*/

void Atlas::remove()
{
	std::cout<<amount<<"\n";
	std::cout<<first<<"\n";
	Atlas_node tmp;
	tmp = first;
	if (tmp == active)
	{	
		tmp = first->next;
		delete active;
		first = tmp;
		if(amount == 1) first = NULL;
		active = NULL;
		amount--;
		std::cout<<first<<"\n";
		return;
	}
	while (tmp->next && tmp->next!=active)
	{
		tmp = tmp -> next;
	}
	if(tmp->next==last) last = tmp;
	if (active->next) tmp->next=active->next;
	else tmp->next = NULL;
	delete active;
	amount--;
	std::cout<<first<<"\n";
	active = NULL;
	}

void Atlas::del()
{
	Atlas_node tmp1 = first; 
	while (tmp1 != NULL)
	{
		Atlas_node tmp2 = tmp1;
		tmp1 = tmp1->next;
		delete(tmp2);
	}
}

void Atlas::out()
{
	Atlas_node tmp1 = first; 
	while (tmp1 != NULL)
	{
		std::cout<<"Atlas "<<tmp1->body<<"\n";
		tmp1 = tmp1->next;
	}
	return;
}

void draw(Atlas* atl, sf::RenderWindow* window)
{
	Atlas_node tmp = atl->first;
	while(tmp != NULL)
	{
		window->draw(tmp->avatar);
		tmp = tmp->next;
	}	
	return;
}



















