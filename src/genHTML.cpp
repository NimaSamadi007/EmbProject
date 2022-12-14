#include <iostream>
#include <fstream>
#include "genHTML.hpp"
#include "db_handler.hpp"
#include <mysql.h>

using namespace std;

bool genHTML::generate(std::string table_type, int n){
    DBHandler db_handler("test", "123456", "sensors");
    MYSQL_RES* res;
    MYSQL_ROW row;
    char db_query[200];
    ofstream html_file("index.html");
    if(!html_file.is_open()){
        cout << "Unable to open file" << endl;
        return false;
    }
    // write static part of html to file:
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
         << "<input class=\"rounded\" type=\"input\" name=\"db_rows\" value=\"1\" placeholder=\"1\" style=\"width: 150px; height: 60px; font-size: 22px; margin-left: auto; margin-right: 30px; margin-top: 0; margin-bottom: 10px; display: block; vertical-align: middle; text-align: center;\"> " << endl
         << "<input class=\"btn btn-primary\" style=\"font-size:22px; width: 150px; height: 50px; margin-right: auto; margin-left: 30px; margin-top: 5px; margin-bottom: 40px; vertical-align: middle;\" type=\"submit\" value=\"show\"> " << endl
         << "</div>" << endl
         << "</form>" << endl
         << "<div>" << endl;
        // generate dynamic part
        if(table_type == "camera"){
            sprintf(db_query, "SELECT * FROM ( SELECT * FROM camera ORDER BY id DESC LIMIT %d) sub ORDER BY id ASC", n);
            db_handler.readFromDB(db_query, &res);
            html_file << "<table class=\"table table-striped table-hover\" style=\"font-size: 18px\">" << endl
                      << "<thead>" << endl
                      << "<tr>" << endl
                      << "<th scope=\"col\">id</th>" << endl
                      << "<th scope=\"col\">time</th>" << endl
                      << "<th scope=\"col\">number of faces</th>" << endl
                      << "</tr>" << endl
                      << "</thead>" << endl
                      << "<tbody>" << endl;
            while((row = mysql_fetch_row(res))){
                html_file << "<tr>" << endl
                          << "<th scope=\"row\">" << row[0] << "</th>" << endl
                          << "<td>" << row[1] << "</td>" << endl
                          << "<td>" << row[2] << "</td>" << endl
                          << "</tr>" << endl;
            }
            html_file << "</tbody>" << endl
                      << "</table>" << endl;
            mysql_free_result(res);      
        }
        else if(table_type == "audio"){
            sprintf(db_query, "SELECT * FROM ( SELECT * FROM sound ORDER BY id DESC LIMIT %d) sub ORDER BY id ASC", n);
            db_handler.readFromDB(db_query, &res);
            html_file << "<table class=\"table table-striped table-hover\" style=\"font-size: 18px\">" << endl
                      << "<thead>" << endl
                      << "<tr>" << endl
                      << "<th scope=\"col\">id</th>" << endl
                      << "<th scope=\"col\">time</th>" << endl
                      << "<th scope=\"col\">sound amplitude</th>" << endl
                      << "</tr>" << endl
                      << "</thead>" << endl
                      << "<tbody>" << endl;
            while((row = mysql_fetch_row(res))){
                html_file << "<tr>" << endl
                          << "<th scope=\"row\">" << row[0] << "</th>" << endl
                          << "<td>" << row[2] << "</td>" << endl
                          << "<td>" << row[1] << "</td>" << endl
                          << "</tr>" << endl;
            }
            html_file << "</tbody>" << endl
                      << "</table>" << endl;
            mysql_free_result(res);      
        } 
    html_file << "</div>" << endl
              << "</div>" << endl
              << "</div>" << endl
              << "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2\" crossorigin=\"anonymous\"></script>" << endl
              << "</body>" << endl
              << "</html>" << endl;
    html_file.close();
    return true;
}
