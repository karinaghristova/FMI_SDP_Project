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

std::vector<std::string> travel(size_t timeLimit, std::string currentVertexName, std::vector<std::string> travelPath,
	std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>> graph)
{
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> currentVertexNeighbours = (*graph.begin()).second;

	//Path
	travelPath.push_back(currentVertexName);
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighboursOfCurrentVertex = findNeighboursOfVertex(currentVertexName, graph);
	Edge closestNeighbour = neighboursOfCurrentVertex.top();

	if (hasUnvisitedNeighbours(neighboursOfCurrentVertex)) {
		closestNeighbour = getNameOfClosestUnvisitedNeighbour(neighboursOfCurrentVertex);
	}
	size_t timeNeededToTravelToClosestNeighbor = closestNeighbour.weight;
	std::string nameOfClosestNeighbour = closestNeighbour.vertexName;
	int timeDiff = timeLimit - timeNeededToTravelToClosestNeighbor;
	if (timeDiff >= 0) {
		changeVertexToVisited(nameOfClosestNeighbour, graph);
		travelPath = travel(timeDiff, nameOfClosestNeighbour, travelPath, graph);
	}

	return travelPath;
}

int main() {
	//Adjacency list of graph
	std::unordered_map<std::string, std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>> graph;

	int vertexCount, edgesCount;
	std::cin >> vertexCount;
	std::cin >> edgesCount;

	std::string vertex1, vertex2;
	int weight;
	for (size_t i = 0; i < edgesCount; i++) {
		std::cin >> vertex1 >> vertex2 >> weight;
		graph[vertex1].push(Edge(vertex2, weight));
		graph[vertex2].push(Edge(vertex1, weight));
	}

	int timeLimit;
	std::cin >> timeLimit;

	//Travel
	std::vector<std::string> travelPath;
	travelPath.push_back("Railstation");
	changeVertexToVisited("Railstation", graph);

	if ((*graph.cbegin()).second.top().weight >= timeLimit)
		printVector(travelPath);
	else {
		std::vector<std::string> travelPath = travel(timeLimit, "Railstation", travelPath, graph);
		printVector(travelPath);
	}

	return 0;
	//std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> neighbours = findNeighboursOfVertex("ArtGallery", graph);
	//printConnectedVerteces(neighbours);
}