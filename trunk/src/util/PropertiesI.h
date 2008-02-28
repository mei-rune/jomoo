// **********************************************************************
//
// Copyright (c) 2003-2005 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_PROPERTIES_I_H
#define ICE_PROPERTIES_I_H

#include <Properties.h>



class PropertiesI : public Properties
{
public:
    
    virtual const std::string& getProperty(const std::string&) const;
    virtual const std::string& getPropertyWithDefault(const std::string&, const std::string&) const;
    virtual int getPropertyAsInt(const std::string&) const;
    virtual int getPropertyAsIntWithDefault(const std::string&, int) const;
    virtual PropertiesPtr getPropertiesForPrefix(const std::string& , bool ) const;
    virtual void setProperty(const std::string&, const std::string&);
    virtual StringSeqPtr getCommandLineOptions() const;
    virtual StringSeqPtr parseCommandLineOptions(const std::string&, const StringSeq&);
    virtual StringSeqPtr parseBTCommandLineOptions(const StringSeq&);
    virtual void load(const std::string&);
    virtual PropertiesPtr clone();

private:

    PropertiesI(const PropertiesI*);
    PropertiesI();
    PropertiesI( const StringSeq&);

    friend  BTNM_Export_C PropertiesPtr createProperties();
    friend  BTNM_Export_C PropertiesPtr createProperties(StringSeq&);
    friend  BTNM_Export_C PropertiesPtr createProperties(int&, char*[]);

    void parseLine(const std::string&);

    void loadConfig();

    std::map<std::string, std::string> _properties;
};


#endif
