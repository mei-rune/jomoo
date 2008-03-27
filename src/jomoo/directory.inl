
DWORD get_application_directory(tchar *szModName, DWORD Size, bool slash )
{
	DWORD ps = GetModuleFileName(NULL, szModName, Size);
	while(ps > 0 && szModName[ps-1] != '\\' && szModName[ps-1] != '/' ) ps--;
	szModName[ps] = '\0';
	if( !slash && ps> 0 )
	{
		ps --;
		szModName[ps] = '\0';
	}

	return ps;
}

tstring get_application_directory( bool slash )
{
	tchar path[ MAX_PATH ] = "";
	get_application_directory( path, MAX_PATH ,slash );
	return tstring( path );
}

tstring simplify(const tstring& pa)
{
	tstring result = pa;

	tstring::size_type pos;

#ifdef _WIN32
	for(pos = 0; pos < result.size(); ++pos)
	{
		if(result[pos] == '\\')
		{
			result[pos] = '/';
		}
	}
#endif

	pos = 0;
	while((pos = result.find("//", pos)) != tstring::npos)
	{
		result.erase(pos, 1);
	}

	pos = 0;
	while((pos = result.find("/./", pos)) != tstring::npos)
	{
		result.erase(pos, 2);
	}

	if(result.substr(0, 2) == "./")
	{
		result.erase(0, 2);
	}

	if(result == "/." ||
		result.size() == 4 && isalpha(result[0]) && result[1] == ':' && result[2] == '/' && result[3] == '.')
	{
		return result.substr(0, result.size() - 1);
	}

	if(result.size() >= 2 && result.substr(result.size() - 2, 2) == "/.")
	{
		result.erase(result.size() - 2, 2);
	}

	if(result == "/" || result.size() == 3 && isalpha(result[0]) && result[1] == ':' && result[2] == '/')
	{
		return result;
	}

	if(result.size() >= 1 && result[result.size() - 1] == '/')
	{
		result.erase(result.size() - 1);
	}

	return result;
}

bool isAbsolute(const tstring& pa)
{
	unsigned i = 0;
	while(isspace(pa[i]))
	{
		++i;
	}
#ifdef _WIN32
	return pa[i] == '\\' || pa[i] == '/' || pa.size() > i + 1 && isalpha(pa[i]) && pa[i + 1] == ':';
#else
	return pa[i] == '/';
#endif
}

bool isRoot(const tstring& pa)
{
	tstring path = simplify(pa);
#ifdef _WIN32
	return path == "/" || path.size() == 3 && isalpha(path[0]) && path[1] == ':' && path[2] == '/';
#else
	return path == "/";
#endif
}

bool isDirectory(const tstring& pa)
{
	struct stat buf;
	if(stat(pa.c_str(), &buf) == -1)
	{
		ThrowException1( RuntimeException, "不能stat `" + pa + "':\n" + lastError() );
	}

	return (S_ISDIR(buf.st_mode)) != 0 ;
}

tstring getBasename(const tstring& pa)
{
	const tstring path = simplify(pa);

	tstring::size_type pos = path.rfind('/');
	if(pos == tstring::npos)
	{
		return path;
	}
	else
	{
		return path.substr(pos + 1);
	}
}

tstring getDirectoryName(const tstring& pa)
{
	const tstring path = simplify(pa);

	tstring::size_type pos = path.rfind('/');
	if(pos == tstring::npos)
	{
		return tstring();
	}
	else
	{
		return path.substr(0, pos);
	}
}

void rename(const tstring& fromPa, const tstring& toPa)
{
	const tstring fromPath = simplify(fromPa);
	const tstring toPath = simplify(toPa);

	::remove(toPath.c_str()); // We ignore errors, as the file we are renaming to might not exist.

	if(::rename(fromPath.c_str(), toPath.c_str()) == -1)
	{
		ThrowException1( RuntimeException,  "不能将文件 `" + fromPath + "' 重命名为  `" + toPath + "': " + lastError() );
	}
}

void remove(const tstring& pa)
{
	const tstring path = simplify(pa);
	//#ifdef _WIN32
	//	struct _stat  buf;
	//    if(_stat(path.c_str(), &buf) == -1)
	//#else
	struct stat buf;
	if(stat(path.c_str(), &buf) == -1)
		//#endif
	{
		ThrowException1( RuntimeException,  "不能stat `" + path + "':\n" + lastError() );
	}

	if(S_ISDIR(buf.st_mode))
	{
#ifdef _WIN32
		if(_rmdir(path.c_str()) == -1)
#else
		if(rmdir(path.c_str()) == -1)
#endif
		{
			ThrowException1( RuntimeException,  "不能删除目录 `" + path + "':\n" + lastError() );
		}
	}
	else
	{
		if(::remove(path.c_str()) == -1)
		{
			ThrowException1( RuntimeException, "不能删除文件 `" + path + "':\n" + lastError());
		}
	}
}

