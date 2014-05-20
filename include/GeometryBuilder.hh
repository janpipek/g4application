#ifndef GEOMETRYBUILDER_HH
#define GEOMETRYBUILDER_HH

class G4LogicalVolume;

namespace g4
{
    /**
      * @short Class to build geometry.
      *
      * To be used (mostly) in plugins.
      * If a geometry builder is returned by the plugin,
      * it's used to add physical volumes into world logical volume
      * (initiated by PluggableGeometry).
      */
    class GeometryBuilder
    {
    public:
        /**
          * @short Create part of the geometry and insert it into
          * provided G4LogicalVolume
          *
          * @param logVolume In most cases, this is the world volume (in most cases)
          */
        virtual void BuildGeometry(G4LogicalVolume* logVolume) = 0;

        virtual ~GeometryBuilder() { }
        
    protected:
        /**
          * @short Call whenever geometry is changed.
          *
          * Not necessary in the initial building.
          */
        void GeometryChanged();
    };
}

#endif // GEOMETRYBUILDER_HH
