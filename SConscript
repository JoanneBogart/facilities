# -*- python -*-
# $Id$
# Authors: T.Burnett <tburnett@u.washington.edu>, Navid Golpayegani <golpa@slac.stanford.edu>
# Version: facilities-02-22-00
import os, os.path, re
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()
swigEnv = baseEnv.Clone()

# Write a config.h containing a list of all the packages in the current build
configfile = open(os.path.join(str(Dir('.').srcnode()),'src','config.h'), 'w')
configfile.write('/* Autogenerated by scons; do not edit! */\n')
configfile.write('#define PACKAGES "')
for package in packages:
    configfile.write(os.path.basename(package))
    configfile.write(' ')
configfile.write('"\n')

if 'obfLdPath' in libEnv:
    configfile.write('#define REL_OBFLDPATH "')
    rpathNode = Dir(str(libEnv['GLASTEXTvalue'])).rel_path(Dir(str(libEnv['obfLdPath'])))
    rpathStr = str(rpathNode)
    if baseEnv['PLATFORM'] == "win32":
        # Change backslashes to forward so they don't get eaten
        [head, tail] = os.path.split(rpathStr)
        while head != '':
            [head, newTail] = os.path.split(head)
            tail = newTail + "/" + tail
        rpathStr = tail
    configfile.write(rpathStr)
    configfile.write('"\n')
                 

configfile.close()

srcFiles = listFiles(['src/*.cxx'])
XGetopt = 'src/XGetopt.cxx'
toRemove = ''
for s in srcFiles:
    if re.search('XGetopt', str(s)) != None: toRemove = s
if toRemove != '' : srcFiles.remove(toRemove)

makeWrapper = True
if 'makeStatic' in baseEnv:
    libEnv.Tool('addLinkDeps', package = 'facilities', toBuild = 'static')
    facilitiesLib = libEnv.StaticLibrary('facilities', srcFiles)
else:
    libEnv.Tool('addLinkDeps', package = 'facilities',
                toBuild = 'shared')
    facilitiesLib = libEnv.SharedLibrary('facilities', srcFiles)

    if 'CONTAINERNAME' in baseEnv:
        if baseEnv['CONTAINERNAME'] == 'GlastRelease':
            makeWrapper = False
    if makeWrapper:
        swigEnv.Tool('facilitiesLib') 
        swigEnv.Tool('addLibrary', library=swigEnv['pythonLibs'])
        lib_pyFacilities = swigEnv.SwigLibrary('_py_facilities', 
                                               'src/py_facilities.i')

objList = []
if baseEnv['PLATFORM'] == 'win32':
    XGetoptObj = libEnv.Object('src/XGetopt.cxx')
    objList += [[XGetoptObj, libEnv]]

progEnv.Tool('facilitiesLib')
test_time = progEnv.Program('test_time', ['src/test/test_time.cxx'])
test_env = progEnv.Program('test_env', ['src/test/test_env.cxx'])
test_Util = progEnv.Program('test_Util',[ 'src/test/testUtil.cxx'])

if 'makeStatic' in baseEnv:
    progEnv.Tool('registerTargets', package = 'facilities',
                 staticLibraryCxts = [[facilitiesLib, libEnv]],
                 testAppCxts = [[test_time, progEnv], [test_env,progEnv],
                                [test_Util,progEnv]],
                 includes = listFiles(['facilities/*.h']),
                 objects = objList)
elif makeWrapper == True:
    progEnv.Tool('registerTargets', package = 'facilities',
                 libraryCxts = [[facilitiesLib, libEnv]],
                 swigLibraryCxts = [[lib_pyFacilities, swigEnv]],
                 testAppCxts = [[test_time, progEnv], [test_env,progEnv],
                                [test_Util,progEnv]],
                 includes = listFiles(['facilities/*.h']),
                 python = ['python/facilities.py', 'src/py_facilities.py'],
                 objects = objList)
else:
    progEnv.Tool('registerTargets', package = 'facilities',
                 libraryCxts = [[facilitiesLib, libEnv]],
                 testAppCxts = [[test_time, progEnv], [test_env,progEnv],
                                [test_Util,progEnv]],
                 includes = listFiles(['facilities/*.h']),
                 objects = objList)



