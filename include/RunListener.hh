#ifndef RUNLISTENER_HH
#define RUNLISTENER_HH
namespace g4
{
    class RunManager;

    /**
      * @short A class reacting to changes in run manager.
      *
      * For each XXX in (Physics, Geometry, ParticleGenerator), it defines
      *  - OnXXXInitialiazing - before initializing
      *  - OnXXXInitialized - after initializing
      *
      * Default implementations do nothing, you can therefore
      * override only those that you are interested in.
      */
    class RunListener 
    {
        friend class RunManager;

    protected:
        /** 
          * @short Method called before geometry is initialized.
          */
        virtual void OnGeometryInitializing() { }
        
        /**
          * @short Method called after geometry is initialized.
          */
        virtual void OnGeometryInitialized() { }
        
        /** 
          * @short Method called before physics is initialized.
          */
        virtual void OnPhysicsInitializing() { }
        
        /**
          * @short Method called after physics is initialized.
          */
        virtual void OnPhysicsInitialized() { }

        /** 
          * @short Method that is called before particle generator builder is initialized.
          */
        virtual void OnParticleGeneratorInitializing() { }
        
        /**
          * @short Method called immediatelly after particle generator builder is initialized.
          */
        virtual void OnParticleGeneratorInitialized() { }           

        /**
          * @short Method called at the end of /run/initialize call.
          */
        virtual void OnRunInitialized() { }
    };
}
#endif