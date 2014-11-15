solution("rpg")
    configurations {"Debug", "Release"}

    targetdir("bin")

    configuration "debug"
        defines { "DEBUG" }
        flags { "Symbols" }
    configuration "release"
        defines { "NDEBUG" }
        flags { "OptimizeSpeed" }

    project("rpg")
        --uuid("")
        kind("ConsoleApp")
        language("C++")
        links {
            "pthread",
            "boost_system",
            "boost_filesystem",
            "boost_thread"
        }
        files {
            "src/**.h",
            "src/**.cpp"
        }
        excludes {
            "src/tests/**"
        }
        includedirs {
            "vendor/include/",
            "/usr/local/include/",
        }
        libdirs {
            "/usr/local/lib/",
            "/usr/local/lib64/",
        }
        
        --configuration {"debug"}
        --    defines { "BACKWARD_HAS_BFD=1" }
        --    links {
        --        "bfd",
        --        "iberty"
        --    }
        --    --buildoptions { "-finstrument-functions" }
        --    linkoptions { "`llvm-config --libs core` `llvm-config --ldflags`" }
        --configuration {}

        configuration { "gmake" }
            buildoptions { "-std=c++11" }
            --buildoptions { "-std=c++11",  "-pedantic", "-Wall", "-Wextra" }
            configuration { "macosx" }
                buildoptions { "-U__STRICT_ANSI__", "-stdlib=libc++" }
                linkoptions { "-stdlib=libc++" }
        configuration {}

