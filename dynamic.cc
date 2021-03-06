#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "define.h"
#include "struct.h"
#include <string>
#include <algorithm>

typedef bool tag_func ( room_data* room );

class dynamic_tag
{
public:
    const char*  tag;       
    tag_func* func;
};

bool is_day( room_data* room ) { return weather.is_day( ); }

bool is_night( room_data* room ) { return !weather.is_day( ); }

bool is_fullmoon( room_data* room )
{   
    if ( room == NULL )
        return false;

    if( room->is_indoors( ) || is_set( room->room_flags, RFLAG_UNDERGROUND ) )
        return false;

    if ( weather.moon_phase == 0 )
        return true;
    else
        return false;

}

bool is_newmoon( room_data* room )
{   
    if ( room == NULL )
        return false;

    if( room->is_indoors( ) || is_set( room->room_flags, RFLAG_UNDERGROUND ) )
        return false;

    if ( weather.moon_phase == 4 )
        return true;
    else
        return false;

}

bool is_true ( room_data* room) { return true; }

bool is_exit_open_north ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_NORTH)
        {           
            if( !is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_open_east ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_EAST)
        {           
            if( !is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_open_south ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_SOUTH)
        {           
            if( !is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_open_west ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_WEST)
        {           
            if( !is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_closed_north ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_NORTH)
        {           
            if( is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_closed_east ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_EAST)
        {           
            if( is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_closed_south ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_SOUTH)
        {           
            if( is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_exit_closed_west ( room_data* room )
{
    if ( room == NULL )
        return false;

    for( int i = 0; i < room->exits; ++i ) 
    {       
        if ( room->exits[i]->direction == DIR_WEST)
        {           
            if( is_set( room->exits[i]->exit_info, EX_CLOSED ))
            {               
                return true;
            }
        }
    }

    return false;
}

bool is_winter ( room_data* room ) { return weather.month >= 11 || weather.month < 2; }

bool is_spring ( room_data* room ) { return weather.month >= 2 && weather.month < 5; }

bool is_summer ( room_data* room ) { return weather.month >= 5 && weather.month < 8; }

bool is_autumn ( room_data* room ) { return weather.month >= 8 && weather.month < 11; }

bool is_reset0 ( room_data* room )
{
    if( is_set( room->room_flags, RFLAG_RESET0 ) )
        return true;

    return false;
}

bool is_status0 ( room_data* room )
{
    if( is_set( room->room_flags, RFLAG_STATUS0 ) )
        return true;

    return false;
}

bool is_reset1 ( room_data* room )
{
    if( is_set( room->room_flags, RFLAG_RESET1 ) )
        return true;

    return false;
}

bool is_status1 ( room_data* room )
{
    if( is_set( room->room_flags, RFLAG_STATUS1 ) )
        return true;

    return false;
}

bool is_reset2 ( room_data* room )
{
    if( is_set( room->room_flags, RFLAG_RESET2 ) )
        return true;

    return false;
}

bool is_status2 ( room_data* room )
{
    if( is_set( room->room_flags, RFLAG_STATUS2 ) )
        return true;

    return false;
}

#define MAX_TAG      23
const dynamic_tag tag_index [] = 
{
    { "day", is_day }, 
    { "night", is_night },
    { "newline", is_true },
    { "open=north", is_exit_open_north },
    { "open=east", is_exit_open_east },
    { "open=south", is_exit_open_south },
    { "open=west", is_exit_open_west },
    { "closed=north", is_exit_closed_north },
    { "closed=east", is_exit_closed_east },
    { "closed=south", is_exit_closed_south },
    { "closed=west", is_exit_closed_west },
    { "winter", is_winter },
    { "spring", is_spring },
    { "summer", is_summer },
    { "autumn", is_autumn },
    { "fullmoon", is_fullmoon },
    { "newmoon", is_newmoon },
    { "reset0", is_reset0 },
    { "status0", is_status0 },
    { "reset1", is_reset1 },
    { "status1", is_status1 },
    { "reset2", is_reset2 },
    { "status2", is_status2 }
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

    if (is == -1 || ie == -1)
        return description;

    int toStart = is + 2 + strlen( tag );    

    std::string data = str.substr(toStart, ie - toStart);
    std::string before = str.substr(0, is);
    std::string after = str.substr(ie + 3 + strlen( tag ));

    std::string newstring;

    if ( remove )
    {
        newstring = before;
        newstring.append(after);
    }
    else
    {
        newstring = before;
        newstring.append(data);
        newstring.append(after);        
    }
    return newstring;
}

/// Given a provided description, parse any existing dynamic tags
std::string GetDescription( const char *description, room_data* room ) 
{   
    std::string new_description(description);

    for (int i = 0; i < MAX_TAG; i++ )
    {         
        if ( tag_index[i].func( room ) )
            new_description = ParseTag( tag_index[i].tag, new_description );
        else
            new_description = ParseTag( tag_index[i].tag, new_description, true );          
    }

    return new_description;
}

// Add newline to provided string at column length
std::string WordWrap(std::string a, int columns)
{
    const int WIDTH = columns;
    int index;
    std::string wrapped = "";

    while(a.length() >= columns)
    {
        index = a.substr(0,WIDTH).find_last_of(" ");
        wrapped.append(a.substr(0,index));
        wrapped.append("\n\r");
        a = a.substr(index+1);
    }

    wrapped.append(a);
    wrapped.append("\n");
    return wrapped;
}

// Replace a match in a string with provided value
std::string replaceinString(std::string str, std::string tofind, std::string toreplace)
{
    size_t position = 0;
    for ( position = str.find(tofind); position != std::string::npos; position = str.find(tofind,position) )
    {
        str.replace(position, 1, toreplace);
    }
    return(str);
}

/// Remove multiple spaces from a string
std::string InnerTrim(std::string value)
{
    std::string str (value);

    int loc = -1;
    while((loc = str.find("  ")) != std::string::npos)
    {
        str.replace(loc, 2, " ");
    }

    return str;
}

/// A way to provide formatted output without modifying the objects description
std::string FormatOutput ( char *description, int columns )
{   
    std::string str ( description );
    std::string clean (str);

// Remove all crlf
    clean = replaceinString(str, "\n", " ");
    clean = replaceinString(clean, "\r", " ");

// Remove multiple spaces
    clean = InnerTrim(clean);

    return WordWrap( clean, columns );   
}


