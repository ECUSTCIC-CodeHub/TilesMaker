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
        "ThirdParty/SFML/SFML-3.0.0/include",
     }-- #include搜索的路径，将第三方库加上

    files { 
        "Code/src/Engine/**.cpp",
        "Code/src/Engine/**.h",
        "Code/src/Engine/**.hpp"
    } -- 源代码，匹配Code/src/Engine/下的所有.c和.h文件

    defines {
        "BUILDING_DLL"
    }
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- 输出目录，如exe文件，非简单字符串，所以必须有括号。
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") -- 中间目录，如obj文件

    libdirs { "bin/" .. outputdir .. "/Tools"
        } -- 链接的库目录，这里链接了SFML库
    
    links { "Tools" }

    filter "configurations:Debug" -- Debug配置
        debugLibdir = {
            "ThirdParty/SFML/SFML-3.0.0/bin/lib/Debug",
        }
        debugLinks = { 
            "sfml-graphics-s-d",
            "sfml-window-s-d",
            "sfml-system-s-d",
            "sfml-audio-s-d",
            "sfml-network-s-d",
            "opengl32.lib",
            "winmm.lib",
            "gdi32.lib"
        }

        libdirs{
            debugLibdir,
        }
        links { 
            debugLinks
        }

    filter "configurations:Release" -- Release配置
        releaseLibdir = {
            "ThirdParty/SFML/SFML-3.0.0/bin/lib/Release",
        }
        releaseLinks = { 
            "sfml-graphics-s",
            "sfml-window-s",
            "sfml-system-s",
            "sfml-audio-s",
            "sfml-network-s",
            "opengl32.lib",
            "winmm.lib",
            "gdi32.lib"
        }
        libdirs{
            releaseLibdir
        }
        links { 
            releaseLinks
        }

    postbuildcommands { -- 构建后执行的命令，暂时没用

    }        


project ("Tools")
    location "Code/src/Tools"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files { 
        "Code/src/Tools/**.cpp",
        "Code/src/Tools/**.h",
        "Code/src/Tools/**.hpp"
    }

    includedirs {
    --   "src/Engine",
    }

    defines {
        "BUILDING_DLL"
    }
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 


project ("TilesMakerApp") 
    location "Code/App/"    
    kind "ConsoleApp"       
    language "C++"          
    cppdialect "C++17"      

    files { 
        "Code/App/**.cpp",
        "Code/App/**.h",
        "Code/App/**.hpp"
    }

    includedirs {
        "Code/src/Engine/",
    }

    libdirs { 
        "bin/" .. outputdir .. "/Engine",
        "bin/" .. outputdir .. "/Tools"
        } 

    links { 
        "Engine",
        "Tools"
     } -- 链接的库，注意g++链接库不能嵌套

    filter "configurations:Debug" 
        libdirs{
            debugLibdir,
        }
        links { 
            debugLinks
        }

    filter "configurations:Release"
        libdirs{
            releaseLibdir
        }
        links { 
            releaseLinks
        }
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
    postbuildcommands {
    --"{COPY} ../third/SFML/build/bin/%{cfg.buildcfg}/*.dll ../bin/" .. outputdir .. "/%{prj.name}"
    }
