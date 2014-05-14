#ifndef RUNLISTENER_HH
#define RUNLISTENER_HH
namespace g4
{
    class RunManager;

    /**
      * @short A class reacting to changes in run manager.
      *
      *  For each XXX in (Physics, Geometry, ParticleGenerator), it defines
      *  - OnXXXInitialiazing - before initializing
      *  - OnXXXInitialized - after initializing
      */
    class RunListener 
    {
        friend class RunManager;

    protected:
        /** 
          * @short Procedure called before geometry is initialized.
          */
        virtual void OnGeometryInitializing() { }
        
        /**
          * @short Procedure called after geometry is initialized.
          */
        virtual void OnGeometryInitialized() { }
        
        /** 
          * @short Procedure called before physics is initialized.
          */
        virtual void OnPhysicsInitializing() { }
        
        /**
          * @short Procedure called after physics is initialized.
          */
        virtual void OnPhysicsInitialized() { }

        /** 
          * @short Procedure that is called before particle generator builder is initialized.
          */
        virtual void OnParticleGeneratorInitializing() { }
        
        /**
          * @short Procedure called immediatelly after particle generator builder is initialized.
          */
        virtual void OnParticleGeneratorInitialized() { }           

        /**
          * @short Procedure called at the end of /run/initialize call.
          */
        virtual void OnRunInitialized() { }
    };
}
#endif