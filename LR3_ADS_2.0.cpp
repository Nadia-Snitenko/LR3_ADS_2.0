#include <iostream>
#include <vector>
#include <list>
#include <iterator>

//#include <algorithm>

using namespace std;

struct Edge {           // ребро - путь/дорога
	string destination; // пункт назначения
	double length;
	bool type;         // 0 - асфальт, 1 - грунт;
	bool payment;      //0 - бесплатно, 1 - платно


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
	string get_type()  const { if (type) return "soil"; else return "asphalt"; }
	string get_payment()  const { if (payment)return "payment"; else "free"; }

	Edge& operator =(const Edge& temp) {
		if (this == &temp) return *this;
		this->destination = temp.destination;
		this->length = temp.length;
		this->payment = temp.payment;
		this->type = temp.type;
		return *this;
	}

};

struct Vertex { // вершина - населенный пункт
	//size_t number;
	string name;
	size_t population;
	
	list<Edge> edgelist;

	Vertex(): name(""),population(0){}
	Vertex(const string& _name, const size_t _population) : name(_name), population(_population) {}

	Vertex(const Vertex& temp){
		name = temp.name;
		population = temp.population;
	}

	~Vertex() {}

	string get_name() const { return name; }
    void set_name(string _name) { name = _name; }

	size_t get_people_count() const { return population; }
    void set_people_count(size_t _population) { population = _population; }

    void set(string _name, size_t _population) { name = _name; population = _population; }
	list<Edge> get_edge_list() const { return edgelist; }

	void print_edge_list() {
		cout << "[";
		for (auto it = edgelist.begin(); it != edgelist.end(); it++) {
			cout << it->get_destination() << "(" << it->get_length() << ',' << it->get_payment()<< ',' << it->get_type() << ',' << ") --> ";
		}
		cout << "]";
		cout << endl;
	}

	void add_edge_to_edgelist(string _destination, double _length, bool _type, bool _payment){
        Edge e(_destination, _length,_type,_payment);
        edgelist.push_back(e); 
		cout<<"Edge between "<<name<<" and "<< _destination <<" added successfully"<<endl;
    }

	Vertex& operator=(const Vertex& temp){
		if (this == &temp) return *this;
		name = temp.name;
		population = temp.population;
		return *this;
	}


};

class Graph {
	vector<Vertex> vertices;
	size_t count;
public:
	Graph(): count(0) {}
	 ~Graph() {}

     bool check_if_vertex_exist_by_name(string temp) {
         for (int i = 0; i < vertices.size(); i++) {
             if (vertices.at(i).get_name() == temp) {
                 return 1;
             }
         }
         return 0;
     }

     bool check_if_edge_exist_between_vertices(string fromVertex, string toVertex) {
         Vertex v = get_vertex_by_name(fromVertex);
         list < Edge > e;
         e = v.get_edge_list();
         for (auto it = e.begin(); it != e.end(); it++) {
             if (it->get_destination() == toVertex) {
                 return 1;
             }

         }
         return 0;
     }

     Vertex get_vertex_by_name(string _temp) {
         Vertex temp;
         for (int i = 0; i < vertices.size(); i++) {
             temp = vertices.at(i);
             if (temp.get_name() == _temp) {
                 return temp;
             }
         }
         return temp;
     }

     void add_vertex(Vertex temp) {
         bool check = check_if_vertex_exist_by_name(temp.get_name());
         if (check == true) {
             cout << "Vertex with this name already exist" << endl;
         }
         else {
             vertices.push_back(temp);
             cout << "New Vertex Added Successfully" << endl;
         }
     }
  
     void add_edge_between_vertices(string fromVertex, string toVertex, size_t _population, bool t,bool p) {
         bool check1 = check_if_vertex_exist_by_name(fromVertex);
         bool check2 = check_if_vertex_exist_by_name(toVertex);

         bool check3 = check_if_edge_exist_between_vertices(fromVertex, toVertex);
         if (check1 && check2) {
             if (check3 == true) {
                 cout << "Edge between " << get_vertex_by_name(fromVertex).get_name() << "(" << fromVertex << ") and " << get_vertex_by_name(toVertex).get_name() << "(" << toVertex << ") already exist" << endl;
             }
             else {

                 for (int i = 0; i < vertices.size(); i++) {

                     if (vertices.at(i).get_name() == fromVertex) {
                         Edge e(toVertex, _population, t, p);
                         vertices.at(i).edgelist.push_back(e);
                     }
                     else if (vertices.at(i).get_name() == toVertex) {
                         Edge e(toVertex, _population, t, p);
                         vertices.at(i).edgelist.push_back(e);
                     }
                 }

                 cout << "Edge between " << fromVertex << " and " << toVertex << " added successfully" << endl;
             }
         }
         else {
             cout << "Invalid Vertex name entered.";
         }
     }


