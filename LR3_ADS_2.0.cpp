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
	int population;

public:
	locality() {
		name = "unknown";
		population = 0;
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


