//#include <algorithm>
#include "kit/kit.h"
#include "kit/log/log.h"
#include "kit/async/multiplexer.h"
#include "kit/args/args.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 

using namespace std;

//int run(string prog, vector<string> args)
//{
//    pid_t pid = fork();
//    if(0 == pid)
//        execl(prog, prog, // (char*)NULL);
//    int status;
//    waitpid(pid, &status, 0);
//    return status;
//}

int main(int argc, const char *argv[])
{
    // ensure rpg dir
    if(mkdir("/dev/shm/rpg/", 0755) != 0) {}
    
    Args args(argc, argv);
    //auto proc = command("du", {"-h","-c","-s"});
    //proc.wait();
    if(args.has("-d"))
    {
        for(unsigned i=0;;++i)
        {
            string dir = args.get(i);
            if(dir.empty())
                break;
            if(boost::starts_with(dir, "-"))
                continue;
            pid_t pid = fork();
            if(0 == pid)
                execl(
                    "/bin/diff", "diff", "-rupN",
                    (string("/dev/shm/rpg/")+dir).c_str(),
                    (string(".")+dir+".rpg").c_str(),
                    (char*)NULL
                );
            int status;
            waitpid(pid, &status, 0);
        }
        return 1;
    }
    
    if(args.has("-r"))
    {
        cout << "Not yet imlemented. A backup of your files is in .<folder>-rpg (hidden)" << endl;
        cout << "The <folder> syslink contains the ram-mounted files." << endl;
        cout << "Your ram files are at /dev/shm/rpg/<folder>/" << endl;
        return 1;
    }
    
    for(unsigned i=0;;++i)
    {
        string dir = args.get(i);
        if(dir.empty())
            break;

        pid_t pid = fork();
        if(0 == pid)
            execl(
                "/bin/cp", "cp", "-r",
                dir.c_str(), string("/dev/shm/rpg/").c_str(),
                (char*)NULL
            );
        int status;
        waitpid(pid, &status, 0);
        if(0 != rename(dir.c_str(), (string(".") + dir + ".rpg").c_str())) {
            cerr << "Cannot enrage. (rename failed)" << endl;
            unlink((string("/dev/shm/rpg/")+dir).c_str());
            return 1;
        }
        if(0 != symlink(
            (string("/dev/shm/rpg/") + dir).c_str(), dir.c_str())
        ){
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

