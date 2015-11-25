#ifndef GENERICPARALLELWORLD_HH
#define GENERICPARALLELWORLD_HH

namespace g4
{
   /**
     * @brief Generic parallel world that can be built from function objects / lambdas.
     */
    class GenericParallelWorld : public G4VUserParallelWorld
    {
    public:
        using handler_type = std::function<void(G4LogicalVolume*)>;

        using sd_handler_type = std::function<void()>;

        GenericParallelWorld(const G4String& name,
                             handler_type constructHandler = [](G4LogicalVolume*) {},
                             sd_handler_type constructSDHandler = []() {}
        ) :
            G4VUserParallelWorld(name),
            _constructHandler(constructHandler),
            _constructSDHandler(constructSDHandler)
        {
        }

        void Construct() override
        {
            auto world = GetWorld()->GetLogicalVolume();
            _constructHandler(world);
        }

        void ConstructSD() override
        {
            _constructSDHandler();
        }
    private:
        handler_type _constructHandler;

        sd_handler_type _constructSDHandler;
    };
}

#endif // GENERICPARALLELWORLD_HH

