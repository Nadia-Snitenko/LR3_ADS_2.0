#include <iostream>
#include <vector>
#include <list>
#include <iterator>

#include <limits>
#include <queue>

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
	string name;
	size_t population;
	
	list<Edge> edgelist;
    int number;

	Vertex(): name(""),population(0), number(-1) {}
	Vertex(const string& _name, const size_t _population) : name(_name), population(_population), number(-1) {}

	Vertex(const Vertex& temp){
		name = temp.name;
		population = temp.population;
        number = temp.number;
        edgelist = temp.edgelist;
	}

	~Vertex() {}

	string get_name() const { return name; }
    void set_name(string _name) { name = _name; }

	size_t get_people_count() const { return population; }
    void set_people_count(size_t _population) { population = _population; }

    void set(string _name, size_t _population) { name = _name; population = _population; }
	list<Edge> get_edge_list() const { return edgelist; }

    int get_number() const { return number; }
    void set_number(int _number) { number = _number; }

	void print_edge_list() {
		cout << "[";
		for (auto it = edgelist.begin(); it != edgelist.end(); it++) {
			cout << it->get_destination() << "(" << it->get_length() << ',' << it->get_payment()<< ',' << it->get_type() << ") --> ";
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
        number = temp.number;
		population = temp.population;

		return *this;
	}


};

