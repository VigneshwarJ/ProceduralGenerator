#ifndef PG_POLYGONALGEOMETRY_H
#define PG_POLYGONALGEOMETRY_H

#include <vector>

#include "../Vertex.h"
#include "Renderable.h"


MAKE_SHARED(PolygonalGeometry);
class PolygonalGeometry : public Renderable
{
public:
    PolygonalGeometry();
    ~PolygonalGeometry();

    void setPrimitiveType(PrimitiveType type = PG_TRIANGLES);
    void setVertices(const Vertex *p_vertices,
                     std::size_t number_of_vertices);
    void setIndices(const uint32_t *p_indices,
                    std::size_t number_of_indices);

    PrimitiveType getPrimitiveType();
    const Vertex* getVertices();
    const uint32_t* getIndices();
    std::size_t getNumberOfVertices();
    std::size_t getNumberOfIndices();

private:
    enum PrimitiveType mPrimitiveType;
    const Vertex *mpVertices;
    const uint32_t *mpIndices;
    std::size_t mNumberOfVertices;
    std::size_t mNumberOfIndices;
};

#endif // PG_POLYGONALGEOMETRY_H