void removeRecursive(const tstring& pa)
{
	const tstring path = simplify(pa);
	struct stat buf;
	if(stat(path.c_str(), &buf) == -1)
	{
		ThrowException1( RuntimeException, "不能stat `" + path + "':\n" + lastError() );
	}

	if(S_ISDIR(buf.st_mode))
	{
		StringSeq paths = readDirectory(path);
		for(StringSeq::const_iterator p = paths.begin(); p != paths.end(); ++p)
		{
			removeRecursive(path + '/' + *p);
		}

		if(!isRoot(path))
		{
#ifdef _WIN32
			if(_rmdir(path.c_str()) == -1)
#else
			if(rmdir(path.c_str()) == -1)
#endif
			{
				ThrowException1( RuntimeException, "不能删除目录 `" + path + "':\n" + lastError() );
			}
		}
	}
	else
	{
		if(::remove(path.c_str()) == -1)
		{
			ThrowException1( RuntimeException, "不能删除文件 `" + path + "':\n" + lastError() );
		}
	}
}

class filefinder_ptr
{
public:
	filefinder_ptr( intptr_t h )
		: h_( h )
	{
	}
	~filefinder_ptr()
	{
		if( -1 != h_ )
			_findclose(h_);
	}
	
	intptr_t get() const
	{
		return h_;
	}

private:
	intptr_t h_;
};

inline bool is_null( const filefinder_ptr& ptr)
{
	return ( -1 == ptr.get());
}



StringSeq readDirectory(const tstring& pa)
{
	const tstring path = simplify(pa);

#ifdef _WIN32

	struct _finddata_t data;
	filefinder_ptr ph( _findfirst(simplify((path + "/*")).c_str(), &data) );
	if( is_null(ph) )
	{
		ThrowException1( RuntimeException, "不能读目录 `" + path + "':\n" + lastError() );
	}

	StringSeq result;

	while(true)
	{
		tstring name = data.name;
		//assert(!name.empty());

		if(name != ".." && name != ".")
		{
			result.push_back(name);
		}

		if(_findnext(ph.get(), &data) == -1)
		{
			if(errno == ENOENT)
			{
				break;
			}

			tstring ex = "不能读目录 `" + path + "':\n" + lastError();
			
			ThrowException1( RuntimeException, ex );
		}
	}


	std::sort(result.begin(), result.end());

	return result;

#else

	struct dirent **namelist;
	int n = scandir(path.c_str(), &namelist, 0, alphasort);
	if(n < 0)
	{
		ThrowException1( RuntimeException, "不能读目录 `" + path + "':\n" + lastError() );
	}

	StringSeq result;
	result.reserve(n - 2);

	for(int i = 0; i < n; ++i)
	{
		tstring name = namelist[i]->d_name;
		assert(!name.empty());

		free(namelist[i]);

		if(name != ".." && name != ".")
		{
			result.push_back(name);
		}
	}

	free(namelist);
	return result;

#endif
}

void createDirectory(const tstring& pa)
{
	const tstring path = simplify(pa);

#ifdef _WIN32
	if(_mkdir(path.c_str()) == -1)
#else
	if(mkdir(path.c_str(), 0777) == -1)
#endif
	{
		if(errno != EEXIST)
		{
			ThrowException1( RuntimeException, "不能创建目录 `" + path + "':\n" + lastError() );
		}
	}
}

void createDirectoryRecursive(const tstring& pa)
{
	const tstring path = simplify(pa);

	tstring dir = getDirectoryName(path);
	if(!dir.empty())
	{
		createDirectoryRecursive(dir);
	}

#ifdef _WIN32
	if(_mkdir(path.c_str()) == -1)
#else
	if(mkdir(path.c_str(), 0777) == -1)
#endif
	{
		if(errno != EEXIST)
		{
			ThrowException1( RuntimeException, "不能创建目录 `" + path + "':\n" + lastError() );
		}
	}
}

tstring combinePath(const tstring& path1,const tstring& path2)
{
	return simplify(path1 + "/" + path2 );
}

tstring getExtension (const tstring& pa)
{
	const tstring path = simplify(pa);

	tstring::size_type dotPos = path.rfind('.');
	tstring::size_type slashPos = path.rfind('/');

	if(dotPos == tstring::npos || slashPos != tstring::npos && slashPos > dotPos)
	{
		return tstring();
	}
	else
	{
		return path.substr(dotPos + 1);
	}
}

tstring getFileName(const tstring& pa)
{
	const tstring path = simplify(pa);

	tstring::size_type slashPos = path.rfind('/');

	if(slashPos == tstring::npos)
	{
		return path;
	}
	else
	{
		return path.substr( slashPos + 1 );
	}
}

tstring getFileNameWithoutExtension(const tstring& pa)
{
	tstring path = getFileName(pa);
	tstring::size_type dotPos = path.rfind('.');

	if(dotPos == tstring::npos )
	{
		return path;
	}
	else
	{
		return path.substr( 0, dotPos);
	}
}