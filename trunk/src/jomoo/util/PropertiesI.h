#ifndef PROPERTIES_I_H
#define PROPERTIES_I_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include "Properties.h"

_jomoo_begin

class PropertiesI : public Properties
{
public:
    
    const ::std::string& getProperty(const ::std::string& key) const;
    const std::string& getPropertyWithDefault(const std::string&, const std::string&) const;
    int getPropertyAsInt(const std::string&) const;
    int getPropertyAsIntWithDefault(const std::string&, int) const;
    PropertiesPtr getPropertiesForPrefix(const std::string& , bool ) const;
    StringSeqPtr getPropertiesKeys( ) const;

    void setProperty(const std::string&, const std::string&);
    StringSeqPtr getCommandLineOptions() const;
    StringSeqPtr parseCommandLineOptions(const std::string&, const StringSeq&);
    StringSeqPtr parseBTCommandLineOptions(const StringSeq&);
    void load(const std::string&);
	void save( const ::std::string& ) const;
    PropertiesPtr clone();

    PropertiesI(const PropertiesI*);
    PropertiesI();
    PropertiesI( const StringSeq&);

private:

    void parseLine(const std::string&);

    void loadConfig();

    std::map<std::string, std::string> _properties;
};

_jomoo_end

#endif
