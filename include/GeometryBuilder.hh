#ifndef GEOMETRYBUILDER_HH
#define GEOMETRYBUILDER_HH

#include <G4LogicalVolume.hh>

namespace g4
{
    /**
      * @short Class to build geometry.
      *
      * To be used (mostly) in plugins.
      * If a geometry builder is returned by the plugin,
      * it's used to add physical volumes into world logical volume.
      *
      */
    class GeometryBuilder
    {
    public:
        /**
          * Creates part of the geometry and inserts it into
          * provided G4LogicalVolume, being the world volume
          * (in most cases)
          */
        virtual void BuildGeometry(G4LogicalVolume*) = 0;

        virtual ~GeometryBuilder() { }
        
    protected:
        /**
          * Call whenever geometry is changed.
          *
          * Not necessary in the initial building.
          */
        void GeometryChanged();
    };
}

#endif // GEOMETRYBUILDER_HH
