#include "double_map.h"

double_map::double_map(){

    movie_num = 0;
}

bool double_map::movie_exist(std::string movie_name){

    if(movie_to_id.count(movie_name) == 0)
        return false;

    return true;
}

int double_map::find_id(std::string movie_name){

    if(!movie_exist(movie_name))
        return -1;

    return movie_to_id[movie_name];
}

std::string double_map::find_movie_name(int id){

    if(id_to_movie.count(id) == 0)
        return "";

    return id_to_movie[id];
}

int double_map::insert(std::string movie_name){

    // insert movie
    if(movie_exist(movie_name))
        return -1;

    int id = movie_num + 1;
    movie_to_id[movie_name] = id;
    id_to_movie[id] = movie_name;
    movie_num++;
    return id;
}
