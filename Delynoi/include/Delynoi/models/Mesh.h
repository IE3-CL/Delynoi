#ifndef DELYNOI_MESH_H
#define DELYNOI_MESH_H

#include <Delynoi/config/DelynoiConfig.h>
#include <Delynoi/models/neighbourhood/PointMap.h>
#include <Delynoi/models/neighbourhood/SegmentMap.h>
#include <Delynoi/utilities/UniqueList.h>
#include <fstream>

namespace Delynoi {
    /*
     * Template class that represents a mesh, containing any class as element.
     */
    template<typename T>
    class Mesh {
    protected:
        /*
         * SegmentMap and PointMap instances representing neighbourhood information
         */
        SegmentMap *edges = nullptr;
        PointMap *pointMap = nullptr;

        /*
         * List of points fo the mesh (forced to be unique)
         */
        UniqueList<Point> points;

        /*
         * List of elements of the mesh
         */
        std::vector<T> polygons;

    public:
        /*
         * Default constructor
         */
        Mesh();

        /*
         * Constructor. Creates a mesh from its points (not necessarily unique), elements and neighbourhood maps
         */
        Mesh(std::vector<Point> &p, std::vector<T> &e, SegmentMap *s, PointMap *pM);

        /*
         * Constructor. Creates a mesh from its points, elements and neighbourhood maps
         */
        Mesh(UniqueList<Point> &p, std::vector<T> &e, SegmentMap *s, PointMap *pM);

        /*
         * Copy constructor
         */
        Mesh(const Mesh &m);

        /*
         * Clear mesh data
         */
        void clear() const;

        /* Prints the mesh contents in a file stream
         * @param file file stream to print the mesh
         */
        void printInStream(std::ofstream &file);

        /* Print the mesh contents in a file relative to user path
         * @param fileName name of the file to print
         */
        void printInFile(const std::string &fileName);

        /* Print the mesh contents in a file relative to absolute path
         * @param fileName name of the file to print
         */
        void printInPath(const std::string &path);

        /* Creates the mesh (fill its contents) from a file
         * @param fileName name of the file to read
         * @param startIndex Index to start reading the informtion (so to be compatible with both zero and one-indexed
         * standards)
         */
        void createFromFile(const std::string &fileName, int startIndex = 0);

        /* Creates the mesh (fill its contents) from a file
         * @param ofstream stream from which the mesh will be read
         * @param startIndex Index to start reading the informtion (so to be compatible with both zero and one-indexed
         * standards)
         */
        void createFromStream(std::ifstream &infile, int startIndex);

        /*
         * @return reference list of elements of the mesh
         */
        std::vector<T> &getPolygons();

        /*
         * @return list of elements of the mesh
         */
        std::vector<T> getPolygons() const;

        /* Gets the element at a given index
         * @param index index to lookup
         * @return element of the given index
         */
        T &getPolygon(int index);

        /*
         * @return segment map of the mesh (neighbourhood by segment information)
         */
        SegmentMap *getSegments() const;

        /*
         * @return point map of the mesh (neighbourhood by point information)
         */
        PointMap *getPointMap() const;

        /*
         * @return reference to the list of points of the mesh
         */
        UniqueList<Point> &getPoints();

        /*
         * @return list of points of the mesh
         */
        UniqueList<Point> getPoints() const;

        /*
         * @param i index to lookup
         * @return point in index i
         */
        Point getPoint(int i);

        /* Gets all neighbours by segment (incident polygons) of a given segment
         * @param s segment to lookup
         * @return all incident polygons to s
         */
        NeighboursBySegment getNeighbours(const IndexSegment &s) const;
    };

    template<typename T>
    Mesh<T>::Mesh() = default;

    template<typename T>
    Mesh<T>::Mesh(std::vector<Point> &p, std::vector<T> &e, SegmentMap *s, PointMap *pM) {
        this->points.push_list(p);
        this->polygons = e;
        this->edges = s;
        this->pointMap = pM;
    }

    template<typename T>
    Mesh<T>::Mesh(UniqueList<Point> &p, std::vector<T> &e, SegmentMap *s, PointMap *pM) {
        // ReSharper disable once CppTemplateArgumentsCanBeDeduced
        this->points = UniqueList<Point>(p);
        this->polygons = e;
        this->edges = s;
        this->pointMap = pM;
    }