class Graph {
    vector<Vertex> vertices;
    int count;
public:
    Graph() : count(0) {}
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
        if (check) {
            cout << "Vertex with this name already exist" << endl;
        }
        else {
            temp.set_number(count);
            vertices.push_back(temp);
            count++;
            cout << "New Vertex Added Successfully" << endl;
        }
    }

    void add_edge_between_vertices(string fromVertex, string toVertex, size_t _length, bool t, bool p) {
        bool check1 = check_if_vertex_exist_by_name(fromVertex);
        bool check2 = check_if_vertex_exist_by_name(toVertex);

        bool check3 = check_if_edge_exist_between_vertices(fromVertex, toVertex);
        if (check1 && check2) {
            if (check3) {
                cout << "Edge between " << get_vertex_by_name(fromVertex).get_name() << "(" << fromVertex << ") and " << get_vertex_by_name(toVertex).get_name() << "(" << toVertex << ") already exist" << endl;
            }
            else {

                for (int i = 0; i < vertices.size(); i++) {

                    if (vertices.at(i).get_name() == fromVertex) {
                        Edge e(toVertex, _length, t, p);
                        vertices.at(i).edgelist.push_back(e);

                    }
                    /*else if (vertices.at(i).get_name() == toVertex) {
                        Edge e(toVertex, _length, t, p);
                        vertices.at(i).edgelist.push_back(e);
                    }*/
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
        re_count();
    }

    void getAllNeigborsByID(const string vid) {
        cout << get_vertex_by_name(vid).get_name() << " (" << get_vertex_by_name(vid).get_people_count() << ") --> ";
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).get_name() == vid) {
                cout << "[";
                for (auto it = vertices.at(i).edgelist.begin(); it != vertices.at(i).edgelist.end(); it++) {
                    cout << it->get_destination() << ", ";
                }
                cout << "]";
            }
        }

    }

    void re_count() {
        for (size_t i = 0; i < vertices.size(); i++) {
            vertices.at(i).set_number(i);
            count = i;
        }
    }

    void print() {
        for (size_t i = 0; i < vertices.size(); i++) {
            Vertex temp(vertices.at(i));
            cout << temp.get_number()<<") " << temp.get_name() << " (" << temp.get_people_count() << ") --> ";
            temp.print_edge_list();
        }
    }

    void BFS(int s)
    {
        vector<bool> visited;            // вектор всех вершин графа 
        visited.resize(count, false); // от нуля до их количества 0|0|0|0, как только она попадает в очередь - будет закрашена, тк точно обработается

        list<int> queue; // очередь номеров найденных "необработанных" вершин" 

        visited[s] = true;  // вершину по заданному номеру закрасить 
        queue.push_back(s); // добавить ее в очередь, чтобы посмотреть соседей 

        // первый элемент обработан, дальше все будет происходить в цикле перемещаясь по соседям :)

        while (!queue.empty()) // теперь очередь не пуста и пока она не закончится мы не уйдем
        {
            s = queue.front(); // поставили "указатель" на того, чья сейчас очередь
            cout << s << " ";
            queue.pop_front(); //  пригласили этот элемент

            for (auto it = vertices.at(s).edgelist.begin(); it != vertices.at(s).edgelist.end(); it++) { //пройти во все вершины, в которые ведет текущий элемент
                int i = (get_vertex_by_name(it->get_destination())).get_number();
                if (!visited[i]){ // если элемент с i-тым номером не отмечен:
                    visited[i] = 1; 
                    queue.push_back(i); //и в очередь
                }
            };
        }
    }


 /*   struct distance {
        int number;
        double min_val;
        vector<int> way;

        distance():number(0),min_val(INFINITY) {};
        ~distance() {}

        void set_number; ()
    };*/

    void Dijkstra(int k) {

        vector<bool> visited; // посещенные 
        //vector <pair<int, double>>distance;  // номер вершины и лучшее расстояние
        vector <pair <int, pair<double, vector<int>>>>_distance; //  +++


        //list <pair<int,double>> queue;  
        //priority_queue <pair<int, double>, vector<pair<int, double>>, greater <pair<int, double>> > _queue; // ++
        priority_queue < pair <int, pair<double, vector<int> > >, vector< pair  <int, pair< double, vector<int> > > >, greater <pair<int, pair<double, vector<int> > > > >  __queue; //+++

        visited.resize(count, 0);

        //for (int i = 0; i < count; i++) {
        //    distance.push_back(make_pair(i, INFINITY));
        //}
        //distance[k].first = k; // номер вершины
        //distance[k].second = 0; // маршрут до нее



        for (int i = 0; i < count; i++) {
            vector<int>temp;
            temp.push_back(k);
            _distance.push_back(make_pair(i, make_pair(INFINITY,temp)));
        }
        _distance[k].first = k; // номер вершины //+++
        _distance[k].second.first = 0; // маршрут до нее // +++

        //queue.push_back(make_pair(distance[k].first, distance[k].second));
        //_queue.push(make_pair(distance[k].first, distance[k].second));
        //_queue.push(make_pair(_distance[k].first, _distance[k].second.first)); 
        __queue.push(make_pair(_distance[k].first, make_pair(_distance[k].second.first, _distance[k].second.second))); // +++

        /*
        while (!queue.empty()) {
            pair<int, double> active = queue.front();
            queue.pop_front();


            if (active.second < distance[active.first].second) { //если найденное расстояние меньше записанного
                distance[active.first].second = active.second;
            }

            for (auto it = vertices[active.first].edgelist.begin(); it != vertices[active.first].edgelist.end(); it++) {
                // пройти по списку вершин соседей, найти по имени ее номер и взять путь=длина ребра+дистанция до текущей, записать в queue
                queue.push_back(make_pair(get_vertex_by_name(it->get_destination()).get_number(), distance[active.first].second + it->get_length()));
            }

            visited[active.first] = true;
        }*/

        //while (!_queue.empty()) {
        //    pair<int, double> active = _queue.top();
        //    _queue.pop();


        //    if (active.second < distance[active.first].second) { //если найденное расстояние меньше записанного
        //        distance[active.first].second = active.second;
        //    }

        //    if (active.second < _distance[active.first].second.first) { //если найденное расстояние меньше записанного  +++
        //        _distance[active.first].second.first = active.second;
        //        _distance[active.first].second.second=
        //    }

        //    for (auto it = vertices[active.first].edgelist.begin(); it != vertices[active.first].edgelist.end(); it++) {
        //        // пройти по списку вершин соседей, найти по имени ее номер и взять путь=длина ребра+дистанция до текущей, записать в queue
        //        _queue.push(make_pair(get_vertex_by_name(it->get_destination()).get_number(), distance[active.first].second + it->get_length()));
        //    }

        //    visited[active.first] = true;
        //}
        //cout << endl<<"best length: "<<distance[5].second << endl;

        while (!__queue.empty()) {
            pair<int, pair<double, vector<int> >> active = __queue.top();
            __queue.pop();


            if (active.second.first < _distance[active.first].second.first) { //если найденное расстояние меньше записанного  +++
                _distance[active.first].second.first = active.second.first; // запишем новое наименьшее значение
                _distance[active.first].second.second= active.second.second; // запишем вектор вершин, который ведет в данную вершину
                _distance[active.first].second.second.push_back(active.first); // запишем саму вершину в конец для полного путь
            }

            for (auto it = vertices[active.first].edgelist.begin(); it != vertices[active.first].edgelist.end(); it++) {
                // пройти по списку вершин соседей, найти по имени ее номер и взять путь=длина ребра+дистанция до текущей, записать в queue
                __queue.push(  make_pair( get_vertex_by_name(it->get_destination()).get_number(),
                                          make_pair(_distance[active.first].second.first + it->get_length(),_distance[active.first].second.second)
                                        )
                            );
            }

            visited[active.first] = true;
        }
        cout << endl<<"best length: "<<_distance[5].second.first << endl;
        cout << endl << "way: ";
        for (int i = 0; i < _distance[5].second.second.size(); i++) { cout  << _distance[5].second.second[i] << " "; }
        cout << endl;
    }
            /*0. Добавляем первый элемент в очередь
            1 Берем след элемент по очереди
            2. Ставим на него active
            3. Удаляем из очереди
            4. Записываем до него путь: 
            
            !а вот тут надо знать ребро, которое на него указывает, чтобы посчитать его вес и путь!!!

                для первого ребра все проставляется до while, там дистанцию мы задали, 
                для не первого дистанцию запишем во время указания соседей
                if (active.second() < distance[active.first].second) {
                distance[active.first].second = active.second;
            } 
  
            5. Записываем в очередь его соседей
                // пройти по списку вершин, найти по номеру нужную и взаять ее соседей и пути до них записать их в queue
                for (auto it = vertices[active.first].edgelist.begin(); it != vertices[active.first].edgelist.end(); it++) {
                    //
                queue.push_back(make_pair(get_vertex_by_name(it->get_destination).get_number(),it-> get_length))
                }
            6. Окрашиваем его*/

        
        //priority_queue <pair<int, double>,  vector< pair<int, int> > , greater <pair<int, int>> > queue; 
              //номер вершины, расстояние до нее; контейнер, в котором будут храниться данные;   компаратор(находится в заголовочном файле functional). 

        /*Почему нам нужен какой-то другой компаратор?
            Потому что при стандартном объявлении priority_queue< pair<int, int> >,
            доставать получится только те вершины,
            расстояние до которых максимально,
            а нам-то нужно совсем наоборот.

    int main()
    {
        int myints[] = { 10,60,50,20,10,50,30 };

        std::priority_queue<int> first;
        std::priority_queue<int, std::vector<int> > second(myints, myints + 7);
        std::priority_queue<int, std::vector<int>, std::greater<int> >
            third(myints, myints + 7);

        int count = 7;
        //vector <pair<int, double>>distance;  // номер вершины и лучшее расстояние
        //list <pair<int, double>> queue; // 
        priority_queue <pair<int, double>, vector<pair<int, double>>, greater <pair<int, double>> > _queue;

        //const double infinity = std::numeric_limits<double>::max();

        for (int i = 0; i < count; i++) {
            _queue.push(make_pair(i, myints[i]));
        }

        _queue.push(make_pair(1, 45));
        _queue.push(make_pair(5, 5));
        _queue.push(make_pair(6, 10));
        _queue.push(make_pair(2, 20));

        while (!third.empty()) {
            cout << third.top() << " ";
            third.pop();
        }
        cout << endl;
        while (!_queue.empty()) {
            cout << _queue.top().first << " - " << _queue.top().second << endl;
            _queue.pop();
        }

        return 0;
    }*/

};



    int main() {
        Graph G1;
        Vertex v0, v1, v2, v3, v4, v5;
        int _population;
        double l;
        bool t = 1, p = 0;

        v0.set("beg", 0);
        G1.add_vertex(v0);

        v1.set("A", 1);
        G1.add_vertex(v1);

        v2.set("B", 2);
        G1.add_vertex(v2);

        v3.set("C", 3);
        G1.add_vertex(v3);

        v4.set("D", 4);
        G1.add_vertex(v4);

        v5.set("fin", 5);
        G1.add_vertex(v5);


        G1.add_edge_between_vertices(v0.get_name(), v1.get_name(), l = 9, t = 1, p = 0);
        G1.add_edge_between_vertices(v0.get_name(), v2.get_name(), l = 4, t = 1, p = 0);
        G1.add_edge_between_vertices(v0.get_name(), v4.get_name(), l = 5, t = 1, p = 0);
        G1.add_edge_between_vertices(v0.get_name(), v5.get_name(), l = 8, t = 1, p = 0);

        G1.add_edge_between_vertices(v1.get_name(), v5.get_name(), l = 1, t = 1, p = 0);
        G1.add_edge_between_vertices(v1.get_name(), v2.get_name(), l = 2, t = 1, p = 0);

        G1.add_edge_between_vertices(v2.get_name(), v5.get_name(), l = 8, t = 1, p = 0);
        G1.add_edge_between_vertices(v2.get_name(), v3.get_name(), l = 1, t = 1, p = 0);

        G1.add_edge_between_vertices(v3.get_name(), v5.get_name(), l = 4, t = 1, p = 0);

        G1.add_edge_between_vertices(v4.get_name(), v1.get_name(), l = 1, t = 1, p = 0);
        G1.add_edge_between_vertices(v4.get_name(), v3.get_name(), l = 1, t = 1, p = 0);

        
        G1.print();

        int begin = 0;
        G1.Dijkstra(begin);

        G1.BFS(begin);



        size_t option = 0;

        string _name, _name2;
        
        bool check;

        //do {
        //    cout << "What operation do you want to perform? " <<
        //        " Select Option number. Enter 0 to exit." << endl;
        //    cout << "1. Add Vertex" << endl;
        //    cout << "2. Update Vertex" << endl;
        //    cout << "3. Delete Vertex" << endl;
        //    cout << "4. Add Edge" << endl;
        //    cout << "5. Update Edge" << endl;
        //    cout << "6. Delete Edge" << endl;
        //    cout << "7. Check if 2 Vertices are Neigbors" << endl;
        //    cout << "8. Print All Neigbors of a Vertex" << endl;
        //    cout << "9. Print Graph" << endl;
        //    cout << "10. Clear Screen" << endl;
        //    cout << "0. Exit Program" << endl;
        //
        //    cin >> option;
        //    Vertex v1;
        //
        //    switch (option) {
        //    case 0: break;
        //
        //    case 1:
        //        cout << "Add vertex: \n";
        //        cout << "Enter state name :";
        //        cin >> _name;
        //        cout << "Enter number of population :";
        //        cin >> _population;
        //
        //        v1.set(_name, _population);
        //        G1.add_vertex(v1);
        //
        //        break;
        //
        //    case 2:
        //       
        //    case 3:
        //        cout << "Delete Vertex Operation -" << endl;
        //        cout << "Enter ID of Vertex(State) to Delete : ";
        //        cin >> _name;
        //        G1.deleteVertexByID(_name);
        //
        //        break;
        //
        //    case 4:
        //        cout << "Add Edge Operation -" << endl;
        //        cout << "Enter ID of Source Vertex(State): ";
        //        cin >> _name;
        //        cout << "Enter ID of Destination Vertex(State): ";
        //        cin >> _name2;
        //        cout << "Enter Weight of Edge: ";
        //        cin >> w;
        //        G1.add_edge_between_vertices(_name, _name2, w,t,p);
        //
        //        break;
        //
        //    case 5:
        //
        //    case 6:
        //        cout << "Delete Edge Operation -" << endl;
        //        cout << "Enter ID of Source Vertex(State): ";
        //        cin >> _name;
        //        cout << "Enter ID of Destination Vertex(State): ";
        //        cin >> _name2;
        //        G1.deleteEdgeByID(_name, _name2);
        //
        //        break;
        //
        //    case 7:
        //        cout << "Check if 2 Vertices are Neigbors -" << endl;
        //        cout << "Enter ID of Source Vertex(State): ";
        //        cin >> _name;
        //        cout << "Enter ID of Destination Vertex(State): ";
        //        cin >> _name2;
        //        check = G1.check_if_edge_exist_between_vertices(_name, _name2);
        //        if (check == true) {
        //            cout << "Vertices are Neigbors (Edge exist)";
        //        }
        //        else {
        //            cout << "Vertices are NOT Neigbors (Edge does NOT exist)";
        //        }
        //
        //        break;
        //
        //    case 8:
        //        cout << "Print All Neigbors of a Vertex -" << endl;
        //        cout << "Enter ID of Vertex(State) to fetch all Neigbors : ";
        //        cin >> _name;
        //        G1.getAllNeigborsByID(_name);
        //
        //        break;
        //
        //    case 9:
        //        cout << "Print Graph Operation -" << endl;
        //        G1.print();
        //
        //        break;
        //
        //    default:
        //        cout << "Enter Proper Option number " << endl;
        //    }
        //    cout << endl;
        //
        //} while (option != 0);

        return 0;
    }
