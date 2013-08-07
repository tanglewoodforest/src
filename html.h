#ifndef twf_html_h
#define twf_html_h

#include "string2.h"


text html( const char* );
void html_start( FILE *fp, const char*, const char*, const char* = "" );
void html_stop( FILE *fp, const char* = "" );


#endif // twf_html_h
