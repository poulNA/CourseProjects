#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <exception>
#include "cs225/PNG.h"
#include "Image.h"
#include "StickerSheet.h"

using namespace std;

class Graph {
    public:
        struct Node {
        int id;
        double x_;
        double y_;
        };
        // constructors and destructor
        Graph(string node_data, string edge_data);
        Graph(string node_data, string edge_data, string file);
        ~Graph();

        /**
        * Loads Nodes 
        * @param file file to read and load nodes.
        */
        void makeNodeList(string file);

        /**
        * Loads Edges 
        * @param file file to read and load edges.
        */
        void makeEdgeList(string file);

        /**
        * Adds Edges
        * @param node1 first node of the edge
        * @param node2 second node of the edge
        * @param dist distance between the edges
        */
        void addEdge(Node node1, Node node2, double dist);

        /**
        * Finds the shortest path between nodes by id and Dijkstra's Algorithm
        * @param first id of the first node
        * @param second id of the second node
        * @return vector of ids in the shortest path
        */
        vector<int> findShortestPath(int first, int second);

        /**
        * Finds the least edge path between nodes by id using BFS
        * @param first id of the first node
        * @param second id of the second node
        * @return vector of ids in the least edges path
        */
        vector<int> BFS(int first, int second);

        /**
        * Gets the adjacent edges of a given node
        * @param node id of the given node
        * @return vector of edges adjacent to a node id
        */
        vector<pair<int,long double> > adjacent(int node);

        /**
        * Draws the path between all nodes in the vector
        * @param nodes vector of nodes
        */
        void draw(vector<Node> nodes);

        /**
        * Reads a different bse image
        * @param file file to read
        */
        void read(string filename);

        /**
        * Converts a path of integers to a path of nodes.
        * @param vect vector of nodes that is the path of nodes
        * @return vector of nodes convertet from vector of int
        */
        vector<Node> convert(vector<int> vect);

        /**
        * Draws all nodes onto the base.
        */
        void drawBase();

        /**
        * Draws connection between two nodes(on the base image) with the 
        * given colors for nodes and edges.
        * @param from the node to start from
        * @param to the node to end at
        * @param nodeColor the color of the node
        * @param edgeColor the color of the edge
        */
        void drawConnection(Node from, Node to, cs225::HSLAPixel nodeColor, cs225::HSLAPixel edgeColor);

        /**
        * Write the current map to file.
        * @param file the file to write to.
        */
        void writeTo(string file);

        /**
        * Draws all edges.
        */
        void drawAllEdges();

        /**
        * Sets height
        * @param h the height to set to
        */
        void setHeight(unsigned h);

        /**
        * Sets width
        * @param w the width to set to
        */
        void setWidth(unsigned w);

        /**
         * finds shortest path through N landmarks taken as vector<int>
         * @param vector of node ids to find shortest path through
         * @return the shortest path
         */
        vector<int> findShortestPath(vector<int> nodes);

        /**
        * Zoom in two nodes if their distance is less than 500 pixels. 
        * Draws the zoomed portion on the top-right of the image.
        * @param start the node to start the zoom
        * @param end the node to end the zoom
        */
        void zoomIn(Node start, Node end);

        //move to private once testing is completed
        vector<Node> nodeList;
        map<int, vector<pair<int,long double> > > edgelist;
        unsigned width_;
        unsigned height_;
        Image* base;
        StickerSheet * zoomedIn;


        /**
        * Colors
        */
        cs225::HSLAPixel yellow = cs225::HSLAPixel(60, 1, .5, 1);
        cs225::HSLAPixel orange = cs225::HSLAPixel(23,.95,.52, 1);
        cs225::HSLAPixel green = cs225::HSLAPixel(120,1,.5, 1);
        cs225::HSLAPixel red = cs225::HSLAPixel(0,1,.5, 1);
        cs225::HSLAPixel black = cs225::HSLAPixel(0, 0, 0, 1);
        cs225::HSLAPixel transparent = cs225::HSLAPixel(0, 0, 0, 0);

        // used only for testing
        static vector<pair<int,int>> testDrawConnection(Node from, Node to);
        int zoomIn_calls = 0;
        

    private:
        // map<int, vector<pair<int,double>>> edgelist;
        // vector<Node> nodeList;
};
bool operator==(const Graph::Node& a, const Graph::Node& b);