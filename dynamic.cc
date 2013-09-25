#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"
#include "struct.h"
#include <string>
#include <algorithm>

// Dodger - Initial implementation 8/25/2013 - I'm a windows programmer, so look out for memory or string problems

typedef bool tag_func (  );

class dynamic_tag
{
    public:
        const char*  tag;		
        tag_func* func;
};

bool is_day(  )
{	
    return weather.is_day( );
}

bool is_night(  )
{
    return !weather.is_day( );
}

bool is_true ( )
{
    return true;
}

const dynamic_tag tag_index [] = 
{
    { "day", is_day }, 
    { "night", is_night },
    { "newline", is_true }
};

/// Given the description and tag, parse!
std::string ParseTag(const char* tag, std::string description, bool remove = false )
{
    char start[MAX_STRING_LENGTH];
    char end[MAX_STRING_LENGTH];

    sprintf(start, "<%s>", tag);
    sprintf(end, "</%s>", tag);
    
    std::string str (description);

    int is = str.find(start);
    int ie = str.find(end);
    
	//bug ( "Debug PT: %d %d", is, ie );
	
    if (is == -1 || ie == -1)
        return description;

    int toStart = is + 2 + strlen( tag );
    //int toEnd = max(1, ie - (2 + strlen( tag )));

    std::string data = str.substr(toStart, ie - toStart);
    std::string before = str.substr(0, is);
    std::string after = str.substr(ie + 3 + strlen( tag ));
        
    std::string newstring;

    if ( remove )
    {
        newstring = before;
        newstring.append(after);
    }

        //sprintf( description, "%s%s", before.c_str(), after.c_str() );
    else
    {
        newstring = before;
        newstring.append(data);
        newstring.append(after);
        //sprintf( description, "%s%s%s", before.c_str(), data.c_str(), after.c_str() );	
    }
    return newstring;
}

/// Given a provided description, parse any existing dynamic tags
std::string GetDescription( const char *description ) 
{	
    std::string new_description(description);
    //sprintf( new_description, "%s", description );
    
    //char *pString = new_description;

    for (int i = 0; i < 2; i++ )
    { 
        //bug( "Parsing Dynamic Description %s:%d", tag_index[i].tag, tag_index[i].func( ) );
        if ( tag_index[i].func( ) )
            new_description = ParseTag( tag_index[i].tag, new_description );
        else
            new_description = ParseTag( tag_index[i].tag, new_description, true );			
    }

    //std::string ret (new_description);
	//bug ( "%s", new_description );
    return new_description;
}

std::string WordWrap(std::string a, int columns)
{
    const int WIDTH = columns; // may take this line out if I implement global width
    int index;
    std::string wrapped = "";
    while(a.length() >= columns)
    {
        index = a.substr(0,WIDTH).find_last_of(" ");
        wrapped.append(a.substr(0,index));
        wrapped.append("\n");
        a = a.substr(index+1);
    }
    wrapped.append(a);
    wrapped.append("\n");
    return wrapped;
}

std::string replaceinString(std::string str, std::string tofind, std::string toreplace)
{
    size_t position = 0;
    for ( position = str.find(tofind); position != std::string::npos; position = str.find(tofind,position) )
    {
            str.replace(position ,1, toreplace);
    }
    return(str);
}

std::string InnerTrim(std::string value)
{
	std::string str (value);

	int loc = -1;
	while((loc = str.find("  ")) != std::string::npos)  //Two spaces here
	{
		str.replace(loc, 2, " "); //Single space in quotes
	}

	return str;
}

/// A way to provide formatted output without modifying the objects description
std::string FormatOutput ( char *description, int columns )
{	
    std::string str ( description );
    std::string clean (str);
		
	clean = replaceinString(str, "\n", " ");
    clean = replaceinString(clean, "\r", " ");
	clean = InnerTrim(clean);

	//replaceinString(clean, "  ", " ");    
    
    return WordWrap( clean, columns );

    //////const char *input = description;
    //////char paragraph[ 3*MAX_STRING_LENGTH ];
    //////char buf[ 3*MAX_STRING_LENGTH ];
    //////char line [ MAX_STRING_LENGTH ];

    ////////char *pString = paragraph;

    //////*paragraph = '\0';
    //////*buf = '\0';	
    //////
    //////while( true ) 
    //////{
    //////    input = one_line( input, line );
    //////    if( !*line )
    //////        break;
    //////    strcat( buf, line );		
    //////}
    //////
    //////bug ( buf );

    //////format( line, buf, false );
    //////strcat( paragraph, line );
    //////    
    //////std::string ret (paragraph);
    //////return ret;
}

