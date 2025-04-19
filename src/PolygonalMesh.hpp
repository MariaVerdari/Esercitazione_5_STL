#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
	unsigned int NumCell0Ds;
	unsigned int NumCell1Ds;
	unsigned int NumCell2Ds;
	
	//conviene fare lista per aggiungere le righe dal file perchè non so quante righe ho e poi creo vettore per poter fare accesso diretto
	
	vector<int> Cell0DsId;
	Eigen::MatrixXd Cell0DsCoordinates; //  x e y
	map<int, list<int>> Cell0DsMarker;
	
	vector<int> Cell1DsId;
	Eigen::MatrixXd Cell1DsExtrema; // origin e end
	map<int, list<int>> Cell1DsMarker;

	
	vector<int> Cell2DsId;
	vector<vector<int>>	Cell2DsVertices;
	vector<vector<int>>	Cell2DsEdges;
	map<int, list<int>> Cell2DsMarker;


	
	

	
	



	
};

}

