-- Find the first_name, last_name and total_combined_film_length of Sci-Fi films for every actor.
-- That is the result should list the names of all of the actors(even if an actor has not been in any Sci-Fi films) and the total length of Sci-Fi films they have been in.
-- Look at the category table to figure out how to filter data for Sci-Fi films.
-- Order your results by the actor_id in descending order.
-- Put query for Q3 here

SELECT actor.actor_id, actor.first_name, actor.last_name, IFNULL(total_combined_film_length, 0) AS total_combined_film_length
FROM (
    SELECT first_name, last_name, SUM(film.length) AS total_combined_film_length, actor_id
    FROM (
        SELECT first_name, last_name, a.actor_id, a.film_id
        FROM (
            SELECT first_name, last_name, actor.actor_id, film_id
            FROM film_actor
            JOIN actor ON actor.actor_id = film_actor.actor_id
        ) AS a, film_category AS b
        WHERE a.film_id=b.film_id AND b.category_id=14
    ) as scifi_movies
    JOIN film on film.film_id=scifi_movies.film_id
    GROUP BY scifi_movies.actor_id
    ORDER BY scifi_movies.actor_id DESC
) as scifi_movies_table
RIGHT JOIN actor on actor.actor_id=scifi_movies_table.actor_id
GROUP BY actor.actor_id
ORDER BY actor.actor_id DESC;