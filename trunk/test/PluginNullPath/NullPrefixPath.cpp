//<<<<<< INCLUDES                                                       >>>>>>

#include "BOE/PluginManager/PluginManager.h"
#include "SealBase/ShellEnvironment.h"
#include "SealBase/SubProcess.h"
#include "SealBase/Signal.h"
#include "SealBase/Argz.h"
#include <cstdlib>

//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>
//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

using namespace seal;
int main (int argc, char **argv)
{
    Signal::handleFatal (argv [0]);

    if (argc == 1)
    {
	ShellEnvironment env;
	env.set ("SEAL_PLUGINS", ":" + env.get ("SEAL_PLUGINS"));
	SubProcess sub (Argz (0+argv [0], "sub").argz ());
	return sub.wait ();
    }
    else if (argc == 2 && ! strcmp (argv [1], "sub"))
    {
	PluginManager::get ()->initialise ();
	return EXIT_SUCCESS;
    }
    else
	abort ();
}
