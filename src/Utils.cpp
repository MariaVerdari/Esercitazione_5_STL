#include "Utils.hpp"
#include <string>
#include "iostream"
#include "fstream"
#include "sstream"
#include <vector>
#include <list>
#include <array>
#include "Eigen/Eigen"


using namespace std;
namespace PolygonalLibrary
{
	


bool ImportMesh(PolygonalMesh& mesh) {
	if(!ImportCell0D(mesh))
        return false;

    if(!ImportCell1D(mesh))
        return false;

    if(!ImportCell2D(mesh))
        return false;

    return true;
}
	
	
	
	
bool ImportCell0D(PolygonalMesh& mesh)
{
ifstream fstr("Cell0Ds.csv");
if (fstr.fail()) {
return false;
}

string temp;
getline(fstr, temp);
list<string> listLines;

    string line;
    while (getline(fstr, line))
        listLines.push_back(line);
fstr.close();

mesh.NumCell0Ds = listLines.size();
if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

for (string& line : listLines)
    {
		std::replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

         int id;
         int marker;
        converter >>  id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);
		
		if (marker != 0) {
		auto it = mesh.Cell0DsMarker.find(marker); // mi da iterator a punto in cui è oppure end se non l'ha trovato
		if (it != mesh.Cell0DsMarker.end()){
			(*it).second.push_back(id); // faccio pushback alla lista
		}
		else{
			mesh.Cell0DsMarker.insert({marker,{id}});
		}
		}

}

return true;



}








bool ImportCell1D(PolygonalMesh& mesh){
	
	
	ifstream fstr("Cell1Ds.csv");
	
	
	if (fstr.fail()) {
		return false;
	}
	
	
	string temp;
	getline(fstr, temp);

	list<string> listLines;

    string line;
    while (getline(fstr, line))
        listLines.push_back(line);
	fstr.close();

	mesh.NumCell1Ds = listLines.size();
	
	if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }
	
	
mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(2, mesh.NumCell1Ds);

for (string& line : listLines)
    {
		std::replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

         int id;
         int marker;
        converter >>  id >> marker >> mesh.Cell1DsExtrema(0, id) >> mesh.Cell1DsExtrema(1, id);

        mesh.Cell1DsId.push_back(id);
		
		if (marker != 0) {
		auto it = mesh.Cell1DsMarker.find(marker); // mi da iterator a punto in cui è oppure end se non l'ha trovato
		if (it != mesh.Cell1DsMarker.end()){
			(*it).second.push_back(id); // faccio pushback alla lista
		}
		else{
			mesh.Cell1DsMarker.insert({marker,{id}});
		}
		}

}

return true;

	
}

	
	





bool ImportCell2D(PolygonalMesh& mesh){
	
	
	ifstream fstr("Cell2Ds.csv");
	
	
	if (fstr.fail()) {
		return false;
	}
	
	
	string temp;
	getline(fstr, temp);

	list<string> listLines;

    string line;
    while (getline(fstr, line))
        listLines.push_back(line);
	fstr.close();

	mesh.NumCell2Ds = listLines.size();
	
	if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }
	
	
	mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
	mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
	mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
	
for (string& line : listLines)
    {
		std::replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

         int id;
         int marker;
		 int numVert;
		 int numEdg;
        converter >>  id >> marker >> numVert;
		

        mesh.Cell2DsId.push_back(id);
		
		
		vector<int> vecVert;
		vecVert.reserve(numVert);

		for (int i = 0; i< numVert; i++) {
			int vert;
			converter >> vert;
			vecVert.push_back(vert);
			
		}
		
		mesh.Cell2DsVertices.push_back(vecVert);
		
		converter>> numEdg;
		
		vector<int> vecEdg;
		vecEdg.reserve(numEdg);
		for (int i = 0; i< numEdg; i++) {
			int edg;
			converter >> edg;
			vecEdg.push_back(edg);
			
		}
		
		
		if (marker != 0) {
		auto it = mesh.Cell2DsMarker.find(marker); // mi da iterator a punto in cui è oppure end se non l'ha trovato
		if (it != mesh.Cell2DsMarker.end()){
			(*it).second.push_back(id); // faccio pushback alla lista
		}
		else{
			mesh.Cell2DsMarker.insert({marker,{id}});
		}
		}

}

return true;

	
}

	




}





