//<<<<<< INCLUDES                                                       >>>>>>

#include "PluginManager/PluginManager.h"

using namespace seal;
int main (int argc, char **argv)
{
    Signal::handleFatal (argv [0]);

    if (argc == 1)
    {
	ShellEnvironment env;
	env.set ("SEAL_PLUGINS", env.get ("SEAL_PLUGINS") + ":");
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
