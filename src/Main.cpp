//#include <algorithm>
#include "kit/kit.h"
#include "kit/log/log.h"
#include "kit/async/multiplexer.h"
#include "kit/args/args.h"
#include "kit/meta/meta.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h> 

using namespace std;

int run(string prog, vector<string> args)
{
    // make space for prog name and null
    std::vector<char*> argsptrs(args.size()+2);
    argsptrs[0] = (char*)prog.c_str();
    for(size_t i=0;i!=args.size();++i)
        argsptrs[i+1] = &args[i][0];
    pid_t pid = fork();
    if(0 == pid)
        execvp(prog.c_str(), argsptrs.data());
    int status;
    waitpid(pid, &status, 0);
    return status;
}

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
            run(
                "/bin/diff",
                {
                    "-rupN",
                    string("/dev/shm/rpg/")+dir,
                    string(".")+dir+".rpg"
                }
            );
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
    
    // write back changes (but don't unmount)
    if(args.has("-w")) for(unsigned i=0;;++i)
    {
        string dir = args.get(i);
        if(dir.empty())
            break;
        if(boost::starts_with(dir,"-"))
            continue;
        int status = run(
            "/bin/rsync",
            {
                "-rav", // recursive
                string("/dev/shm/rpg/") + dir + "/",
                string(".") + dir + ".rpg"
            }
        );
        if(0 != status) {
            cerr << "Cannot restore. (copy failed)" << endl;
            return 1;
        }
        return 0;
    }
    
    if(not args.empty()) for(unsigned i=0;;++i)
    {
        string dir = args.get(i);
        if(dir.empty())
            break;

        int status = run(
            "/bin/rsync",
            {
                "-r", // recursive
                "-ltpg", // preserve symlinks times,perms,groups
                dir,
                "/dev/shm/rpg/"
            }
        );

        //auto detail = make_shared<Meta>();
        //detail->set<string>("path","");
        //detail->serialize(string("/dev/shm/rpg/")+dir+".json");
        
        if(0 != status) {
            cerr << "Cannot enrage. (copy failed)" << endl;
            return 1;
        }
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
    else
    {
        // no app parameters
        cout << "Rampages: " << endl;
        run("/bin/ls", {"/dev/shm/rpg/"});
    }
    
    return 0;
}

