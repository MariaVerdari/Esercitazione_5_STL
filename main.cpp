#include "Utils.hpp"
#include <list>
#include <vector>
#include <array>
#include <iomanip>
#include <iostream>
#include "Eigen/Eigen"
#include <cmath>
#include <iomanip>
#include <limits>


#include "PolygonalMesh.hpp"
//#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;



/*
//cose da fare
-funzione area e lunghezza
-test nel main di area e lunghezza
-map marker e test dei marker (tolgo 0) e faccio mappa vera da confrontare
-esportare mesh e test visivo
*/

int main()


{   
	PolygonalMesh mesh;
	
	
	// mappa marker celle
	
	

	
	bool a =  ImportMesh(mesh);
	



	
	
	// TEST PER I MARKER:
	
	for (auto &el : mesh.Cell0DsMarker) {
		cout<<el.first<< ":  [ ";
		for (int k :el.second)
			cout <<k<<" ";
		cout<<"]"<<endl;
		
	}
	cout<<endl;
	
	for (auto &el : mesh.Cell1DsMarker) {
		cout<<el.first<< ":  [ ";
		for (int k :el.second)
			cout <<k<<" ";
		cout<<"]"<<endl;
	}
	cout<<endl;

	
	for (auto &el : mesh.Cell2DsMarker) {
		cout<<el.first<< ":  [ ";
		for (int k :el.second)
			cout <<k<<" ";
		cout<<"]"<<endl;
	}
	cout<<endl;

		
	
	/// TEST PER LA LUNGHEZZA DEI LATI
	for (int edge: mesh.Cell1DsId){
		double len = fabs(mesh.Cell1DsExtrema(0,edge)-mesh.Cell1DsExtrema(1,edge));
		if( len < std::numeric_limits<double>::epsilon() ) 
        throw std::runtime_error("Lunghezza nulla");
	
	}




/*
for (int polyg: mesh.Cell2DsId){
		vector<int> vertices = mesh.Cell2DsVertices[polyg];
		double area = 0;
		int numVert =  vertices.size();
		for (int i = 0; i <  numVert -1; i++)
		{
			int vert1 = vertices[i];
			int vert2 = vertices[i+1];
			area =area + mesh.Cell0DsCoordinates( 0, vert1) * mesh.Cell0DsCoordinates( 1, vert2);
			area =area - mesh.Cell0DsCoordinates( 1, vert1) * mesh.Cell0DsCoordinates( 0, vert2);
		}
		area = area + mesh.Cell0DsCoordinates( 0, vertices[numVert-1]) * mesh.Cell0DsCoordinates( 1, vertices[0]);
		area = area - mesh.Cell0DsCoordinates( 1, vertices[numVert-1]) * mesh.Cell0DsCoordinates(0, vertices[0]);
		
		area = fabs(area);
		area = area/2.0;
		
		
		*/
		
	
	/// TEST PER L'AREA DEI POLIGONI
	for (int polyg: mesh.Cell2DsId){
		vector<int> vertices = mesh.Cell2DsVertices[polyg];
		double area = 0;
		int numVert =  vertices.size();
		
		
		// trovo baricentro
		double x_bar = 0;
		double y_bar = 0;
		
		for (int vert : vertices){
			x_bar += mesh.Cell0DsCoordinates( 0, vert);
			y_bar += mesh.Cell0DsCoordinates( 1, vert);
		}
		
		x_bar = x_bar/double(numVert);
		y_bar = y_bar/double(numVert);
		
		//traslo tutti i vertici in modo da avere baricentro nell'origine
		
	
		map<double, int> angoli;

			
		for (int i = 0; i< numVert; i++){
			double x_trasl = mesh.Cell0DsCoordinates( 0, vertices[i]) - x_bar;
			double y_trasl = mesh.Cell0DsCoordinates( 1, vertices[i]) - y_bar;
			
			double ang = atan2(y_trasl, x_trasl);
			if (ang<0)
				ang+= 2*M_PI;
			angoli.insert({ang,{vertices[i]}});

		}	
		int vert_orario[numVert];
		int i = 0;
		for (auto [angolo, vertice] : angoli){
			vert_orario[i] = vertice;
			i++;
			
		}
			
		
		for (int i = 0; i<numVert-1;i++)
		{
			int vert1 = vert_orario[i];
			int vert2 = vert_orario[i+1];
			area =area + mesh.Cell0DsCoordinates( 0, vert1) * mesh.Cell0DsCoordinates( 1, vert2);
			area =area - mesh.Cell0DsCoordinates( 1, vert1) * mesh.Cell0DsCoordinates( 0, vert2);
		}
		area = area + mesh.Cell0DsCoordinates( 0, vert_orario[numVert-1]) * mesh.Cell0DsCoordinates( 1, vert_orario[0]);
		area = area - mesh.Cell0DsCoordinates( 1, vert_orario[numVert-1]) * mesh.Cell0DsCoordinates(0, vert_orario[0]);
		
		area = fabs(area);
		area = area/2.0;
		
		double eps = std::numeric_limits<double>::epsilon();
		double tol2d = sqrt(3.0)*(eps*eps)/4.0;



		if( area < tol2d) 
        throw std::runtime_error("Area nulla");
	
	}
		
		
	
		

		
		
		


	// test nel main
	//per il primo test stampo per ogni marker lista di vertici e di lati e faccio test visivo oppure faccio mappa in cui inserisco valori a mano e poi controllo che le due mappe siano uguali
	// per gli altri faccio funzione area e lunghezza e ciclo tutti (tolleranza)
	//per l'lutimo uso vicini(mesh converter su internet-paraview glance) o paraview-confronto visivo; file da ucd a utv-con coordinate di celle ( o anche marker e id)


	
	
    return 0;
}
