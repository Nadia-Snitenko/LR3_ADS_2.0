#include <iostream>
#include <vector>
#include <list>

//#include <algorithm>

using namespace std;

class Edge {           // ребро - путь/дорога
	string destination; // пункт назначения
	double length;
	bool type;         // 0 - асфальт, 1 - грунт;
	bool payment;      //0 - бесплатно, 1 - платно

public:
	Edge() : destination(""), length(0.0), type(0), payment(0) {}
	Edge(const string& _dest, const double& _length, const bool& _payment, const bool& _type) :destination(_dest), length(_length), type(_type), payment(_payment) {}
	Edge(const Edge& temp) {
		destination = temp.destination;
		length = temp.length;
		type = temp.type;
		payment = temp.payment;
	}
	~Edge() {}

	string get_destination() const { return destination; }
	double get_length()  const { return length; }
	bool get_type()  const { return type; }
	bool get_payment()  const { return payment; }

	Edge& operator =(const Edge& temp) {
		if (this == &temp) return *this;
		this->destination = temp.destination;
		this->length = temp.length;
		this->payment = temp.payment;
		this->type = temp.type;
		return *this;
	}

};

class Vertex { // вершина - населенный пункт
	//size_t number;
	string name;
	size_t population;
	
	list<Edge> edgelist;
public:
	Vertex(): name(""),population(0){}
	Vertex(const string& _name, const size_t _population) : name(_name), population(_population) {}

	Vertex(const Vertex& temp){
		name = temp.name;
		population = temp.population;
	}

	~Vertex() {}

	string get_name() const { return name; }
	int get_people_count() const { return population; }
	list<Edge> get_edgelist() const { return edgelist; }

	Vertex& operator=(const Vertex& temp){
		if (this == &temp) return *this;
		name = temp.name;
		population = temp.population;
		return *this;
	}	
};




class Graph {
	vector<Vertex> vertices;
public:
	Graph() {}
	 ~Graph() {}
};

int main() {
	Graph G1;
}

