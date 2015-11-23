#ifndef VERBOSITY_HH
#define VERBOSITY_HH

#include <memory>

#include <G4Types.hh>
#include <G4GenericMessenger.hh>

namespace g4
{
    namespace util
    {
        /**
          * @short Mixin that enables automatic verbosity management (including macro command).
          */
        class VerbosityMixin
        {
        public:
            /**
              * @short Constructor.
              *
              * @param useMessenger If true, an UI command "/[messengerDirectory]/verbose is automatically created
              * @param messengerDirectory Name of the UI directory where to put the command (should contain
              *    begin and end slashes.)
              */
            VerbosityMixin(bool createMessenger = false, const G4String& messengerDirectory = "") : _verboseLevel(0)
            {
                if (createMessenger)
                {
                    if (!messengerDirectory.length())
                    {
                        G4Exception("VerbosityMixin", "NoMessengerDirectory", FatalException, "Cannot create verbosity messenger without a directory name");
                    }
                    _messenger = std::make_shared<G4GenericMessenger>(this, messengerDirectory);
                    _messenger->DeclareMethod("verbose", &VerbosityMixin::SetVerboseLevel, "Set verbosity level.");
                }
            }

            virtual ~VerbosityMixin() = default;

            void SetVerboseLevel(G4int vl) { _verboseLevel = vl; }

            G4int GetVerboseLevel() const { return _verboseLevel; }

        private:
            G4int _verboseLevel;

            std::shared_ptr<G4GenericMessenger> _messenger;
        };
    }
}
#endif
