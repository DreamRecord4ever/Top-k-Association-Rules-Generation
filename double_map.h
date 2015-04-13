#ifndef __DOUBLE_MAP__H__
#define __DOUBLE_MAP__H__

#include <map>
#include <string>

class double_map{

    std::map<std::string, int> movie_to_id;
    std::map<int, std::string> id_to_movie;
    int movie_num;

public:
    double_map();
    bool movie_exist(std::string movie_name);
    int find_id(std::string movie_name);
    std::string find_movie_name(int id);
    int insert(std::string movie_name);
};

#endif
