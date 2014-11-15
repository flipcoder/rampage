//#include <algorithm>
#include "kit/kit.h"
#include "kit/log/log.h"
#include "kit/async/multiplexer.h"
#include "kit/args/args.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 

using namespace std;

int main(int argc, const char *argv[])
{
    // ensure rpg dir
    if(mkdir("/dev/shm/rpg/", 0755) != 0) {}
    
    Args args(argc, argv);
    //auto proc = command("du", {"-h","-c","-s"});
    //proc.wait();
    if(args.has("-d"))
    {
        for(string& dir: args)
        {
            system(string(
                string("diff")
                +" \""+ 
                    (string(".")+dir+".rpg")
                +"\" \""+
                    (string("/dev/shm/rpg/")+dir)
                +"\""
            ).c_str());
            return 1;
        }
    }
    
    if(args.has("-r"))
    {
        cout << "Not yet imlemented. A backup of your files is in .<folder>-rpg (hidden)" << endl;
        cout << "The <folder> syslink contains the ram-mounted files." << endl;
        cout << "Your ram files are at /dev/shm/rpg/<folder>/" << endl;
        return 1;
    }
    
    for(string& dir: args)
    {
        int r;
        string t1, t2;
        //char buf[PATH_MAX];
        //getcwd(buf, PATH_MAX);
        //t1 = string(buf) + "/"+ dir;
        t2 = string("/dev/shm/rpg/");
        pid_t pid = fork();
        if(0 == pid)
            execl("/bin/cp", "cp", "-r", dir.c_str(), t2.c_str(), (char*)NULL);
        int status;
        waitpid(pid, &status, 0);
        t2 = string(".") + dir + ".rpg";
        if(0 != rename(dir.c_str(), t2.c_str())) {
            cerr << "Cannot enrage. (rename failed)" << endl;
            t1 = string("/dev/shm/rpg/")+dir;
            unlink(t1.c_str());
            return 1;
        }
        t1 = string("/dev/shm/rpg/") + dir;
        if(0 != symlink(t1.c_str(), dir.c_str())) {
            cerr << "Cannot enrage. (symlink failed)"<< endl;
            rename((string(".")+ dir + ".rpg").c_str(), dir.c_str());
            unlink((string("/dev/shm/rpg/")+dir).c_str());
            return 1;
        }
        cout << dir << " has went on a rampage!" << endl;
        return 0;
    }
    
    return 0;
}

