#ifndef PLUGGABLEGEOMETRY_HH
#define PLUGGABLEGEOMETRY_HH

#include <G4VUserDetectorConstruction.hh>
#include <G4LogicalVolume.hh>

#include <vector>

#include "GeometryBuilder.hh"

namespace g4
{
    /**
      * Class that collects all GeometryBuilders (from plugins)
      * and uses them to construct detector once requested.
      *
      * This class itself is not a G4VUserDetectorConstruction
      * because we want to postpone instantiating one till the 
      * last possible moment (i.e. just before the initialization
      * phase of the run manager). For this purpose it contains
      * the inner class.
      */
    class PluggableGeometry
    {
        class PluggableGeometryDetectorConstruction;
        friend class PluggableGeometryDetectorConstruction;
        
    public:
        PluggableGeometry();
        
        virtual ~PluggableGeometry();
                
        void AddGeometryBuilder(GeometryBuilder* builder) { _builders.push_back(builder); }
        
        G4VUserDetectorConstruction* GetDetectorConstruction();
        
    private:                        
        std::vector<GeometryBuilder*> _builders;
        
        PluggableGeometryDetectorConstruction* _detectorConstruction;
        
        /**
          * Private inner class that is a G4VUserDetectorConstruction.
          *
          * When constructing detector, it reads all the builders
          * from the parent PluggableGeometry.
          */
        class PluggableGeometryDetectorConstruction : public G4VUserDetectorConstruction
        {
        public:
            PluggableGeometryDetectorConstruction(const PluggableGeometry*);
            
            G4LogicalVolume* GetWorldLogicalVolume() const { return _worldLog; }
            
        protected:          
            virtual G4VPhysicalVolume* Construct();
                    
        private:    
            void CreateWorld();         
            
            G4VPhysicalVolume* _worldPhys;      
            
            G4LogicalVolume* _worldLog;                 
            
            const PluggableGeometry* _parent;
        };
    };
}

#endif // PLUGGABLEGEOMETRY_HH
