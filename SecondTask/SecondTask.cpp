#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

struct Edge {
	std::string vertexName;
	int weight;
	bool visited = false;
	Edge(std::string vertexName, int weight) : vertexName(vertexName), weight(weight), visited(false) {}

	friend bool operator<(const Edge& l, const Edge& r)
	{
		return l.weight < r.weight;
	}

	friend bool operator>(const Edge& l, const Edge& r)
	{
		return l.weight > r.weight;
	}
};

void printVector(std::vector<std::string> vectorOfStrings) {
	size_t elementsOfVector = vectorOfStrings.size();
	for (size_t i = 0; i < elementsOfVector; i++)
		std::cout << vectorOfStrings[i] << " | ";
	std::cout << std::endl;
}

void printConnectedVerteces(std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighbors) {
	while (!neighbors.empty()) {
		std::cout << "	" << neighbors.top().vertexName << " " << neighbors.top().weight << "\n";
		neighbors.pop();
	}
}

std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> findNeighboursOfVertex(std::string vertexName, std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>> graph) {
	for (auto it = graph.cbegin(); it != graph.cend(); ++it) {
		if (vertexName == (*it).first)
			return (*it).second;
	}
}

bool hasUnvisitedNeighbours(std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighbors) {
	while (!neighbors.empty()) {
		if (!neighbors.top().visited)
			return true;
		neighbors.pop();
	}

	return false;
}

void changeVertexToVisited(std::string vertexName,
	std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>>& graph) {
	for (auto it = graph.begin(); it != graph.end(); ++it) {
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>& edges = (*it).second;
		std::vector<Edge> edgesToPushBack;
		while (!edges.empty()) {
			Edge edge = edges.top();
			if (edge.vertexName == vertexName)
				edge.visited = true;
			edgesToPushBack.push_back(edge);
			edges.pop();
		}

		//Turning them back
		for (size_t i = 0; i < edgesToPushBack.size(); i++)
			edges.push(edgesToPushBack[i]);
	}
}

Edge getNameOfClosestUnvisitedNeighbour(std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighbors) {
	while (!neighbors.empty()) {
		if (!neighbors.top().visited)
			return neighbors.top();
		neighbors.pop();
	}
}

//Function is only needed to find the shortest path between any vertex and the Railstation 
//vertex but for the sake of testing it with other vertexes it will accept two vertex names
int findShortestPathBetween(std::string first, std::string second, 
	std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>> graph) 
{
	std::unordered_map<std::string, bool> visited;
	std::unordered_map<std::string, int> distances;
	std::queue<std::string> vertexQueue;

	//Setting all vertices as not visited and their distances as infinite
	for (auto it = graph.cbegin(); it != graph.cend(); ++it) {
		visited[it->first] = false;
		distances[it->first] = std::numeric_limits<int>::max();
	}

	//Distance of the starting vertex set to 0
	distances[first] = 0;
	visited[first] = true;
	vertexQueue.push(first);

	//Using BFS
	while (!vertexQueue.empty()) {
		std::string currentVertex = vertexQueue.front();
		vertexQueue.pop();
		//Find all neighbours of the current vertex
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighbors = findNeighboursOfVertex(currentVertex, graph);
		while (!neighbors.empty()) {
			Edge neighbor = neighbors.top();
			if (!visited[neighbor.vertexName]) {
				visited[neighbor.vertexName] = true;
				distances[neighbor.vertexName] = distances[currentVertex] + neighbor.weight; 
				vertexQueue.push(neighbor.vertexName);
			}
			neighbors.pop();
		}
	}

	return distances[second];
}

std::vector<std::string> travel(size_t timeLimit, std::string currentVertexName, std::vector<std::string> travelPath,
	std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>> graph)
{
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> currentVertexNeighbours = (*graph.begin()).second;

	//Add vertex to path
	travelPath.push_back(currentVertexName);
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighboursOfCurrentVertex = findNeighboursOfVertex(currentVertexName, graph);
	Edge closestNeighbour = neighboursOfCurrentVertex.top();
	size_t timeNeededToTravelToClosestNeighbor = closestNeighbour.weight;
	std::string nameOfClosestNeighbour = closestNeighbour.vertexName;
	
	//If there are unvisited neighbours that can be visited they are a priority
	if (hasUnvisitedNeighbours(neighboursOfCurrentVertex)) {
		Edge closestUnvisitedNeighbour = getNameOfClosestUnvisitedNeighbour(neighboursOfCurrentVertex);

		//Check if neighbour can be visited and we can go back in time
		int timeToVisitAndGoBack = closestUnvisitedNeighbour.weight + 
			findShortestPathBetween("Railstation", closestUnvisitedNeighbour.vertexName, graph);

		int timeDiff = timeLimit - timeToVisitAndGoBack;
		if (timeDiff >= 0) {
			closestNeighbour = closestUnvisitedNeighbour;
			timeNeededToTravelToClosestNeighbor = closestNeighbour.weight;
			nameOfClosestNeighbour = closestNeighbour.vertexName;
		}
	}

	//Check if we can visit our closest neighbour and go back in time
	int timeToVisitAndGoBack = closestNeighbour.weight +
		findShortestPathBetween("Railstation", closestNeighbour.vertexName, graph);

	int timeDiff = timeLimit - timeToVisitAndGoBack;
	if (timeDiff > 0) {
		changeVertexToVisited(nameOfClosestNeighbour, graph);
		travelPath = travel(timeLimit - closestNeighbour.weight, nameOfClosestNeighbour, travelPath, graph);
	}

	return travelPath;
}

int main() {
	//1. Create adjacency list of graph
	std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>> graph;

	//2. Read input
	std::cout << "Please enter one number for the objects and the amount of relationships between them:\n";
	std::cout << "------------------------------------------------------\n";
	int vertexCount, edgesCount;
	std::cin >> vertexCount;
	std::cin >> edgesCount;
	std::cout << "------------------------------------------------------\n";

	std::cout << "Please enter information for every path between objects in the following format: {Start point} {End point} {Time}:\n";
	std::cout << "------------------------------------------------------\n";
	std::string vertex1, vertex2;
	int weight;
	for (size_t i = 0; i < edgesCount; i++) {
		std::cin >> vertex1 >> vertex2 >> weight;
		graph[vertex1].push(Edge(vertex2, weight));
		graph[vertex2].push(Edge(vertex1, weight));
	}
	std::cout << "------------------------------------------------------\n";
	std::cout << "Please enter a number for the time limit:\n";
	std::cout << "------------------------------------------------------\n";
	int timeLimit;
	std::cin >> timeLimit;
	std::cout << "------------------------------------------------------\n";

	//3. Travel around
	std::cout << "The places you could visit based on the time you have:\n";
	std::cout << "------------------------------------------------------\n";
	std::vector<std::string> travelPath;
	travelPath.push_back("Railstation");
	changeVertexToVisited("Railstation", graph);

	//First case we cannot visit any place
	if ((*graph.cbegin()).second.top().weight >= timeLimit)
		printVector(travelPath);
	//Second case we have time to visit exactly one place
	else if ((*graph.cbegin()).second.top().weight * 2 >= timeLimit) {
		travelPath.push_back((*graph.cbegin()).second.top().vertexName);
		travelPath.push_back("Railstation");
		printVector(travelPath);
	}
	else {
		std::vector<std::string> travelPath = travel(timeLimit, "Railstation", travelPath, graph);
		if (travelPath.size() != 1)
			travelPath.push_back("Railstation");
		printVector(travelPath);
	}

	return 0;

}

