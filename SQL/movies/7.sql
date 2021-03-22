SELECT title, (SELECT rating FROM ratings WHERE movie_id = id) FROM movies WHERE year = 2010
    ORDER BY (SELECT rating FROM ratings WHERE movie_id = id) DESC, title;