     void deleteEdgeByID(string fromVertex, string toVertex) {
         bool check = check_if_edge_exist_between_vertices(fromVertex, toVertex);
         if (check == true) {
             for (int i = 0; i < vertices.size(); i++) {
                 if (vertices.at(i).get_name() == fromVertex) {
                     for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++) {
                         if (it->get_destination() == toVertex) {
                             vertices.at(i).edgelist.erase(it);
                             break;
                         }
                     }
                 }

                 if (vertices.at(i).get_name() == toVertex) {

                     for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++) {
                         if (it->get_destination() == fromVertex) {
                             vertices.at(i).edgelist.erase(it);
                             break;
                         }
                     }
                 }
             }
             cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
         }
     }

     void deleteVertexByID(string vid) {
         int vIndex = 0;
         for (int i = 0; i < vertices.size(); i++) {
             if (vertices.at(i).get_name() == vid) {
                 vIndex = i;
             }
         }
         for (int i = 0; i < vertices.size(); i++) {
             for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++) {
                 if (it->get_destination() == vid) {
                     vertices.at(i).edgelist.erase(it);
                     break;
                 }
             }

         }
         vertices.erase(vertices.begin() + vIndex);
         cout << "Vertex Deleted Successfully" << endl;
     }

     void getAllNeigborsByID(string vid) {
         cout << get_vertex_by_name(vid).get_name() << " (" << get_vertex_by_name(vid).get_people_count() << ") --> ";
         for (int i = 0; i < vertices.size(); i++) {
             if (vertices.at(i).get_name() == vid) {
                 cout << "[";
                 for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++) {
                     cout << it->get_destination();
                 }
                 cout << "]";
             }
         }

     }

     void print() {
         for (size_t i = 0; i < vertices.size(); i++) {
             Vertex temp;
             temp = vertices.at(i);
             cout << temp.get_name() << " (" << temp.get_people_count() << ") --> ";
             temp.print_edge_list();
         }
     }
};

int main() {
Graph G1;
size_t option;

string _name,_name2;
int _population,  w;
bool t = 1, p = 0;
bool check;

do {
    cout << "What operation do you want to perform? " <<
        " Select Option number. Enter 0 to exit." << endl;
    cout << "1. Add Vertex" << endl;
    cout << "2. Update Vertex" << endl;
    cout << "3. Delete Vertex" << endl;
    cout << "4. Add Edge" << endl;
    cout << "5. Update Edge" << endl;
    cout << "6. Delete Edge" << endl;
    cout << "7. Check if 2 Vertices are Neigbors" << endl;
    cout << "8. Print All Neigbors of a Vertex" << endl;
    cout << "9. Print Graph" << endl;
    cout << "10. Clear Screen" << endl;
    cout << "0. Exit Program" << endl;

    cin >> option;
    Vertex v1;

    switch (option) {
    case 0: break;

    case 1:
        cout << "Add vertex: \n";
        cout << "Enter state name :";
        cin >> _name;
        cout << "Enter number of population :";
        cin >> _population;

        v1.set(_name, _population);
        G1.add_vertex(v1);

        break;

    case 2:
       
    case 3:
        cout << "Delete Vertex Operation -" << endl;
        cout << "Enter ID of Vertex(State) to Delete : ";
        cin >> _name;
        G1.deleteVertexByID(_name);

        break;

    case 4:
        cout << "Add Edge Operation -" << endl;
        cout << "Enter ID of Source Vertex(State): ";
        cin >> _name;
        cout << "Enter ID of Destination Vertex(State): ";
        cin >> _name2;
        cout << "Enter Weight of Edge: ";
        cin >> w;
        G1.add_edge_between_vertices(_name, _name2, w,t,p);

        break;

    case 5:

    case 6:
        cout << "Delete Edge Operation -" << endl;
        cout << "Enter ID of Source Vertex(State): ";
        cin >> _name;
        cout << "Enter ID of Destination Vertex(State): ";
        cin >> _name2;
        G1.deleteEdgeByID(_name, _name2);

        break;

    case 7:
        cout << "Check if 2 Vertices are Neigbors -" << endl;
        cout << "Enter ID of Source Vertex(State): ";
        cin >> _name;
        cout << "Enter ID of Destination Vertex(State): ";
        cin >> _name2;
        check = G1.check_if_edge_exist_between_vertices(_name, _name2);
        if (check == true) {
            cout << "Vertices are Neigbors (Edge exist)";
        }
        else {
            cout << "Vertices are NOT Neigbors (Edge does NOT exist)";
        }

        break;

    case 8:
        cout << "Print All Neigbors of a Vertex -" << endl;
        cout << "Enter ID of Vertex(State) to fetch all Neigbors : ";
        cin >> _name;
        G1.getAllNeigborsByID(_name);

        break;

    case 9:
        cout << "Print Graph Operation -" << endl;
        G1.print();

        break;

    default:
        cout << "Enter Proper Option number " << endl;
    }
    cout << endl;

} while (option != 0);

return 0;
}
