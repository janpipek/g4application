#ifndef COMPOSITEGEOMETRY_HH
#define COMPOSITEGEOMETRY_HH

#include <vector>

#include <G4VUserDetectorConstruction.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace g4
{
    class GeometryBuilder;

    /**
      * @short Class that collects all GeometryBuilders (from plugins)
      * and uses them to construct detector once requested.
      *
      * This class itself is not a G4VUserDetectorConstruction
      * because we want to postpone instantiating one till the 
      * last possible moment (i.e. just before the initialization
      * phase of the run manager). For this purpose it contains
      * an inner class.
      */
    class CompositeGeometry
    {
        class CompositeGeometryDetectorConstruction;
        friend class CompositeGeometryDetectorConstruction;
        
    public:
        CompositeGeometry();
        
        virtual ~CompositeGeometry();
                
        /**
         * @brief Add one geometry builder.
         */
        void AddGeometryBuilder(GeometryBuilder* builder) { _builders.push_back(builder); }
        
        /**
         * @brief Get the detector contruction object.
         */
        G4VUserDetectorConstruction* GetDetectorConstruction();

        /**
         * @brief Use user-provided world volume instead of a default one.
         *
         * @param volume The physical world volume being used.
         */
        void SetWorldVolume(G4VPhysicalVolume* volume);
        
    private:                        
        std::vector<GeometryBuilder*> _builders;
        
        CompositeGeometryDetectorConstruction* _detectorConstruction;

        G4VPhysicalVolume* _worldPhys;

        G4LogicalVolume* _worldLog;

        /**
          * Private inner class that is a G4VUserDetectorConstruction.
          *
          * When constructing detector, it reads all the builders
          * from the parent CompositeGeometry.
          */
        class CompositeGeometryDetectorConstruction : public G4VUserDetectorConstruction
        {          
        public:
            CompositeGeometryDetectorConstruction(CompositeGeometry*);
            
        protected:
            virtual G4VPhysicalVolume* Construct();

        private:
            void CreateWorld();
            
            CompositeGeometry* _parent;
        };
    };
}

#endif // COMPOSITEGEOMETRY_HH
