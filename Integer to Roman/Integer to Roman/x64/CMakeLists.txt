cmake_minimum_required(VERSION 3.8)
project(x64)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        "Debug/Integer to Roman.tlog/CL.command.1.tlog"
        "Debug/Integer to Roman.tlog/CL.read.1.tlog"
        "Debug/Integer to Roman.tlog/CL.write.1.tlog"
        "Debug/Integer to Roman.tlog/Integer to Roman.lastbuildstate"
        "Debug/Integer to Roman.tlog/link.command.1.tlog"
        "Debug/Integer to Roman.tlog/link.read.1.tlog"
        "Debug/Integer to Roman.tlog/link.write.1.tlog"
        "Debug/Integer to Roman.tlog/unsuccessfulbuild"
        "Debug/Integer to Roman.log"
        "Debug/Integer to Roman.obj"
        "Debug/Integer to Roman.pch"
        Debug/stdafx.obj
        Debug/vc141.idb
        Debug/vc141.pdb)

add_executable(x64 ${SOURCE_FILES})