#include <Delynoi/models/polygon/Polygon.h>
#include <Delynoi/models/Mesh.h>

using namespace Delynoi;

int main() {
    Mesh<Polygon> mesh;
    mesh.createFromFile("ExampleMesh.txt");
}