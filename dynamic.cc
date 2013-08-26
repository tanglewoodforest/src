#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"
#include "struct.h"
#include <string>

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

const dynamic_tag tag_index [] = 
{
	{ "day", is_day }, 
	{ "night", is_night }
};

/// Given the description and tag, parse!
void ParseTag(const char* tag, char* description, bool remove = false )
{
	char start[MAX_STRING_LENGTH];
	char end[MAX_STRING_LENGTH];

	sprintf(start, "<%s>", tag);
	sprintf(end, "</%s>", tag);
	
	std::string str (description);
	int is = str.find(start);
	int ie = str.find(end);
	
	if (is == -1 || ie == -1)
		return;

	int toStart = is + 2 + strlen( tag );
	int toEnd = max(1, ie - (2 + strlen( tag )));

	std::string data = str.substr(toStart, ie - toStart);
	std::string before = str.substr(0, is);
	std::string after = str.substr(ie + 3 + strlen( tag ));
		
	if ( remove )
		sprintf( description, "%s%s", before.c_str(), after.c_str() );
	else
		sprintf( description, "%s%s%s", before.c_str(), data.c_str(), after.c_str() );	
}

/// Given a provided description, parse any existing dynamic tags
char *GetDescription( const char *description ) 
{	
	char new_description[ 3*MAX_STRING_LENGTH ];
	sprintf( new_description, "%s", description );
	
	for (int i = 0; i < 2; i++ )
	{ 
		//bug( "Parsing Dynamic Description %s:%d", tag_index[i].tag, tag_index[i].func( ) );
		if ( tag_index[i].func( ) )
			ParseTag( tag_index[i].tag , new_description );
		else
			ParseTag( tag_index[i].tag, new_description, true );			
	}
	return new_description;
}

/// A way to provide formatted output without modifying the objects description
char *FormatOutput ( const char *description )
{
	const char *input = description;
	char paragraph [ 3*MAX_STRING_LENGTH ];
	char buf [ 3*MAX_STRING_LENGTH ];
	char line [ MAX_STRING_LENGTH ];

	*paragraph = '\0';
	*buf = '\0';	
	
    while( true ) 
	{
		input = one_line( input, line );
        if( !*line )
			break;
        strcat( buf, line );
	}
	
	format( line, buf, false );
	strcat( paragraph, line );

	return paragraph;
}