#ifndef GPS_HH
#define GPS_HH

#include "Component.hh"

class G4GeneralParticleSource;

namespace g4
{
    namespace components
    {
        /**
         * @brief Component providing the GeneraralParticleSource.
         *
         * Configure the GPS using its methods.
         */
        class GPS : public Component
        {
        public:
            GPS();

            virtual ~GPS();

            virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction();

        private:
            G4GeneralParticleSource* _gps;
        };
    }
}

#endif // GPS_HH

