#include <iostream>
#include <fstream>
#include "genHTML.hpp"

using namespace std;

bool genHTML::generate(std::string table_type, int n){
    ofstream html_file("index.html");
    if(!html_file.is_open()){
        cout << "Unable to open file" << endl;
        return false;
    }
    // now write html to file:
    html_file << "<!-- Generated with genHTML.hpp -->" << endl
         << "<!doctype html>" << endl
         << "<html>" << endl
         << "<head>" << endl
         << "<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">" << endl
         << "<title> Emb Proj Web Server </title>" << endl
         << "</head>" << endl
         << "<body style=\"font-size:40px; text-align:center; margin:0; background-color: #4B4B4B\">" << endl
         << "<div class=\"row\"> " << endl
         << "<div class=\"w-50 rounded\" style=\"background-color:#007bff; margin-top: 20px; margin-left:auto; margin-right:auto; padding:10px; color: white;\">Real-time Embedded Systems Course Project</div>" << endl
         << "</div>" << endl
         << "<div class=\"row\">" << endl
         << "<div class=\"w-50 shadow rounded\" style=\"border:solid 1px white; margin-left:auto; margin-right:auto; padding:10px; background-color: white;\">" << endl
         << "<img class=\"w-75 rounded\" src=\"./img.jpg\" style=\"border: solid #007bff 2px;\">" << endl
         << "<form method=\"GET\" action=\"index.html\">" << endl
         << "<input type=\"hidden\" name=\"update\" value=\"true\">" << endl
         << "<input class=\"btn btn-primary\" style=\"font-size:18px\" type=\"submit\" value=\"Update image\">" << endl
         << "</form>" << endl
         << "</div>" << endl
         << "</div>" << endl
         << "<div class=\"row\">" << endl
         << "<div class=\"w-50 rounded\" style=\"background-color:#007bff; font-size:40px; color: white; margin-left: auto; margin-right: auto; margin-top: 30px;\">" << endl
         << "Database" << endl
         << "</div>" << endl
         << "</div>" << endl
         << "<div class=\"row\">" << endl
         << "<div class=\"w-50 shadow rounded\" style=\"border:solid 1px white; margin-left:auto; margin-right:auto; background-color: white; padding: 10px; margin-bottom: 50px\">" << endl
         << "<form method=\"GET\" action=\"index.html\"> " << endl
         << "<div style=\"display: inline-block;\"> " << endl
         << "<div class=\"col form-check\"> " << endl
         << "<input class=\"form-check-input\" type=\"radio\" name=\"table_type\" value=\"camera\" id=\"flexRadioDefault1\" style=\"vertical-align: middle; text-align: center; margin-left: -1px;\" checked> " << endl
         << "<label class=\"form-check-label\" for=\"flexRadioDefault1\" style=\"font-size: 20px\">" << endl
         << "Camera" << endl
         << "</label>" << endl
         << "</div>" << endl
         << "</div>" << endl
         << "<div style=\"display: inline-block;\">" << endl
         << "<div class=\"col form-check\"> " << endl
         << "<input class=\"form-check-input\" type=\"radio\" name=\"table_type\" value=\"audio\" id=\"flexRadioDefault2\" style=\"vertical-align: bottom; text-align: center; margin-left: -1px;\"> " << endl
         << "<label class=\"form-check-label\" for=\"flexRadioDefault2\" style=\"font-size: 20px\"> " << endl
         << "Audio" << endl
         << "</label>" << endl
         << "</div>" << endl
         << "</div>" << endl
         << "<div class=\"row\" style=\"margin-top: 20px;\"> " << endl
         << "<input class=\"rounded\" type=\"input\" name=\"db_rows\" placeholder=\"1\" style=\"width: 150px; height: 60px; font-size: 22px; margin-left: auto; margin-right: 30px; margin-top: 0; margin-bottom: 10px; display: block; vertical-align: middle; text-align: center;\"> " << endl
         << "<input class=\"btn btn-primary\" style=\"font-size:22px; width: 150px; height: 50px; margin-right: auto; margin-left: 30px; margin-top: 5px; margin-bottom: 40px; vertical-align: middle;\" type=\"submit\" value=\"show\"> " << endl
         << "</div>" << endl
         << "</form>" << endl
         << "<div>" << endl
         << "generated for" << table_type << endl;
    html_file.close();
    return true;
}
