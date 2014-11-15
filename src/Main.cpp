//#include <algorithm>
#include "kit/kit.h"
#include "kit/log/log.h"
#include "kit/async/multiplexer.h"
#include "kit/args/args.h"

#include <sys/types.h>
#include <unistd.h> 

using namespace std;

int main(int argc, const char *argv[])
{
    Args args(argc, argv);
    //auto proc = command("du", {"-h","-c","-s"});
    //proc.wait();
    if(args.has("-d"))
    {
        cout << "Not yet imlemented. A backup of your files is in .<folder>-rpg (hidden)" << endl;
        cout << "The <folder> syslink contains the ram-mounted files." << endl;
        cout << "Your ram files are at /dev/shm/rpg/<folder>/" << endl;
        return 1;
    }
    
    if(args.has("-r"))
    {
        cout << "Not yet imlemented. A backup of your files is in .<folder>-rpg (hidden)" << endl;
        cout << "The <folder> syslink contains the ram-mounted files." << endl;
        cout << "Your ram files are at /dev/shm/rpg/<folder>/" << endl;
        return 1;
    }
    
    if(mkdir("/dev/shm/rpg/", 0755) != 0) {}
    for(string& dir: args)
    {
        if(mkdir((string("/dev/shm/rpg/")+dir).c_str(), 0755) != 0) {}
        rename(dir.c_str(), (string(".")+ dir + ".rpg").c_str());
        int r =symlink((string("/dev/shm/rpg/")+dir).c_str(), dir.c_str());
        cout << dir << " has been rampaged." << endl;
    }
    
    return 0;
}

