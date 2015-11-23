#ifndef RunManager_HH
#define RunManager_HH

#include <memory>

#include <G4RunManager.hh>
#include <G4MTRunManager.hh>

namespace g4
{
    class RunObserver;
    class RunInitializer;

#ifdef G4MULTITHREADED
    typedef G4MTRunManager RunManagerBaseClass;
#else
    typedef G4RunManager RunManagerBaseClass;
#endif

    /**
      * @short Custom version of G4RunManager that enables us to
      * step in the middle of state transitions.
      *
      * Note: it can be done in another way, from outside
      *   via special callback classes (see manual).
      *
      * Run manager catches SIGINT signal and stops the run
      * instead of the whole application. Another interrupt
      * makes the application really stop.
      */
    class RunManager : public RunManagerBaseClass
    {
    public:
        RunManager(std::shared_ptr<RunInitializer> init);

        virtual ~RunManager();

        /**
          * @short Do what is necessary for the application and do standard initialize.
          *
          * This invokes all the builders from plugins.
          * It is called with /run/initialize
          */
        virtual void Initialize() override;

        void AddObserver(RunObserver* observer);

        void RemoveObserver(RunObserver* observer);

    private:
        std::shared_ptr<RunInitializer> _initializer;

        std::vector<RunObserver*> _observers;
    };
}

#endif // RunManager_HH
