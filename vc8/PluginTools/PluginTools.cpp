// PluginTools.cpp : 定义控制台应用程序的入口点。
//

# include "stdafx.h"
# include "Hazel.PluginManager/IPluginManager.H"
# include "Hazel.PluginManager/PluginInfoDOM.H"
# include "Hazel.PluginManager/ModuleDescriptorTarget.H"
# include "Hazel.Base/directory.H"
# include <iostream>
# include <string>


class Walker : public _seal PluginInfoWalker
{
public:

	virtual void onPlugInfo( _seal ModuleDescriptor& info )
	{
	}

	virtual void onModule( _seal IModule& info )
	{
		info.query();
	}

	virtual void onModuleReg( _seal IModuleReg& info )
	{
	}

	virtual void onModuleCache( _seal IModuleCache& info )
	{
		info.feelbackDirectory();
	}
};

class SaveWalker : public _seal PluginInfoWalker
{
public:

	virtual void onPlugInfo( _seal ModuleDescriptor& info )
	{
	}

	virtual void onModule( _seal IModule& info )
	{
	}

	virtual void onModuleReg( _seal IModuleReg& info )
	{
	}

	virtual void onModuleCache( _seal IModuleCache& info )
	{
		_seal IModuleDescriptorBuilderPtr bulder = _seal createModuleDescriptorBuilder( _seal getPluginManager() );
		_seal ModuleDescriptorPtr	descriptor = info.cache ( *bulder );
		_seal ModuleDescriptorTarget target( _hazel simplify(  info.directory() + "/.cache" ) );
		target << *descriptor;

	}
};

class FeedBack : public _seal IPluginFeedback
{
public:

	//   enum FeedbackCode
	//   {
	//StatusLoading,		//
	//StatusUnloading,	//
	//StatusEntries,		//
	//StatusAttaching,	//
	//StatusDetaching,	//
	//StatusQuerying,		//

	//ErrorLoadFailure,	//
	//ErrorEntryFailure,	//
	//ErrorBadModule,		//
	//ErrorBadCacheFile,	//
	//ErrorNoFactory,		//

	//Other
	//   };

	virtual void feedback( int code,
		const tstring &scope,
		const _hazel Exception& error )
	{
		tstring explanation = error.what();
		feedback( code, scope, explanation );
	}

	virtual void feedback( int code,
		const tstring &scope,
		const tstring& explanation )
	{
		if ( code == StatusLoading)
			std::cerr << "Note: Loading " << scope << "\n" << explanation <<std::endl;

		else if ( code == ErrorLoadFailure)
			std::cerr << "  *** WARNING: module `" << scope
			<< "' failed to load for the following reason\n\t"
			<< explanation << "\n";

		else if (code == ErrorBadModule)
			std::cerr << "  *** WARNING: module `" << scope
			<< "' ignored until problems with it are fixed, reason was\n\t"
			<< explanation << std::endl;

		else if (code == ErrorBadCacheFile)
			std::cerr << "  *** WARNING: cache file " << scope
			<< " is corrupted, reason was\n\t"
			<< explanation << std::endl;

		else if (code == ErrorEntryFailure)
			std::cerr << "  *** WARNING: module `" << scope
			<< "' does not have the required entry point, reason was\n\t"
			<< explanation << std::endl;
		else
			std::cout << "  *** WARING: unknown error in " << scope << ", reason was\n\t"
			<< explanation << std::endl;
	}

	virtual void feedback( int code,
		const tstring &scope )
	{
		if ( code == StatusLoading)
			std::cerr << "Note: Loading " << scope << std::endl;

		else if ( code == ErrorLoadFailure)
			std::cerr << "  *** WARNING: module `" << scope
			<< "' failed to load for the unknow reason"<< std::endl;

		else if (code == ErrorBadModule)
			std::cerr << "  *** WARNING: module `" << scope
			<< "' ignored until problems with it are fixed."<< std::endl;

		else if (code == ErrorBadCacheFile)
			std::cerr << "  *** WARNING: cache file " << scope
			<< " is corrupted."<< std::endl;

		else if (code == ErrorEntryFailure)
			std::cerr << "  *** WARNING: module `" << scope
			<< "' does not have the required entry point." << std::endl;
		else
			std::cout << "  *** WARING: unknown error in " << scope << std::endl;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	_seal IPluginManager& manager = _seal getPluginManager();

	manager.addFeedback( _seal FeedbackCB( new FeedBack() ) );
	manager.initialize();
	Walker walker;
	manager.walk(walker);

	SaveWalker saver;
	manager.walk(saver);


	return EXIT_SUCCESS;
}
