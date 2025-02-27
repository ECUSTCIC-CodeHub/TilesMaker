project "tmxlite"

    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    
    includedirs {
        "include"
    }

    files { 
        "src/**.c",
        "src/**.cpp",
        "include/**.h",
        "include/**.hpp"
    }

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}") -- 输出目录，如exe文件，非简单字符串，所以必须有括号。
    objdir ("bin/obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}") -- 中间目录，如obj文件


    filter "configurations:Debug" 
        defines { "DEBUG" } 
        optimize "Off"
        symbols "On" 

    filter "configurations:Release" 
        defines { "NDEBUG" }
        optimize "On"