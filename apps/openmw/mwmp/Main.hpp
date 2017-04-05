#include "../mwworld/ptr.hpp"
#include <boost/program_options.hpp>
#include <components/files/collections.hpp>

namespace mwmp
{
    class CellController;
    class GUIController;
    class LocalPlayer;
    class Networking;

    class Main
    {
    public:
        Main();
        ~Main();

        static void optionsDesc(boost::program_options::options_description *desc);
        static void configure(const boost::program_options::variables_map &variables);
        static bool init(std::vector<std::string> &content, Files::Collections &collections);
        static void postInit();
        static void destroy();
        static const Main &get();
        static void frame(float dt);
        static void pressedKey(int key);

        static bool isValidPacketScript(std::string script);

        Networking *getNetworking() const;
        LocalPlayer *getLocalPlayer() const;
        GUIController *getGUIController() const;
        CellController *getCellController() const;

        void updateWorld(float dt) const;

    private:
        static std::string addr;
        static std::string passw;
        Main (const Main&);
        ///< not implemented
        Main& operator= (const Main&);
        ///< not implemented
        static Main *pMain;
        Networking *mNetworking;
        LocalPlayer *mLocalPlayer;

        GUIController *mGUIController;
        CellController *mCellController;
        std::string server;
        unsigned short port;
    };
}
