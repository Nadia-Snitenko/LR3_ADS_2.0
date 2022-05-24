#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
	size_t count;
	vector<list<TVertex>> adj;
public:
	Graph() {
		count = 0;
	}
};

class locality {
	string name;
	size_t population;

public:
	locality() {
		name = "unknown";
		population = 0;
	}
	locality(const string& _name, const size_t _population) : name(_name), population(_population) {}

	locality(const locality& rhs){
		name = rhs.name;
		population = rhs.population;
	}

	string GetName() const { return name; }
	int GetPeopleCount() const { return population; }

	locality& operator=(const locality& rhs){
		if (this == &rhs) return *this;
		name = rhs.name;
		population = rhs.population;
		return *this;
	}	
};

struct TVertex {
	locality a;
	TVertex* next;
	TEdge* c;

	TVertex() {
		locality();
		next = nullptr;
		c = nullptr;
	}
};

struct TEdge {
	double length;
	bool type;// 0 - асфальт, 1 - грунт;
	bool payment;
};

int main() {

}

