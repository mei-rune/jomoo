import os;
import sys;

prifix = "/cygdrive/";

arguments = [];
for val in sys.argv:
    p = val.find( prifix );
    if( -1 != p and '/' == val[ p + 11 ] ):
        arguments.append( val[0: p ] + val[ p + len(prifix) ] + ":" + val[ p + len(prifix) +1 : ] )
    else:
        arguments.append( val )

out = open( "c:\\aaab.txt", "w" )
print >>out, "Old_Environment:";
envirionMap = {};
for k in os.environ:
    val = os.environ[ k ];
    print >>out, "%s=%s"%( k , val );
    p = val.find( prifix );
    if( -1 != p and '/' == val[ p + 11 ] ):
        envirionMap[ k ] = val[0: p ] + val[ p + len(prifix) ] + ":" + val[ p + len(prifix) +1 : ]
    else:
        envirionMap[ k ] = val


arguments[0] = "e:\\tools\\MinGW\\bin\\mingw32-make.exe";

print >>out, "Arguments:";
for argumnet in arguments:
    print >>out, argumnet;
print >>out, "\r\nEnvironment:";
for k in envirionMap:
    print >>out, "%s=%s"%( k , envirionMap[ k ] );
out.close();
    
os.spawnve(os.P_WAIT, arguments[0],  arguments, envirionMap );
#os.spawnve(os.P_WAIT, "/cygdrive/e/tools/MinGW/bin/mingw32-make.exe",  arguments, envirionMap )
#os.execve( "/cygdrive/e/tools/MinGW/bin/mingw32-make.exe",  arguments, envirionMap )
#os.exece( "/cygdrive/e/tools/MinGW/bin/mingw32-make.exe", " ".join( arguments ), envirionMap )