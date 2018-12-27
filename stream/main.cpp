#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;
struct Serverinfo 
{
  char _ip[32];  // Ip
   int _port;   //端口
};
struct ConfigerManager
{
  private:
    string _configfile;
  public:
     ConfigerManager(const char* configfile = "server.file")
       :_configfile(configfile)
       {
            
       }
     void WriteBin(const Serverinfo &info)
     {
       ofstream ofs(_configfile,ifstream::in|ifstream::binary);
       ofs.write((const char*)&info,sizeof(Serverinfo));
       ofs.close();
     }
     void ReadBin( Serverinfo &info)
     {
        ifstream ifs(_configfile,ifstream::out|ifstream::binary);
        ifs.read(( char *)&info,sizeof(Serverinfo));
        ifs.close();

     }
     void WriteTxt(const Serverinfo &info)
     {
       ofstream ofs(_configfile );

       ofs << info._ip << endl;
       ofs << info._port << endl;
       ofs.close();
     }
     void ReadTxt( Serverinfo &info)
     {
       ifstream ifs(_configfile );

       ifs >> info._ip ;
       ifs >> info._port ;
       ifs.close();
     }
};
int main()
{
  ConfigerManager cfgMgr;
   
    Serverinfo winfo;
    Serverinfo rinfo;
    strcpy(winfo._ip,"126.00.1");
    winfo._port = 80;
    cfgMgr.WriteBin(winfo);
    cfgMgr.ReadBin(rinfo);

    cout << rinfo._ip << endl;
    cout << rinfo._port << endl;
    
  //   cfgMgr.WriteTxt(winfo);
  //  cfgMgr.ReadTxt(rinfo);

  //  cout << rinfo._ip << endl;
   // cout << rinfo._port << endl;
   return 0;
}
