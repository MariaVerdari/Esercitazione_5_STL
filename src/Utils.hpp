#pragma once
#include <string>
#include <iostream>
#include <list>
#include<vector>
#include <array>

#include "PolygonalMesh.hpp"


using namespace std;

namespace PolygonalLibrary
{

bool ImportMesh(PolygonalMesh& mesh);
bool ImportCell0D(PolygonalMesh& mesh);
bool ImportCell1D(PolygonalMesh& mesh);
bool ImportCell2D(PolygonalMesh& mesh);

}