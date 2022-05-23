#include "graph.h"
#include <iostream>
using namespace std;
int main(int argc, char** argv){
    bool use_default = false;
    if(argc == 3){
        try
        {
            stoi(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        use_default = true;
    }else if(argc == 2){
        try
        {
            stoi(argv[1]);
            throw runtime_error("usage: ./test [output] [start node] [end node]");
        }
        catch(const std::exception& e)
        {
            cout << "";
        }
        
    }
    if(argc > 4){
        throw runtime_error("usage: ./test [output] [start node] [end node]");
    }
    string node_data = "sanfrancisco/SF.txt";
    string edge_data = "sanfrancisco/SF2.txt";
    // string img = "assets/sanfrancisco.png";
    Graph h(node_data, edge_data);
    h.drawBase();
    vector<int> path;
    if(argc > 2){
        int end_index = argc - 1;
        int start_index = end_index - 1; 
        path = h.findShortestPath(stoi(argv[start_index]),stoi(argv[end_index]));
        vector<Graph::Node> p = h.convert(path);
        h.draw(p);
    }else{
        h.drawAllEdges();
    }
    if(argc < 2  || use_default){
        h.writeTo("myfile.png");
    }else{
        h.writeTo(argv[1]);
    }


    return 0;
}