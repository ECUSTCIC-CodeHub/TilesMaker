workspace ("TilesMaker") -- 工作区名，VS上对应sln文件名
    configurations { "Debug", "Release" } -- 配置
    platforms { "x64", "x86" } -- 平台，64位或32位系统

    startproject "TilesMakerApp" -- 启动项目
    flags { "MultiProcessorCompile" } 

    filter "configurations:Debug" -- Debug配置
        defines { "DEBUG" } -- 宏定义
        optimize "Off"
        symbols "On" -- 生成调试信息

    filter "configurations:Release" -- Release配置
        defines { "NDEBUG" } -- 宏定义
        optimize "On" -- 优化


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- 变量


project ("Engine") -- 项目名，vs上解决方案内项目名称
    location "Code/src/Engine/" -- 项目所在目录，相对于premake5.lua开始，vs的.vcxproj项目文件会放在这
    kind "StaticLib"  -- 项目类型，静态链接库
    language "C++"   -- 语言标准
    cppdialect "C++17" -- C++标准

    includedirs { 
        "Code/src/Tools",
        --"third/SFML/include",
     }-- #include搜索的路径，将第三方库加上

    files { 
        "Code/src/Engine/*.cpp",
        "Code/src/Engine/*.h",
        "Code/src/Engine/*.hpp"
    } -- 源代码，匹配src/MyLinkLib下的所有.c和.h文件

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- 输出目录，如exe文件，非简单字符串，所以必须有括号。
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- 中间目录，如obj文件

    filter "configurations:Debug" -- Debug配置
        defines { "DEBUG" } -- 宏定义
        symbols "On" -- 生成调试信息

        libdirs { 
            --"third/SFML/build/lib/Debug" 
        } -- 链接的库目录，这里链接了SFML库

        links { 
            "Tools"
            --"sfml-audio-d", 
            --"sfml-graphics-d",
            --"sfml-network-d",
            --"sfml-system-d",
            --"sfml-window-d" 
        } -- 链接的库，这里链接了SFML库
        
        libdirs { "bin/" .. outputdir .. "/Tools"
        } -- 链接的库目录，这里链接了SFML库

        links {
            "Tools"
            --"sfml-audio", 
            --"sfml-graphics",
            --"sfml-network",
            --"sfml-system",
            --"sfml-window" 
        } -- 链接的库，这里链接了SFML库

    postbuildcommands { -- 构建后执行的命令，暂时没用

    }        


project ("Tools")
    location "Code/src/Tools"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files { 
        "Code/src/Tools/*.cpp",
        "Code/src/Tools/*.h",
        "Code/src/Tools/*.hpp"
    }

    includedirs {
    --   "src/Engine",
    }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 


project ("TilesMakerApp") -- 项目名，vs上解决方案内项目名称
    location "Code/App/" -- 项目所在目录
    kind "ConsoleApp"  -- 项目类型，控制台应用
    language "C++"   -- 语言标准
    cppdialect "C++17" -- C++标准

    files { 
        "Code/App/*.cpp",
        "Code/App/*.h",
        "Code/App/*.hpp"
    } -- 源代码，匹配src/Application下的所有.cpp和.h文件

    includedirs {
        "Code/src/Engine/",
    } -- #include搜索的路径

    libdirs { "bin/" .. outputdir .. "/Engine" } -- 链接的库目录，这里链接了MyLinkLib项目生成的静态库

    links { "Engine" } -- 链接的库，这里链接了Engine项目生成的静态库

    targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- 输出目录，如exe文件
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- 中间目录，如obj文件

    postbuildcommands { -- 构建后执行的命令，
    --"{COPY} ../third/SFML/build/bin/%{cfg.buildcfg}/*.dll ../bin/" .. outputdir .. "/%{prj.name}"
    }
