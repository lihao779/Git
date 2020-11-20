#include<iostream>
#include<string.h>
#include<string>
#include<fstream>

using namespace std;

struct ServerInfo
{
    char _ip[32];
    int _port;
};
class ConfigManager
{
    public:
    ConfigManager(const char* configfile = "biteserver.config")
       :_configfile(configfile) 
    {}
    
    void WriteBin(const ServerInfo& info)
    {
        ofstream ofs(_configfile,ifstream::out|ifstream::binary);
        ofs.write((const char*)&info,sizeof(info));
        ofs.close();
    }
    void ReadBin(ServerInfo& info)
    {
        ifstream ifs(_configfile,ifstream::in|ifstream::binary);
        ifs.read((char*)&info,sizeof(info));
        ifs.close();
    }
    void WriteText(const ServerInfo& info)
    {
        ofstream ofs(_configfile);
        ofs<<info._ip<<endl;
        ofs<<info._port<<endl;
        ofs.close();
    }
    void ReadText(ServerInfo& info)
    {
        ifstream ifs(_configfile);
        ifs>>info._ip;
        ifs>>info._port;
        ifs.close();
    }
    private:
        string _configfile;
};
int main()
{
    ConfigManager cfgMgr;
    ServerInfo wtinfo;
    ServerInfo rdinfo;

    strcpy(wtinfo._ip,"127.0.0.1");
    wtinfo._port = 80;
    cfgMgr.WriteBin(wtinfo);
    cfgMgr.ReadBin(rdinfo);
    cout<<rdinfo._ip<<endl;
    cout<<rdinfo._port<<endl;

    ///////////
    cfgMgr.WriteText(wtinfo);
    cfgMgr.ReadText(rdinfo);
    cout<<rdinfo._ip<<endl;
    cout<<rdinfo._port<<endl;
    return 0;
}
