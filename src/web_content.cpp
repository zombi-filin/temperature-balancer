#include "web_content.h"

String int2str(int val)
{
    return (val < 10 ? "0" : "") + String(val);
}

String HTML_header()
{
    String str = "<!DOCTYPE html>\n<html  style=\"height: 100%;\">\n";
    str += "<head>\n";
    str += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n";
    str += "<title>Balancer</title>\n";
    str += "</head>\n";
    str += "<body style=\"background-color:black; color:white; height: 100%; margin: 0px;\">\n";
    return str;
}

String HTML_footer()
{
    String str = "</body>\n</html>";
    return str;
}

String HTML_main_page(DS3231_datetime_t* datetime, float current_temp)
{
    String str = HTML_header();
    str += "<div style=\"text-align: center; font-size: 5vh; padding: 1vh;\">\n";
    str += int2str(datetime->day_month) + "." + int2str(datetime->month) + "." + String(datetime->year);
    str += "</div>\n";
    
    str += "<div style=\"text-align: center; font-size: 5vh; padding: 1vh;\">\n";
    str += int2str(datetime->hour) + ":" + int2str(datetime->minute) + ":" + int2str(datetime->second);
    str += "</div>\n";

    str += "<div style=\"text-align: center; font-weight: bold; font-size: 30vh; padding: 5vh;\">\n";
    str += String(current_temp, 1);
    str += "</div>\n";  
    
    str += "<script type=\"text/javascript\">\n";
    str += "setTimeout(function(){window.location.reload(1);}, 1000);\n";
    str += "</script>\n";
    str += HTML_footer();
    return str;

}