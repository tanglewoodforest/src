#include <stdio.h>
#include <ctype.h>
#include "html.h"


extern  const char *color_key;


static const char *const html_colors[] = {
  0,
  "<span style=\"font-weight:bold;\">",
  "<span style=\"text-decoration:underline;\">",
  "<span style=\"color:black;\">",
  "<span style=\"color:red;\">",
  "<span style=\"font-weight:bold; color:red;\">",
  "<span style=\"color:green;\">",
  "<span style=\"font-weight:bold; color:green;\">",
  "<span style=\"color:yellow;\">",
  "<span style=\"font-weight:bold; color:yellow;\">",
  "<span style=\"color:blue;\">",
  "<span style=\"font-weight:bold; color:blue;\">",
  "<span style=\"color:magenta;\">",
  "<span style=\"font-weight:bold; color:magenta;\">",
  "<span style=\"color:cyan;\">",
  "<span style=\"font-weight:bold; color:cyan;\">",
  "<span style=\"color:#a9a9a9;\">",
  "<span style=\"font-weight:bold; color:white;\">",
  "<span style=\"text-decoration:underline;\">",
  "<span style=\"font-weight:bold;\">"
};


text html( const char *twf )
{
  text html = "<pre>\n";

  unsigned spans = 0;

  while( char c = *twf++ ) {
    if( c == '\n' ) {
      html += "\n";
      continue;
    }
    if( c == '\r' ) {
      continue;
    }
    if( c == '<' ) {
      html += "&lt;";
      continue;
    }
    if( c == '>' ) {
      html += "&gt;";
      continue;
    }
    if( c == '&' ) {
      html += "&amp;";
      continue;
    }
    if( c == '\"' ) {
      html += "&quot;";
      continue;
    }
    if( c == '@' ) {
     c = *twf++;
     if( c == '@' || c == 0 ) {
       html += '@';
       continue;
     }
     if( c == 'I' ) {
       html += "  ";
       continue;
     }
     if( c == 'n' ) {
       while( spans != 0 ) {
	 html += "</span>";
	 --spans;
       }
       continue;
     }
     for( int i = 1; color_key[i]; ++i ) {
       if( color_key[i] == c ) {
	 while( spans != 0 ) {
	   html += "</span>";
	   --spans;
	 }
	 html += html_colors[i];
	 ++spans;
	 break;
       }
     }
     continue;
    }
    html += c;
  }

  html += "</pre>\n";

  return html;
}

void html_start( FILE *fp, const char *title, const char *header, const char *dir ){
        fprintf( fp,
        "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<meta charset=\"utf-8\">\n\t<title>Tanglewood Forest MUD - %s</title>\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\t<meta name=\"description\" content=\"\">\n\t<meta name=\"author\" content=\"\">\n\t\n\t<!-- Le styles -->\n\t<link href=\"%scss/bootstrap.min.css\" rel=\"stylesheet\">\n\t<style type=\"text/css\">\n\t\tbody {\n\t\t\tpadding-top: 60px;\n\t\t\tpadding-bottom: 40px;\n\t\t}\n\t\t.sidebar-nav {\n\t\t\tpadding: 9px 0;\n\t\t}\n\t\t\n\t\t@media (max-width: 980px) {\n\t\t\t/* Enable use of floated navbar text */\n\t\t\t.navbar-text.pull-right {\n\t\t\t\tfloat: none;\n\t\t\t\tpadding-left: 5px;\n\t\t\t\tpadding-right: 5px;\n\t\t\t}\n\t\t}\n\t</style>\n\t<link href=\"%scss/bootstrap-responsive-min.css\" rel=\"stylesheet\">\n\t<script src=\"%sjs/vendor/modernizr-2.6.2-respond-1.1.0.min.js\"></script>\n\t\n\t<!-- HTML5 shim, for IE6-8 support of HTML5 elements -->\n\t<!--[if lt IE 9]>\n\t\t<script src=\"%sjs/html5shiv.js\"></script>\n\t<![endif]-->\n</head>\n\n<body>\n\t<div class=\"navbar navbar-inverse navbar-fixed-top\">\n\t\t<div class=\"navbar-inner\">\n\t\t\t<div class=\"container\">\n\t\t\t\t<button type=\"button\" class=\"btn btn-navbar\" data-toggle=\"collapse\" data-target=\".nav-collapse\">\n\t\t\t\t\t<span class=\"icon-bar\"></span>\n\t\t\t\t\t<span class=\"icon-bar\"></span>\n\t\t\t\t\t<span class=\"icon-bar\"></span>\n\t\t\t\t</button>\n\t\t\t\t<a class=\"brand\" href=\"#\">Tanglewood Forest</a>\n\t\t\t\t<div class=\"nav-collapse collapse\">\n\t\t\t\t\t<ul class=\"nav\">\n\t\t\t\t\t\t<li><a href=\"%sindex.php\">Home</a></li>\n\t\t\t\t\t\t<li><a href=\"%splayers.html\">Player Directory</a></li>\n\t\t\t\t\t\t<li><a href=\"%swho.php\">Who's Online</a></li>\n\t\t\t\t\t\t<li><a href=\"%shelp/index.html\">Help</a></li>\n\t\t\t\t\t\t<li><a href=\"%sclans/index.html\">Clans</a></li>\n\t\t\t\t\t\t<li><a href=\"%scredits.html\">Credits</a></li>\n\t\t\t\t\t</ul>\n\t\t\t\t</div><!--/.nav-collapse -->\n\t\t\t</div>\n\t\t</div>\n\t</div>\n\t\n\t<div class=\"container\">\n\t\n\t\t<h2>%s</h2>\n",
        title, dir, dir, dir, dir, dir, dir, dir, dir, dir, dir, header);

fprintf( fp, "<hr>\n" );
}

void html_stop( FILE *fp, const char *dir ){
        fprintf( fp,
                "\n\n<hr>\n\n<footer><p>&copy;2013 Tanglewood Forest - The Fighting Ferret - Clint Milner</p></footer>\n\n</div><!--/.container-->\n\n\t<!-- Le javascript\n\t================================================== -->\n\t<!-- Placed at the end of the document so the pages load faster -->\n        <script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js\"></script>\n\t<script src=\"%sjs/vendor/bootstrap.min.js\"></script>\t\n</body>\n</html>\n",
                dir );
        fclose( fp );
}