    template<typename T>
    Mesh<T>::Mesh(const Mesh &m) {
        this->points = m.getPoints();
        this->polygons = m.getPolygons();
        this->edges = m.getSegments();
        this->pointMap = m.getPointMap();
    }

    template<typename T>
    void Mesh<T>::clear() const {
        delete this->edges;
        delete this->pointMap;
    }

    template<typename T>
    void Mesh<T>::createFromFile(const std::string &fileName, const int startIndex) {
        std::ifstream infile = utilities::openFile(fileName);
        createFromStream(infile, startIndex);
        infile.close();
    }

    template<typename T>
    void Mesh<T>::createFromStream(std::ifstream &infile, const int startIndex) {
        if (this->edges == nullptr) this->edges = new SegmentMap;
        if (this->pointMap == nullptr) this->pointMap = new PointMap;

        std::string line;
        std::getline(infile, line);
        const int numberMeshPoints = std::atoi(line.c_str()); // NOLINT(*-err34-c)
        for (int i = 0; i < numberMeshPoints; ++i) {
            std::getline(infile, line);
            std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

            Point newPoint(std::atof(splittedLine[0].c_str()), std::atof(splittedLine[1].c_str())); // NOLINT(*-err34-c)
            this->points.push_back(newPoint);
        }

        std::getline(infile, line);
        const int numberMeshPolygons = std::atoi(line.c_str()); // NOLINT(*-err34-c)

        for (int i = 0; i < numberMeshPolygons; ++i) {
            std::getline(infile, line);
            std::vector<std::string> splittedLine = utilities::splitBySpaces(line);

            std::vector<int> polygonPoints;
            for (int j = 1; j < splittedLine.size(); ++j) {
                polygonPoints.push_back(std::atoi(splittedLine[j].c_str()) - startIndex); // NOLINT(*-err34-c)
            }

            T newPolygon(polygonPoints, this->points.getList());
            this->polygons.push_back(newPolygon);
            std::vector<IndexSegment> segments;
            newPolygon.getSegments(segments);

            for (const IndexSegment &s: segments) {
                this->edges->insert(s, i);
            }
        }
    }

    template<typename T>
    void Mesh<T>::printInFile(const std::string &fileName) {
        this->printInPath(utilities::getPath() + fileName);
    }

    template<typename T>
    void Mesh<T>::printInPath(const std::string &path) {
        std::ofstream file;
        file.open(path, std::ios::out);
        file << std::fixed << std::setprecision(DelynoiConfig::instance()->getPrecision());

        printInStream(file);
        file.close();
    }

    template<typename T>
    std::vector<T> &Mesh<T>::getPolygons() {
        return this->polygons;
    }

    template<typename T>
    std::vector<T> Mesh<T>::getPolygons() const {
        return this->polygons;
    }

    template<typename T>
    T &Mesh<T>::getPolygon(int index) {
        return this->polygons[index];
    }

    template<typename T>
    void Mesh<T>::printInStream(std::ofstream &file) {
        file << points.size() << std::endl;
        for (int i = 0; i < points.size(); i++) {
            file << points[i].getString() << std::endl;
        }

        if (this->edges != nullptr) {
            file << this->edges->size() << std::endl;
            for (const auto &e: this->edges->getMap()) {
                IndexSegment edge = e.first;
                file << edge.getString() << std::endl;
            }
        }

        file << this->polygons.size() << std::endl;
        for (int i = 0; i < this->polygons.size(); i++) {
            file << this->polygons[i].getString() << std::endl;
        }
    }

    template<typename T>
    SegmentMap *Mesh<T>::getSegments() const {
        return this->edges;
    }

    template<typename T>
    PointMap *Mesh<T>::getPointMap() const {
        return this->pointMap;
    }

    template<typename T>
    UniqueList<Point> &Mesh<T>::getPoints() {
        return this->points;
    }

    template<typename T>
    UniqueList<Point> Mesh<T>::getPoints() const {
        return this->points;
    }

    template<typename T>
    Point Mesh<T>::getPoint(int i) {
        return this->points[i];
    }

    template<typename T>
    NeighboursBySegment Mesh<T>::getNeighbours(const IndexSegment &s) const {
        return this->edges->get(s);
    }
} // namespace Delynoi

#endif
