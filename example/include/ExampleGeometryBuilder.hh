#ifndef EXAMPLE_GENERATOR_BUILDER
#define EXAMPLE_GENERATOR_BUILDER

#include "GeometryBuilder.hh"

class ExampleGeometryBuilder : public g4::GeometryBuilder
{
public:
    void BuildGeometry(G4LogicalVolume *);
};
#endif
